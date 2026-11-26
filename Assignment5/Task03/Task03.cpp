#include <chrono>
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <variant>
#include <vector>

using Clock = std::chrono::steady_clock;

struct BillBase {
    virtual ~BillBase() = default;
    virtual double total() const = 0;
};

struct OPVirtual : BillBase {
    double consultation, tests;
    double total() const override { return consultation + tests; }
};
struct IPVirtual : BillBase {
    double room, procedure;
    double total() const override { return room + procedure; }
};
struct DayVirtual : BillBase {
    double packagePrice;
    double total() const override { return packagePrice; }
};

enum class Kind { OP, IP, DayCare };
struct SwitchBill {
    Kind kind;
    double first, second;
};
double switchTotal(const SwitchBill& bill) {
    switch (bill.kind) {
        case Kind::OP: return bill.first + bill.second;
        case Kind::IP: return bill.first + bill.second;
        case Kind::DayCare: return bill.first;
    }
    return 0.0;
}

struct OPValue { double consultation, tests; };
struct IPValue { double room, procedure; };
struct DayValue { double packagePrice; };
using VariantBill = std::variant<OPValue, IPValue, DayValue>;

double variantTotal(const VariantBill& bill) {
    return std::visit([](const auto& item) -> double {
        using T = std::decay_t<decltype(item)>;
        if constexpr (std::is_same_v<T, OPValue>)
            return item.consultation + item.tests;
        else if constexpr (std::is_same_v<T, IPValue>)
            return item.room + item.procedure;
        else
            return item.packagePrice;
    }, bill);
}

template <typename Function>
double measureMs(Function function) {
    const auto start = Clock::now();
    const double result = function();
    const auto stop = Clock::now();
    volatile double keep = result;
    (void)keep;
    return std::chrono::duration<double, std::milli>(stop - start).count();
}

double returnCodeValidation(std::size_t count, int invalidPercent) {
    double accepted = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        const bool invalid = invalidPercent != 0 &&
            (i % 100) < static_cast<std::size_t>(invalidPercent);
        const int status = invalid ? 1 : 0;
        if (status == 0) accepted += 1.0;
    }
    return accepted;
}

double exceptionValidation(std::size_t count, int invalidPercent) {
    double accepted = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        const bool invalid = invalidPercent != 0 &&
            (i % 100) < static_cast<std::size_t>(invalidPercent);
        try {
            if (invalid) throw std::runtime_error("invalid claim");
            accepted += 1.0;
        } catch (const std::runtime_error&) {
            // The invalid claim is rejected; processing continues.
        }
    }
    return accepted;
}

int main() {
    std::cout << "Virtual / switch / variant benchmark (times in ms)\n";
    for (std::size_t count : {1000U, 1000000U, 10000000U}) {
        std::vector<std::unique_ptr<BillBase>> virtualBills;
        std::vector<SwitchBill> switchBills;
        std::vector<VariantBill> variantBills;
        virtualBills.reserve(count);
        switchBills.reserve(count);
        variantBills.reserve(count);

        for (std::size_t i = 0; i < count; ++i) {
            const int kind = static_cast<int>(i % 3);
            if (kind == 0) {
                auto bill = std::make_unique<OPVirtual>();
                bill->consultation = 500.0;
                bill->tests = 1200.0;
                virtualBills.push_back(std::move(bill));
                switchBills.push_back({Kind::OP, 500.0, 1200.0});
                variantBills.push_back(OPValue{500.0, 1200.0});
            } else if (kind == 1) {
                auto bill = std::make_unique<IPVirtual>();
                bill->room = 7500.0;
                bill->procedure = 40000.0;
                virtualBills.push_back(std::move(bill));
                switchBills.push_back({Kind::IP, 7500.0, 40000.0});
                variantBills.push_back(IPValue{7500.0, 40000.0});
            } else {
                auto bill = std::make_unique<DayVirtual>();
                bill->packagePrice = 60000.0;
                virtualBills.push_back(std::move(bill));
                switchBills.push_back({Kind::DayCare, 60000.0, 0.0});
                variantBills.push_back(DayValue{60000.0});
            }
        }

        const double virtualMs = measureMs([&] {
            double sum = 0.0;
            for (const auto& bill : virtualBills) sum += bill->total();
            return sum;
        });
        const double switchMs = measureMs([&] {
            double sum = 0.0;
            for (const auto& bill : switchBills) sum += switchTotal(bill);
            return sum;
        });
        const double variantMs = measureMs([&] {
            double sum = 0.0;
            for (const auto& bill : variantBills) sum += variantTotal(bill);
            return sum;
        });
        std::cout << count << " bills: virtual=" << virtualMs
                  << " switch=" << switchMs << " variant=" << variantMs << '\n';
        if (count == 1000) {
            double a = 0.0, b = 0.0, c = 0.0;
            for (const auto& x : virtualBills) a += x->total();
            for (const auto& x : switchBills) b += switchTotal(x);
            for (const auto& x : variantBills) c += variantTotal(x);
            std::cout << "Correctness check: " << a << " | " << b << " | " << c << '\n';
        }
    }

    std::cout << "\nValidation benchmark for 1,000,000 claims (ms)\n";
    constexpr std::size_t claims = 1000000;
    for (int invalid : {0, 1, 50}) {
        const double rcMs = measureMs([&] {
            return returnCodeValidation(claims, invalid);
        });
        const double exMs = measureMs([&] {
            return exceptionValidation(claims, invalid);
        });
        std::cout << invalid << "% invalid: return-code=" << rcMs
                  << " exception=" << exMs << '\n';
    }
    return 0;
}
