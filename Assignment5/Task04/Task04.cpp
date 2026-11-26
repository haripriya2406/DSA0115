#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

class BillingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
class ClaimError : public BillingError {
public:
    using BillingError::BillingError;
};

class Bill {
protected:
    std::string patient;
public:
    explicit Bill(std::string p) : patient(std::move(p)) {}
    virtual ~Bill() noexcept = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(const std::string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) {
        if (c < 0 || t < 0) throw BillingError("negative outpatient charge");
    }
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OutPatient"; }
};

class DayCareBill : public Bill {
    double packagePrice;
public:
    DayCareBill(const std::string& p, double price) : Bill(p), packagePrice(price) {
        if (price < 0) throw BillingError("negative day-care package");
    }
    double total() const override { return packagePrice; }
    std::string type() const override { return "DayCare"; }
};

// New bill type: existing bill classes and the Bill interface remain unchanged.
class TelemedicineBill : public Bill {
    double consultation, platformFee;
public:
    TelemedicineBill(const std::string& p, double c, double fee)
        : Bill(p), consultation(c), platformFee(fee) {
        if (c < 0 || fee < 0) throw BillingError("negative telemedicine charge");
    }
    double total() const override { return consultation + platformFee; }
    std::string type() const override { return "Telemedicine"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual std::string name() const = 0;
};
class SelfPay : public Payer {
public:
    double amountCovered(const Bill& bill) const override { return bill.total(); }
    std::string name() const override { return "SelfPay"; }
};

// New payer: added without changing existing payer classes.
class CorporatePayer : public Payer {
    double percentage, maximum;
public:
    CorporatePayer(double percent, double cap) : percentage(percent), maximum(cap) {
        if (percent < 0 || percent > 100 || cap < 0)
            throw BillingError("invalid corporate payer policy");
    }
    double amountCovered(const Bill& bill) const override {
        return std::min(bill.total() * percentage / 100.0, maximum);
    }
    std::string name() const override { return "CorporateTieUp"; }
};

void processBill(const Bill& bill, const Payer& payer) {
    const double covered = payer.amountCovered(bill);
    if (covered < 0 || covered > bill.total())
        throw ClaimError("payer returned an invalid covered amount");
    std::cout << bill.type() << " for " << bill.patient
              << " | total=" << bill.total()
              << " | " << payer.name() << " covers=" << covered
              << " | balance=" << bill.total() - covered << '\n';
}

struct AuditGuard {
    std::string name;
    explicit AuditGuard(std::string n) : name(std::move(n)) {}
    ~AuditGuard() noexcept { std::cout << "released " << name << '\n'; }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("Ravi", 500, 1200));
    bills.push_back(std::make_unique<DayCareBill>("Meena", 60000));
    bills.push_back(std::make_unique<TelemedicineBill>("Kavin", 800, 100));

    SelfPay selfPay;
    CorporatePayer corporate(75, 30000);

    for (const auto& bill : bills) {
        try {
            processBill(*bill, selfPay);
            processBill(*bill, corporate);
        } catch (const BillingError& e) {
            std::cerr << "billing error: " << e.what() << '\n';
        }
    }

    try {
        AuditGuard guard("claim audit resource");
        throw ClaimError("demonstration exception");
    } catch (const ClaimError& e) {
        std::cout << "caught safely: " << e.what() << '\n';
    }

    try {
        OutPatientBill invalid("Test", -10, 200);
        (void)invalid;
    } catch (const BillingError& e) {
        std::cout << "invalid bill rejected: " << e.what() << '\n';
    }

    // Catch-all at the service boundary prevents an unhandled exception.
    try {
        throw std::runtime_error("unexpected service error");
    } catch (...) {
        std::cout << "top-level catch-all: request failed safely\n";
    }
    return 0;
}
