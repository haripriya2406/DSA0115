#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n, int i, const std::string& p)
        : name(n), id(i), phone(p) {
        std::cout << "Person constructed\\n";
    }
    virtual ~Person() = default;
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n, int i, const std::string& p,
            const std::string& course, double g)
        : Person(n, i, p), programme(course), cgpa(g) {
        std::cout << "Student constructed\\n";
    }
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n, int i, const std::string& p,
          const std::string& dept, double s)
        : Person(n, i, p), department(dept), salary(s) {
        std::cout << "Staff constructed\\n";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& course, double g,
                      const std::string& dept, double s)
        : Person(n, i, p), Student(n, i, p, course, g),
          Staff(n, i, p, dept, s) {
        std::cout << "TeachingAssistant constructed\\n";
    }

    void display() const {
        std::cout << name << " | ID: " << id << " | " << phone
                  << " | " << programme << " | CGPA: " << cgpa
                  << " | " << department << " | Salary: " << salary << '\\n';
    }
};

class ResearchScholar : public Student {
    double fellowship;

public:
    ResearchScholar(const std::string& n, int i, const std::string& p,
                    const std::string& course, double g, double f)
        : Person(n, i, p), Student(n, i, p, course, g), fellowship(f) {}
    void display() const {
        std::cout << name << " | Research Scholar | Fellowship: "
                  << fellowship << '\\n';
    }
};

int main() {
    TeachingAssistant ta("Kavya", 201, "9876543210", "CSE", 8.7,
                         "Computer Science", 30000);
    ta.display();

    ResearchScholar scholar("Arun", 202, "9876501234", "IT", 9.1, 15000);
    scholar.display();
    return 0;
}
