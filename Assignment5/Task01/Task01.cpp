#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

class Bill {
protected:
    std::string patient;
public:
    explicit Bill(std::string name) : patient(std::move(name)) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const { return "Bill"; }
    void print() const {
        std::cout << type() << " " << patient << ": " << total() << '\n';
    }
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(const std::string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};

class InPatientBill : public Bill {
    int days;
    double perDay, procedure, medicines;
public:
    InPatientBill(const std::string& p, int d, double rate, double proc, double med)
        : Bill(p), days(d), perDay(rate), procedure(proc), medicines(med) {}
    double total() const override { return days * perDay + procedure + medicines; }
    std::string type() const override { return "IP"; }
};

class DayCareBill : public Bill {
    double packagePrice;
public:
    DayCareBill(const std::string& p, double price) : Bill(p), packagePrice(price) {}
    double total() const override { return packagePrice; }
    std::string type() const override { return "DayCare"; }
};

class EmergencyBill : public Bill {
    double baseCharge, hourlyCharge;
    int hours;
public:
    EmergencyBill(const std::string& p, double base, double rate, int h)
        : Bill(p), baseCharge(base), hourlyCharge(rate), hours(h) {}
    double total() const override { return baseCharge + hourlyCharge * hours; }
    std::string type() const override { return "Emergency"; }
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

class Insurance : public Payer {
    double coverLimit, coPaymentPercent;
public:
    Insurance(double limit, double copay)
        : coverLimit(limit), coPaymentPercent(copay) {}
    double amountCovered(const Bill& bill) const override {
        const double eligible = bill.total() * (1.0 - coPaymentPercent / 100.0);
        return std::min(eligible, coverLimit);
    }
    std::string name() const override { return "Insurance"; }
};

class GovernmentScheme : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        if (bill.type() == "OP") return std::min(1500.0, bill.total());
        if (bill.type() == "IP") return std::min(40000.0, bill.total());
        if (bill.type() == "DayCare") return std::min(50000.0, bill.total());
        if (bill.type() == "Emergency") return std::min(12000.0, bill.total());
        return 0.0;
    }
    std::string name() const override { return "GovernmentScheme"; }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("Ravi", 500, 1200));
    bills.push_back(std::make_unique<InPatientBill>("Meena", 3, 2500, 40000, 0));
    bills.push_back(std::make_unique<DayCareBill>("Arun", 60000));
    bills.push_back(std::make_unique<EmergencyBill>("Sara", 10000, 2500, 3));

    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::make_unique<SelfPay>());
    payers.push_back(std::make_unique<Insurance>(50000, 20));
    payers.push_back(std::make_unique<GovernmentScheme>());

    double dayTotal = 0.0;
    for (const auto& bill : bills) {
        bill->print();
        dayTotal += bill->total();
    }
    std::cout << "Day total: " << dayTotal << "\n\n";

    for (const auto& payer : payers) {
        std::cout << payer->name() << '\n';
        for (const auto& bill : bills) {
            const double covered = payer->amountCovered(*bill);
            std::cout << "  " << bill->type() << ": covered "
                      << covered << ", patient balance "
                      << bill->total() - covered << '\n';
        }
    }
    return 0;
}
