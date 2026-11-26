#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {
protected:
    std::string name;
    int id;
    static constexpr double DA_RATE = 0.42;

public:
    Staff(const std::string& n, int i) : name(n), id(i) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    virtual void display() const {
        std::cout << name << " (" << id << ") Pay: " << pay() << '\n';
    }
};

class Professor : public Staff {
    double basic;
    double research;

public:
    Professor(const std::string& n, int i, double b, double r)
        : Staff(n, i), basic(b), research(r) {}
    double pay() const override { return basic * (1.0 + DA_RATE) + research; }
};

class LabAssistant : public Staff {
    double basic;

public:
    LabAssistant(const std::string& n, int i, double b)
        : Staff(n, i), basic(b) {}
    double pay() const override { return basic * (1.0 + DA_RATE); }
};

class GuestFaculty : public Staff {
    double hours;
    double rate;

public:
    GuestFaculty(const std::string& n, int i, double h, double r)
        : Staff(n, i), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};

int main() {
    std::vector<std::unique_ptr<Staff>> staff;
    staff.push_back(std::make_unique<Professor>("Anita", 101, 50000, 8000));
    staff.push_back(std::make_unique<LabAssistant>("Ravi", 102, 25000));
    staff.push_back(std::make_unique<GuestFaculty>("Meena", 103, 40, 750));

    for (const auto& person : staff) person->display();
    return 0;
}
