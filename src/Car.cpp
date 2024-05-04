#include <sstream>
#include "Car.h"

Car::Car(const std::string &user,const std::string& manufacturer, const std::string& model, const std::string& modelVariant,
         int year, double price, const std::string& VIN, const std::string& colour,
         const std::string& fuelType, double engineSize, const std::string& transmissionType,
         double mileage, const std::string& condition, int numberOfPreviousOwners,
         const std::string& description, int numberOfDoors, const std::string& bodyStyle)
        : Vehicle(user,manufacturer, model, modelVariant, year, price, VIN, colour, fuelType,
                  engineSize, transmissionType, mileage, condition, numberOfPreviousOwners,
                  description, numberOfDoors, bodyStyle), numberOfDoors(numberOfDoors), bodyStyle(bodyStyle) {}

std::string Car::displayInfo() const {

    // calls the base class displayInfo() function first
    // since shared attributes are stored in the base class

    std::stringstream info;
    info << Vehicle::displayInfo();
    info << "Number of Doors: " << numberOfDoors << "\n";
    info << "Body Style: " << bodyStyle << "\n";
    return info.str();
}

void Car::setNumberOfDoors(int newNumberOfDoors) {
    numberOfDoors = newNumberOfDoors;
}

void Car::setBodyStyle(const std::string& newBodyStyle) {
    bodyStyle = newBodyStyle;
}

std::ostream& operator<<(std::ostream& os, const Car& car) {

    // calls the base class operator<< function first
    os << static_cast<const Vehicle&>(car);
    os << "Number of Doors: " << car.numberOfDoors << "\n";
    os << "Body Style: " << car.bodyStyle << "\n";
    return os;
}

std::string Car::getTypeVehicle() const {
    return "Car";
}

