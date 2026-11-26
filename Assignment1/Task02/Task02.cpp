#include <iostream>
using namespace std;

constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
enum class Zone { Inner, Middle, Outer };

int main() {
    int zone = static_cast<int>(Zone::Outer);
    long long baseFare = 3000;
    long long fare = baseFare + baseFare * PEAK_SURCHARGE_PERCENT / 100;
    cout << "Zone identifier: " << zone << '\n';
    cout << "Fare (paise): " << fare << '\n';
    cout << "Minimum balance (paise): " << MIN_BALANCE_PAISE << '\n';
}
