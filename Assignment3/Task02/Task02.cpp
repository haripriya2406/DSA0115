#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Prescription {
private:
    int n;
    string* medicines;

public:
    explicit Prescription(int count)
        : n(count < 0 ? 0 : count),
          medicines(n > 0 ? new string[n] : nullptr) {}

    // Deep-copy constructor
    Prescription(const Prescription& other)
        : n(other.n),
          medicines(n > 0 ? new string[n] : nullptr) {
        for (int i = 0; i < n; ++i)
            medicines[i] = other.medicines[i];
        cout << "[copy constructor] ";
    }

    // Deep-copy assignment operator
    Prescription& operator=(const Prescription& other) {
        if (this == &other)
            return *this;

        string* newMedicines =
            other.n > 0 ? new string[other.n] : nullptr;

        for (int i = 0; i < other.n; ++i)
            newMedicines[i] = other.medicines[i];

        delete[] medicines;
        medicines = newMedicines;
        n = other.n;
        return *this;
    }

    ~Prescription() {
        delete[] medicines;
    }

    void set(int i, const string& medicine) {
        if (i >= 0 && i < n)
            medicines[i] = medicine;
    }

    string get(int i) const {
        if (i >= 0 && i < n)
            return medicines[i];
        return "";
    }

    int size() const {
        return n;
    }
};

void inspectByValue(Prescription prescription) {
    cout << "Passed by value; size = " << prescription.size() << '\n';
}

void inspectByReference(const Prescription& prescription) {
    cout << "Passed by const reference; size = "
         << prescription.size() << '\n';
}

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;
    p.set(0, "Ibuprofen");

    cout << p.get(0) << ' ' << p.get(1) << " | "
         << q.get(0) << ' ' << q.get(1) << " | "
         << r.get(0) << ' ' << r.get(1) << '\n';

    p = p; // self-assignment test
    cout << "After self-assignment: "
         << p.get(0) << ' ' << p.get(1) << '\n';

    inspectByValue(p);
    inspectByReference(p);
    return 0;
}