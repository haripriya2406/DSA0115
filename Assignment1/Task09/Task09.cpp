#include <iostream>
#include <vector>
using namespace std;

enum class Zone { Inner, Middle, Outer };
struct TestCase { Zone zone; int hour, minute; bool concession; long long expected; };

bool isPeak(int h, int m) {
    int t = h * 60 + m;
    return (t >= 480 && t < 600) || (t >= 1020 && t < 1200);
}
long long calculateFare(const TestCase& c) {
    const long long base[] = {1000, 2000, 3000};
    long long f = base[static_cast<int>(c.zone)];
    if (c.concession) f = (f * 50 + 50) / 100;
    if (isPeak(c.hour, c.minute)) f = (f * 120 + 50) / 100;
    return f;
}
int main() {
    vector<TestCase> tests = {
        {Zone::Inner, 12, 0, false, 1000},
        {Zone::Outer, 8, 30, false, 3600},
        {Zone::Inner, 10, 0, false, 1000},
        {Zone::Inner, 20, 0, false, 1000},
        {Zone::Middle, 17, 0, true, 1200}
    };
    int passed = 0;
    for (size_t i = 0; i < tests.size(); ++i) {
        long long actual = calculateFare(tests[i]);
        bool ok = actual == tests[i].expected;
        passed += ok;
        cout << "Test " << i + 1 << ": expected " << tests[i].expected
             << ", actual " << actual << " -> " << (ok ? "PASS" : "FAIL") << '\n';
    }
    cout << passed << "/" << tests.size() << " tests passed\n";
}
