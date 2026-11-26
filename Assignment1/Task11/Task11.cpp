#include <iostream>
using namespace std;

class FarePolicy {
public:
    static constexpr long long MIN_BALANCE_PAISE = 5000;
    static constexpr int PEAK_PERCENT = 20;
    static constexpr int CONCESSION_PERCENT = 50;
    static long long applyConcession(long long fare) {
        return (fare * CONCESSION_PERCENT + 50) / 100;
    }
    static long long applyPeak(long long fare) {
        return (fare * (100 + PEAK_PERCENT) + 50) / 100;
    }
};

class SmartCard {
    long long balance_;
public:
    explicit SmartCard(long long balance) : balance_(balance) {}
    bool deduct(long long fare) {
        if (fare < 0 || balance_ - fare < FarePolicy::MIN_BALANCE_PAISE) return false;
        balance_ -= fare;
        return true;
    }
    long long balance() const { return balance_; }
};

int main() {
    SmartCard card(10000);
    long long fare = FarePolicy::applyPeak(FarePolicy::applyConcession(3000));
    cout << "Calculated fare: " << fare << " paise\n";
    cout << (card.deduct(fare) ? "Journey accepted" : "Journey denied") << '\n';
    cout << "Remaining balance: " << card.balance() << " paise\n";
}
