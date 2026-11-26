#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string items[10];
    double prices[10]{};
    int count = 0;
    double discount = 0.0;

public:
    Cart& add(const std::string& item, double price) {
        if (count < 10 && price >= 0.0) {
            items[count] = item;
            prices[count] = price;
            ++count;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    double total() const {
        double sum = 0.0;
        for (int i = 0; i < count; ++i) sum += prices[i];
        return sum * (100.0 - discount) / 100.0;
    }

    void display() const {
        for (int i = 0; i < count; ++i)
            std::cout << items[i] << ": " << prices[i] << '\\n';
    }
};

int main() {
    // (a) Direct object access.
    Cart direct;
    direct.add("Bread", 40);

    // (b) Pointer to an existing object.
    Cart second;
    Cart* pointer = &second;
    pointer->add("Milk", 50);

    // (c) Reference access.
    Cart& reference = second;
    reference.add("Eggs", 70);

    // (d) Dynamically created object; delete releases it.
    Cart* dynamicCart = new Cart;
    dynamicCart->add("Rice", 60).add("Dal", 120).setDiscount(10);
    std::cout << std::fixed << std::setprecision(2)
              << "Dynamic cart total: " << dynamicCart->total() << '\\n';
    delete dynamicCart;

    // Completed chaining example.
    Cart customer;
    customer.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* customerPointer = &customer;
    customerPointer->add("Oil", 180);
    std::cout << "Expected chaining total: " << customerPointer->total() << '\\n';

    // Array of pointers: find the cart with the largest total.
    Cart a, b, c;
    a.add("A", 100);
    b.add("B", 250);
    c.add("C", 175);
    Cart* carts[] = {&a, &b, &c};
    Cart* highest = carts[0];
    for (Cart** current = carts; current != carts + 3; ++current) {
        if ((*current)->total() > highest->total()) highest = *current;
    }
    std::cout << "Highest cart total: " << highest->total() << '\\n';
    return 0;
}
