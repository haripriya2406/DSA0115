#include <iostream>
using namespace std;

long long proceduralBalance = 5400;
bool proceduralDeduct(long long fare) {
    if (proceduralBalance - fare < 5000) return false;
    proceduralBalance -= fare;
    return true;
}

class SmartCard {
    long long balance_;
public:
    explicit SmartCard(long long b) : balance_(b) {}
    bool deduct(long long fare) {
        if (fare < 0 || balance_ - fare < 5000) return false;
        balance_ -= fare;
        return true;
    }
    long long balance() const { return balance_; }
};

int main() {
    cout << "Procedural deduction: " << (proceduralDeduct(9999) ? "Allowed" : "Denied") << '\n';
    cout << "Procedural balance: " << proceduralBalance << '\n';
    SmartCard card(5400);
    cout << "OOP deduction: " << (card.deduct(9999) ? "Allowed" : "Denied") << '\n';
    cout << "OOP balance: " << card.balance() << '\n';
}
