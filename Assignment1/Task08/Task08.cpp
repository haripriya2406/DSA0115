#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    int zone, hour, minute;
    cout << "Enter zone (0-2), hour (0-23), minute (0-59): ";
    if (!(cin >> zone >> hour >> minute)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid numeric input\n";
        return 1;
    }
    if (zone < 0 || zone > 2 || hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        cout << "Invalid journey details\n";
        return 1;
    }
    long long fare = (zone + 1) * 1000LL;
    cout << fixed << setprecision(2);
    cout << "Base fare: Rs " << fare / 100.0 << '\n';
    cout << "Time: " << setw(2) << setfill('0') << hour << ':'
         << setw(2) << minute << '\n';
}
