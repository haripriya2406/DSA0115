#include <iostream>
using namespace std;

class BusTicket {
private:
    int seatId;
    static int nextSeatId;
    static const int capacity = 40;

public:
    BusTicket() : seatId(++nextSeatId) {}

    int getSeatId() const {
        return seatId;
    }

    static int issued() {
        return nextSeatId - 100;
    }

    static int getCapacity() {
        return capacity;
    }
};

int BusTicket::nextSeatId = 100;

void createTickets() {
    BusTicket tickets[3];
    for (const BusTicket& ticket : tickets)
        cout << ticket.getSeatId() << ' ';
    cout << '\n';
}

int main() {
    BusTicket tickets[3];
    for (const BusTicket& ticket : tickets)
        cout << ticket.getSeatId() << ' ';
    cout << '\n';

    BusTicket extra;
    cout << extra.getSeatId() << '\n';
    cout << "Total issued: " << BusTicket::issued() << '\n';
    cout << "Bus capacity: " << BusTicket::getCapacity() << '\n';

    createTickets();
    cout << "Total issued after function: "
         << BusTicket::issued() << '\n';
    return 0;
}