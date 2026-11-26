#include <cstring>
#include <iostream>
#include <utility>
using namespace std;

class Text {
private:
    char* data;

public:
    explicit Text(const char* value = "") {
        if (value == nullptr) value = "";
        data = new char[strlen(value) + 1];
        strcpy(data, value);
    }

    Text(const Text& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        cout << "[copy] ";
    }

    Text& operator=(const Text& other) {
        if (this == &other)
            return *this;

        char* newData = new char[strlen(other.data) + 1];
        strcpy(newData, other.data);
        delete[] data;
        data = newData;
        return *this;
    }

    ~Text() {
        delete[] data;
    }

    Text& operator+=(const Text& other) {
        size_t newLength = strlen(data) + strlen(other.data);
        char* combined = new char[newLength + 1];
        strcpy(combined, data);
        strcat(combined, other.data);
        delete[] data;
        data = combined;
        return *this;
    }

    friend Text operator+(const Text& first, const Text& second) {
        Text result(first);
        result += second;
        return result;
    }

    friend bool operator==(const Text& first, const Text& second) {
        return strcmp(first.data, second.data) == 0;
    }

    friend bool operator!=(const Text& first, const Text& second) {
        return !(first == second);
    }

    friend ostream& operator<<(ostream& out, const Text& value) {
        return out << value.data;
    }
};

int main() {
    Text first("Hello");
    Text second(" ");
    Text third("World!");

    Text message = first + second + third;
    cout << "\nMessage: " << message << '\n';

    Text empty;
    cout << "Empty text: [" << empty << "]\n";

    Text longMessage("This is a longer SMS message used to test dynamic allocation.");
    cout << "Long message: " << longMessage << '\n';

    message = message; // self-assignment
    cout << "After self-assignment: " << message << '\n';

    Text another("Hello World!");
    cout << boolalpha << "Equal: " << (message == another) << '\n';
    cout << "Not equal: " << (message != first) << '\n';

    Text joined = first;
    joined += third;
    cout << "Using +=: " << joined << '\n';
    return 0;
}