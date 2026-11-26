#include <iostream>
using namespace std;

int main() {
    int a = 7, b = 2;
    double integerDivision = a / b;
    double floatingDivision = static_cast<double>(a) / b;
    char ch = 'A';
    int code = ch + 1;
    int value = 5;
    bool flag = value;

    cout << "Integer division stored in double: " << integerDivision << '\n';
    cout << "Explicit floating division: " << floatingDivision << '\n';
    cout << "Character after A: " << static_cast<char>(ch + 2) << '\n';
    cout << "Character numeric value + 1: " << code << '\n';
    cout << boolalpha << "Boolean conversion: " << flag << '\n';
    int signedValue = -1;
    unsigned int unsignedValue = 1;
    cout << "Signed comparison: " << (signedValue < static_cast<int>(unsignedValue)) << '\n';
}
