#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    double rate() const { return 3.5; }
    virtual double virtualRate() const { return 3.5; }
    virtual ~Account() { std::cout << "Account destroyed\n"; }
};

class SeniorAccount : public Account {
    double* history;

public:
    SeniorAccount() : history(new double[100]{}) {}
    double rate() const { return 4.0; } // Non-virtual: base-pointer call uses Account::rate.
    double virtualRate() const override { return 4.0; }
    ~SeniorAccount() override {
        delete[] history;
        std::cout << "SeniorAccount destroyed; history released\n";
    }
};

int main() {
    SeniorAccount senior;
    Account* p = &senior;
    Account slicedCopy = senior;

    // Expected: 3.5 4 3.5
    std::cout << p->rate() << ' ' << p->virtualRate() << ' '
              << slicedCopy.virtualRate() << '\n';

    std::cout << "-- Safe polymorphic ownership --\n";
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for (const auto& account : accounts)
        std::cout << account->virtualRate() << '\n';

    // unique_ptr plus a virtual destructor releases the complete derived object.
    return 0;
}
