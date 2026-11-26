#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class Complex {
private:
    double realPart;
    double imaginaryPart;

public:
    Complex() : realPart(0.0), imaginaryPart(0.0) {}

    Complex(double real) : realPart(real), imaginaryPart(0.0) {}

    Complex(double real, double imaginary)
        : realPart(real), imaginaryPart(imaginary) {}

    Complex operator+(const Complex& other) const {
        return Complex(realPart + other.realPart,
                       imaginaryPart + other.imaginaryPart);
    }

    Complex operator-(const Complex& other) const {
        return Complex(realPart - other.realPart,
                       imaginaryPart - other.imaginaryPart);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
            realPart * other.realPart - imaginaryPart * other.imaginaryPart,
            realPart * other.imaginaryPart + imaginaryPart * other.realPart
        );
    }

    Complex operator/(const Complex& other) const {
        double denominator =
            other.realPart * other.realPart +
            other.imaginaryPart * other.imaginaryPart;

        if (denominator == 0.0)
            throw domain_error("Division by zero impedance");

        return Complex(
            (realPart * other.realPart +
             imaginaryPart * other.imaginaryPart) / denominator,
            (imaginaryPart * other.realPart -
             realPart * other.imaginaryPart) / denominator
        );
    }

    bool operator==(const Complex& other) const {
        const double epsilon = 1e-9;
        return fabs(realPart - other.realPart) < epsilon &&
               fabs(imaginaryPart - other.imaginaryPart) < epsilon;
    }

    double magnitude() const {
        return hypot(realPart, imaginaryPart);
    }

    friend ostream& operator<<(ostream& out, const Complex& value) {
        out << fixed << setprecision(2)
            << value.realPart;
        if (value.imaginaryPart >= 0)
            out << " + j" << value.imaginaryPart;
        else
            out << " - j" << -value.imaginaryPart;
        return out;
    }
};

int main() {
    const double resistance = 30.0;
    const double inductiveReactance = 40.0;
    const double capacitiveReactance = 20.0;

    Complex zR(resistance);
    Complex zL(0.0, inductiveReactance);
    Complex zC(0.0, -capacitiveReactance);

    Complex series = zR + zL + zC;
    cout << "Series RLC impedance: " << series << '\n';
    cout << "Series magnitude: " << series.magnitude() << " ohms\n";

    Complex z1(10.0, 5.0);
    Complex z2(20.0, -5.0);
    try {
        Complex parallel = (z1 * z2) / (z1 + z2);
        cout << "Parallel impedance: " << parallel << '\n';
        cout << "Parallel magnitude: " << parallel.magnitude()
             << " ohms\n";
    } catch (const domain_error& error) {
        cout << error.what() << '\n';
    }

    try {
        Complex invalid = z1 / Complex();
        cout << invalid << '\n';
    } catch (const domain_error& error) {
        cout << "Safe division test: " << error.what() << '\n';
    }

    Complex check(30.0, 20.0);
    cout << boolalpha << "Series result verified: "
         << (series == check) << '\n';
    return 0;
}