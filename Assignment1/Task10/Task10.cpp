#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const long long farePaise = 1875;
    const long long journeys = 3000000;
    long long exactTotal = farePaise * journeys;
    double doubleTotal = static_cast<double>(farePaise) * journeys;
    float floatTotal = static_cast<float>(farePaise) * static_cast<float>(journeys);
    cout << "Journeys: " << journeys << '\n';
    cout << "Exact total (paise): " << exactTotal << '\n';
    cout << fixed << setprecision(2);
    cout << "double total (paise): " << doubleTotal << '\n';
    cout << "float total (paise): " << floatTotal << '\n';
    cout << "double error (paise): " << doubleTotal - exactTotal << '\n';
    cout << "float error (paise): " << static_cast<double>(floatTotal) - exactTotal << '\n';
}
