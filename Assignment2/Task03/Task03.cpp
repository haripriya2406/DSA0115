#include <iostream>
#include <string>
using namespace std;

struct Parcel {
    double weight;
    bool express = false;
    bool insured = false;
};

double charge(int weight, bool express = false, bool insured = false) {
    double amount = weight * 10.0;
    if (express) amount += 20.0;
    if (insured) amount += 15.0;
    return amount;
}

double charge(double weight, bool express = false, bool insured = false) {
    double amount = weight * 10.0;
    if (express) amount += 20.0;
    if (insured) amount += 15.0;
    return amount;
}

double charge(const Parcel& parcel) {
    return charge(parcel.weight, parcel.express, parcel.insured);
}

int main() {
    cout << "charge(2.5): " << charge(2.5) << '\n';
    cout << "charge(2): " << charge(2) << '\n';
    cout << "charge(2.0f): " << charge(static_cast<double>(2.0f)) << '\n';
    cout << "charge(3.1, true): " << charge(3.1, true) << '\n';
    cout << "charge(500, false, true): "
         << charge(500, false, true) << '\n';

    Parcel parcel{4.5, true, true};
    cout << "charge(parcel): " << charge(parcel) << '\n';
    return 0;
}