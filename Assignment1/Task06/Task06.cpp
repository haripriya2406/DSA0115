#include <iostream>
using namespace std;

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };

long long baseFare(Zone z) {
    switch (z) {
        case Zone::Inner: return 1000;
        case Zone::Middle: return 2000;
        case Zone::Outer: return 3000;
    }
    return 0;
}

bool isPeak(int hour, int minute) {
    int t = hour * 60 + minute;
    return (t >= 480 && t < 600) || (t >= 1020 && t < 1200);
}

int main() {
    for (int h : {8, 10, 17, 20}) {
        cout << h << ":00 -> " << (isPeak(h, 0) ? "Peak" : "Off-peak") << '\n';
    }
    cout << "Outer zone base fare: " << baseFare(Zone::Outer) << " paise\n";
}
