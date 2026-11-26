#include <iostream>
using namespace std;

class Time {
private:
    int h;
    int m;

    int totalMinutes() const {
        return h * 60 + m;
    }

public:
    Time(int hours = 0, int minutes = 0) : h(hours), m(minutes) {
        if (h < 0 || h > 23 || m < 0 || m > 59) {
            h = 0;
            m = 0;
        }
    }

    friend inline int minutesBetween(const Time& first, const Time& second);
    friend inline bool earlier(const Time& first, const Time& second);
};

inline int minutesBetween(const Time& first, const Time& second) {
    return second.totalMinutes() - first.totalMinutes();
}

inline bool earlier(const Time& first, const Time& second) {
    return first.totalMinutes() < second.totalMinutes();
}

int main() {
    Time departure(9, 45);
    Time arrival(13, 10);

    cout << minutesBetween(departure, arrival) << ' '
         << boolalpha << earlier(arrival, departure) << '\n';

    Time sameTime(10, 30);
    cout << minutesBetween(sameTime, sameTime) << ' '
         << earlier(sameTime, sameTime) << '\n';

    Time morning(11, 0);
    Time afternoon(13, 0);
    cout << minutesBetween(morning, afternoon) << ' '
         << earlier(morning, afternoon) << '\n';
    return 0;
}