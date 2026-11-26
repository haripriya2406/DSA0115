#include <iomanip>
#include <iostream>
#include <stdexcept>
using namespace std;

class Money {
private:
    long long paise;

public:
    Money(long long rupees = 0, int extraPaise = 0)
        : paise(rupees * 100 + extraPaise) {}

    explicit Money(long long totalPaise, bool)
        : paise(totalPaise) {}

    Money operator+(const Money& other) const {
        return Money(paise + other.paise, true);
    }

    Money operator-(const Money& other) const {
        return Money(paise - other.paise, true);
    }

    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const {
        return paise == other.paise;
    }

    bool operator<(const Money& other) const {
        return paise < other.paise;
    }

    friend ostream& operator<<(ostream& out, const Money& amount) {
        long long absolutePaise = amount.paise < 0
            ? -amount.paise : amount.paise;
        if (amount.paise < 0) out << "-";
        out << "Rs " << absolutePaise / 100 << '.'
            << setw(2) << setfill('0') << absolutePaise % 100
            << setfill(' ');
        return out;
    }

    friend istream& operator>>(istream& in, Money& amount) {
        long long rupees;
        int p;
        if (in >> rupees >> p)
            amount.paise = rupees * 100 + p;
        return in;
    }

    long long getPaise() const {
        return paise;
    }
};

int main() {
    Money item1(120, 75);
    Money item2(79, 25);
    Money total = item1 + item2;

    cout << total << '\n';
    cout << boolalpha << (total == Money(200)) << '\n';

    Money carryTest = Money(0, 75) + Money(0, 50);
    cout << "Carry test: " << carryTest << '\n';

    Money negative = Money(2, 0) - Money(3, 25);
    cout << "Negative subtraction: " << negative << '\n';

    Money bill(50, 0);
    bill += item1;
    cout << "Bill total: " << bill << '\n';
    cout << "Is item1 less than item2? " << (item1 < item2) << '\n';
    return 0;
}