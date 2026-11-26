#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Vehicle {
protected:
    std::string registration;
    double dailyRate;
    bool rented = false;

public:
    Vehicle(const std::string& reg, double rate)
        : registration(reg), dailyRate(rate) {}
    virtual ~Vehicle() = default;
    virtual double charge(int days) const = 0;

    bool rent() {
        if (rented) return false;
        rented = true;
        return true;
    }

    double returnVehicle(int lateDays = 0) {
        if (!rented) return 0.0;
        rented = false;
        return charge(1) * 0.25 * (lateDays > 0 ? lateDays : 0);
    }

    virtual void display(int days) const {
        std::cout << registration << " | Rental charge for " << days
                  << " day(s): " << charge(days) << '\n';
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate) : Vehicle(reg, rate) {}
    double charge(int days) const override { return dailyRate * days; }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel;
    std::string serviceDueDate;

public:
    MotorVehicle(const std::string& reg, double rate, double level,
                 const std::string& due)
        : Vehicle(reg, rate), fuelOrChargeLevel(level), serviceDueDate(due) {}
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& reg, double rate, double fuel,
               const std::string& due)
        : MotorVehicle(reg, rate, fuel, due) {}
    double charge(int days) const override { return dailyRate * days; }
};

class Car : public MotorVehicle {
protected:
    int seats;

public:
    Car(const std::string& reg, double rate, double fuel,
        const std::string& due, int capacity)
        : MotorVehicle(reg, rate, fuel, due), seats(capacity) {}
    double charge(int days) const override {
        return dailyRate * days + seats * 20.0;
    }
};

class ElectricCar : public Car {
    double batteryKWh;

public:
    ElectricCar(const std::string& reg, double rate, double level,
                const std::string& due, int capacity, double battery)
        : Car(reg, rate, level, due, capacity), batteryKWh(battery) {}
    double charge(int days) const override {
        return dailyRate * days + batteryKWh * 2.0;
    }
};

// New type added by extending the hierarchy; existing classes are unchanged.
class ElectricBus : public MotorVehicle {
    int seats;
    double batteryKWh;

public:
    ElectricBus(const std::string& reg, double rate, double level,
                const std::string& due, int capacity, double battery)
        : MotorVehicle(reg, rate, level, due), seats(capacity),
          batteryKWh(battery) {}
    double charge(int days) const override {
        return dailyRate * days + seats * 10.0 + batteryKWh * 1.5;
    }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("BIKE-01", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("TW-02", 250, 80, "2026-12-15"));
    fleet.push_back(std::make_unique<Car>("CAR-03", 1500, 60, "2026-12-20", 5));
    fleet.push_back(std::make_unique<ElectricCar>("EV-04", 1800, 90, "2026-12-25", 5, 60));
    fleet.push_back(std::make_unique<ElectricBus>("EB-05", 3000, 85, "2026-12-30", 30, 150));

    for (const auto& vehicle : fleet) {
        vehicle->rent();
        vehicle->display(3);
    }

    std::cout << "Late return charge for " << "CAR-03: "
              << fleet[2]->returnVehicle(2) << '\n';
    std::cout << "Returned CAR-03; available again: "
              << (fleet[2]->rent() ? "yes" : "no") << '\n';
    return 0;
}
