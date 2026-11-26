#include <iostream>
using namespace std;

void change(int a, int& b, int* c) {
    a += 10;
    b += 11;
    if (c != nullptr) *c += 12;
}

int& bigger(int& a, int& b) {
    return (a > b) ? a : b;
}

void show(int x, int y = 5, int z = 10) {
    cout << x + y + z << '\n';
}

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
    cout << "Inside value function: " << fee << '\n';
}

void applyByReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}

void applyByPointer(long long* fee, int percent) {
    if (fee != nullptr)
        *fee -= *fee * percent / 100;
}

int main() {
    int a = 1, b = 1, c = 1;
    change(a, b, &c);
    cout << "After change: " << a << ' ' << b << ' ' << c << '\n';

    bigger(a, c) = 100;
    cout << "After bigger assignment: " << a << ' ' << c << '\n';

    cout << "Default arguments:\n";
    show(1);
    show(1, 2);
    show(1, 2, 3);

    long long fee = 45000;
    cout << "Original hostel fee: " << fee << '\n';
    applyByValue(fee, 10);
    cout << "After call by value: " << fee << '\n';
    applyByReference(fee, 10);
    cout << "After call by reference: " << fee << '\n';

    fee = 45000;
    applyByPointer(&fee, 10);
    cout << "After call by pointer: " << fee << '\n';
    return 0;
}