#include <iostream>
#include <climits>
using namespace std;

int main() {
    long long farePaise = 1080;
    long long journeys = 3000000;
    long long totalPaise = farePaise * journeys;
    cout << "Fare in paise: " << farePaise << '\n';
    cout << "Total for " << journeys << " journeys: " << totalPaise << " paise\n";
    cout << "INT_MAX: " << INT_MAX << '\n';
    cout << "long long size: " << sizeof(long long) << " bytes\n";
    cout << "double size: " << sizeof(double) << " bytes\n";
}
