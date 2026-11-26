#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Time {
private:
    int totalSeconds;

public:
    Time(int hours = 0, int minutes = 0, int seconds = 0)
        : totalSeconds(hours * 3600 + minutes * 60 + seconds) {
        if (totalSeconds < 0)
            totalSeconds = 0;
        totalSeconds %= 24 * 3600;
    }

    Time& operator++() { // prefix
        totalSeconds = (totalSeconds + 1) % (24 * 3600);
        return *this;
    }

    Time operator++(int) { // postfix
        Time old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const Time& other) const {
        return totalSeconds == other.totalSeconds;
    }

    bool operator<(const Time& other) const {
        return totalSeconds < other.totalSeconds;
    }

    void display() const {
        int h = totalSeconds / 3600;
        int m = (totalSeconds / 60) % 60;
        int s = totalSeconds % 60;
        cout << (h < 10 ? "0" : "") << h << ':'
             << (m < 10 ? "0" : "") << m << ':'
             << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
private:
    string* tracks;
    int count;

public:
    explicit Playlist(int size)
        : tracks(size > 0 ? new string[size] : nullptr),
          count(size > 0 ? size : 0) {}

    ~Playlist() {
        delete[] tracks;
    }

    Playlist(const Playlist&) = delete;
    Playlist& operator=(const Playlist&) = delete;

    string& operator[](int index) {
        if (index < 0 || index >= count)
            throw out_of_range("Playlist index out of range");
        return tracks[index];
    }

    const string& operator[](int index) const {
        if (index < 0 || index >= count)
            throw out_of_range("Playlist index out of range");
        return tracks[index];
    }

    int size() const {
        return count;
    }
};

int main() {
    Time t(0, 0, 5);
    Time a = t++;
    Time b = ++t;

    cout << "Postfix result: ";
    a.display();
    cout << '\n' << "Prefix result: ";
    b.display();
    cout << '\n' << "Current time: ";
    t.display();
    cout << '\n';

    Time lastSecond(0, 59, 59);
    ++lastSecond;
    cout << "Minute rollover: ";
    lastSecond.display();
    cout << '\n';

    Time endOfDay(23, 59, 59);
    ++endOfDay;
    cout << "Day rollover: ";
    endOfDay.display();
    cout << '\n';

    Playlist playlist(3);
    playlist[0] = "Track One";
    playlist[1] = "Track Two";
    playlist[2] = "Track Three";

    const Playlist& readOnlyPlaylist = playlist;
    cout << "Now playing: " << readOnlyPlaylist[1] << '\n';

    try {
        cout << playlist[-1] << '\n';
    } catch (const out_of_range& error) {
        cout << error.what() << '\n';
    }

    try {
        cout << playlist[playlist.size()] << '\n';
    } catch (const out_of_range& error) {
        cout << error.what() << '\n';
    }
    return 0;
}