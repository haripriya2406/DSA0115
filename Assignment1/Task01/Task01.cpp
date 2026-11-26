#include <iostream>
#include <string>
using namespace std;

enum class Zone { Inner, Middle, Outer };
enum class Category { Regular, Student, Senior };

class Passenger {
    string name;
    Category category;
public:
    Passenger(string n, Category c) : name(n), category(c) {}
    bool isConcession() const { return category != Category::Regular; }
    string getName() const { return name; }
};

class Journey {
    Zone zone;
    int hour, minute;
public:
    Journey(Zone z, int h, int m) : zone(z), hour(h), minute(m) {}
    bool validTime() const { return hour >= 0 && hour < 24 && minute >= 0 && minute < 60; }
    bool isPeak() const {
        int t = hour * 60 + minute;
        return (t >= 480 && t < 600) || (t >= 1020 && t < 1200);
    }
    Zone getZone() const { return zone; }
};

class FareTable {
public:
    static constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
    static constexpr int CONCESSION_PERCENT = 50;
    static constexpr int PEAK_SURCHARGE_PERCENT = 20;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

    static long long fare(const Journey& j, bool concession) {
        long long base = BASE_PAISE[static_cast<int>(j.getZone())];
        if (concession) base = (base * CONCESSION_PERCENT + 50) / 100;
        if (j.isPeak()) base = (base * (100 + PEAK_SURCHARGE_PERCENT) + 50) / 100;
        return base;
    }
};

class SmartCard {
    long long balance_;
public:
    explicit SmartCard(long long balance) : balance_(balance) {}
    long long balance() const { return balance_; }
    bool canTravel(long long f) const { return f >= 0 && balance_ - f >= FareTable::MIN_BALANCE_PAISE; }
    bool deduct(long long f) {
        if (!canTravel(f)) return false;
        balance_ -= f;
        return true;
    }
    bool recharge(long long amount) {
        if (amount <= 0) return false;
        balance_ += amount;
        return true;
    }
};

int main() {
    Passenger p("Yashwanth", Category::Student);
    Journey j(Zone::Outer, 8, 30);
    SmartCard card(10000);
    if (!j.validTime()) { cout << "Invalid journey time\n"; return 0; }
    long long f = FareTable::fare(j, p.isConcession());
    cout << "Passenger: " << p.getName() << "\nFare: Rs " << f / 100 << "." << (f % 100 < 10 ? "0" : "") << f % 100 << "\n";
    cout << (card.deduct(f) ? "Travel allowed" : "Travel denied") << "\nBalance (paise): " << card.balance() << "\n";
}
