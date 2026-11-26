#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 3;
    cout << "x + y * 2 = " << x + y * 2 << '\n';
    cout << "(x + y) * 2 = " << (x + y) * 2 << '\n';

    int a = 5, b = 3;
    cout << "a++ + ++b = " << a++ + ++b << '\n';
    cout << "a = " << a << ", b = " << b << '\n';
    cout << " -10 / 3 = " << -10 / 3 << '\n';
    cout << " -10 % 3 = " << -10 % 3 << '\n';

    int total = 0;
    for (int i = 0; i <= 9; i += 3) total += i;
    cout << "Sum of 0, 3, 6, 9 = " << total << '\n';
}
