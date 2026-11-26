#include <iostream>
#include <algorithm>
using namespace std;

class AuditoriumEvent {
private:
    int rows;
    int seatsPerRow;
    bool** seats;
    int bookedCount;

public:
    AuditoriumEvent(int rowCount, int seatCount)
        : rows(max(0, rowCount)),
          seatsPerRow(max(0, seatCount)),
          seats(nullptr),
          bookedCount(0) {
        if (rows > 0 && seatsPerRow > 0) {
            seats = new bool*[rows];
            for (int r = 0; r < rows; ++r) {
                seats[r] = new bool[seatsPerRow]{};
            }
        }
        cout << "Event created: " << rows << " rows, "
             << seatsPerRow << " seats per row\n";
    }

    ~AuditoriumEvent() {
        if (seats != nullptr) {
            for (int r = 0; r < rows; ++r)
                delete[] seats[r];
            delete[] seats;
        }
        cout << "Event closed. Booked seats: " << bookedCount << '\n';
    }

    bool book(int row, int seat) {
        if (!valid(row, seat) || seats[row][seat])
            return false;
        seats[row][seat] = true;
        ++bookedCount;
        return true;
    }

    bool cancel(int row, int seat) {
        if (!valid(row, seat) || !seats[row][seat])
            return false;
        seats[row][seat] = false;
        --bookedCount;
        return true;
    }

    void display() const {
        cout << "Seat map (0=free, 1=booked):\n";
        for (int r = 0; r < rows; ++r) {
            for (int s = 0; s < seatsPerRow; ++s)
                cout << (seats[r][s] ? 1 : 0) << ' ';
            cout << '\n';
        }
    }

private:
    bool valid(int row, int seat) const {
        return row >= 0 && row < rows &&
               seat >= 0 && seat < seatsPerRow &&
               seats != nullptr;
    }
};

int main() {
    cout << "Stack event:\n";
    {
        AuditoriumEvent hall(2, 3);
        hall.book(0, 1);
        hall.book(1, 2);
        hall.cancel(0, 1);
        hall.display();
    }

    cout << "\nHeap event:\n";
    AuditoriumEvent* special = new AuditoriumEvent(3, 4);
    special->book(2, 1);
    special->display();
    delete special;

    cout << "\nZero-row event:\n";
    AuditoriumEvent emptyEvent(0, 5);
    emptyEvent.display();

    cout << "\nInner-block event:\n";
    {
        AuditoriumEvent shortEvent(1, 2);
        shortEvent.book(0, 0);
    }
    return 0;
}