#include <iostream>
#include <sstream>
#include "Motorbike.h"

std::string Motorbike::displayInfo() const {

    // call the base class displayInfo

    std::stringstream info;
    info << Vehicle::displayInfo();
    info << "Number of Wheels: " << getNumberOfWheels() << "\n";

    return info.str();
    }

int Motorbike::getNumberOfWheels() const {
    return numberOfWheels;
}

std::ostream &operator<<(std::ostream &os, const Motorbike &motorbike) {
    os << static_cast<const Vehicle&>(motorbike);

    // properties specific to vehicle class
    os << "Number of wheels: " << motorbike.getNumberOfWheels()<< "\n";

    return os;  // Return the stream object

}

std::string Motorbike::getTypeVehicle() const {
    return "Motorbike";
}

