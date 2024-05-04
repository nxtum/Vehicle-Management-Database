#include "Vehicle.h"


std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle) {
    vehicle.displayInfo(); // Call the displayInfo function to output all properties
    return os;
}

std::string Vehicle::displayInfo() const {

    // all vehicles have these properties
    // so we output them here

    std::stringstream info;
    info << "Manufacturer: " << getManufacturer() << "\n";
    info << "Model: " << getModel() << "\n";
    info << "Model Variant: " << getModelVariant() << "\n";
    info << "Year: " << getYear() << "\n";
    info << "Price: " << getPrice() << "\n";
    info << "VIN: " << getVIN() << "\n";
    info << "Colour: " << getColour() << "\n";
    info << "Fuel Type: " << getFuelType() << "\n";
    info << "Engine Size: " << getEngineSize() << "\n";
    info << "Transmission Type: " << getTransmissionType() << "\n";
    info << "Mileage: " << getMileage() << "\n";
    info << "Condition: " << getCondition() << "\n";
    info << "Number of Previous Owners: " << getNumberOfPreviousOwners() << "\n";
    info << "Description: " << getDescription() << "\n";
    return info.str();
}
