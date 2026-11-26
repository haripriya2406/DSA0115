#include <iostream>
#include <array>
using namespace std;

enum class Zone { Inner, Middle, Outer, Airport };
enum class DayType { Weekday, Weekend };

class MonthlyPass {
    array<bool, 4> covered_{};
public:
    MonthlyPass(Zone a, Zone b) {
        covered_[static_cast<int>(a)] = true;
        covered_[static_cast<int>(b)] = true;
    }
    bool covers(Zone z) const { return covered_[static_cast<int>(z)]; }
};

class FareEngine {
    static constexpr array<long long, 4> BASE = {1000, 2000, 3000, 6000};
public:
    static long long calculate(Zone z, int hour, int minute, DayType day,
                               bool concession, const MonthlyPass* pass = nullptr) {
        if (pass && pass->covers(z)) return 0;
        long long fare = BASE[static_cast<int>(z)];
        if (concession) fare = (fare * 50 + 50) / 100;
        int t = hour * 60 + minute;
        bool peak = (t >= 480 && t < 600) || (t >= 1020 && t < 1200);
        if (day == DayType::Weekend) {
            fare = (fare * 90 + 50) / 100; // Weekend discount replaces peak surcharge.
        } else if (peak) {
            fare = (fare * 120 + 50) / 100;
        }
        return fare;
    }
};

int main() {
    MonthlyPass pass(Zone::Inner, Zone::Airport);
    cout << "Airport pass journey: "
         << FareEngine::calculate(Zone::Airport, 8, 30, DayType::Weekday, false, &pass)
         << " paise\n";
    cout << "Airport weekend journey: "
         << FareEngine::calculate(Zone::Airport, 12, 0, DayType::Weekend, false)
         << " paise\n";
    cout << "Outer weekday peak: "
         << FareEngine::calculate(Zone::Outer, 8, 30, DayType::Weekday, false)
         << " paise\n";
}
