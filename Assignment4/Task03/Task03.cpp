#include <iostream>
#include <string>

class Address {
    std::string city;
    int pin;

public:
    Address(const std::string& c = "Unknown", int p = 0) : city(c), pin(p) {
        std::cout << "Address constructed\\n";
    }
    ~Address() { std::cout << "Address destroyed\\n"; }
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class Course {
    std::string title;

public:
    explicit Course(const std::string& t) : title(t) {
        std::cout << "Course constructed\\n";
    }
    ~Course() { std::cout << "Course destroyed\\n"; }
};

class Person {
protected:
    std::string name;
    int age;
    Address address;

public:
    Person(const std::string& n, int a, const std::string& city, int pin)
        : name(n), age(a), address(city, pin) {
        std::cout << "Person constructed\\n";
    }
    virtual ~Person() { std::cout << "Person destroyed\\n"; }
};

class Student : virtual public Person {
    long long regNo;
    Course course;

public:
    Student(const std::string& n, int a, long long r,
            const std::string& city, int pin, const std::string& subject)
        : Person(n, a, city, pin), regNo(r), course(subject) {
        std::cout << "Student constructed\\n";
    }
    ~Student() override { std::cout << "Student destroyed\\n"; }

    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") "
                  << address.str() << '\\n';
    }
};

class Staff : virtual public Person {
    std::string department;

public:
    Staff(const std::string& n, int a, const std::string& city, int pin,
          const std::string& dept)
        : Person(n, a, city, pin), department(dept) {
        std::cout << "Staff constructed\\n";
    }
    ~Staff() override { std::cout << "Staff destroyed\\n"; }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int a, long long r,
                      const std::string& city, int pin,
                      const std::string& subject, const std::string& dept)
        : Person(n, a, city, pin),
          Student(n, a, r, city, pin, subject),
          Staff(n, a, city, pin, dept) {
        std::cout << "TeachingAssistant constructed\\n";
    }
    ~TeachingAssistant() override {
        std::cout << "TeachingAssistant destroyed\\n";
    }
};

// Complete-the-code example: base, regNo and Address are initialised in the list.
class AddressStudent : public Person {
    long long regNo;
    Address home;

public:
    AddressStudent(const std::string& n, int a, long long r,
                   const std::string& city, int pin)
        : Person(n, a, city, pin), regNo(r), home(city, pin) {}
    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") "
                  << home.str() << '\\n';
    }
};

int main() {
    std::cout << "-- Student --\\n";
    {
        Student s("Kavya", 19, 192311001, "Salem", 636001, "C++");
        s.print();
    }

    std::cout << "-- Staff --\\n";
    {
        Staff member("Ravi", 35, "Chennai", 600001, "IT");
    }

    std::cout << "-- Teaching Assistant --\\n";
    {
        TeachingAssistant ta("Meena", 24, 192311002, "Madurai", 625001,
                             "OOP", "IT");
    }

    std::cout << "-- Initializer-list example --\\n";
    AddressStudent example("Kavya", 19, 192311001, "Salem", 636001);
    example.print();
    return 0;
}
