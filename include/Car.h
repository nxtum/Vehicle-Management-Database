#ifndef MANAGEMENT_SYSTEM_CAR_H
#define MANAGEMENT_SYSTEM_CAR_H

#include "Vehicle.h"
#include <sstream>

class Car : public Vehicle {
private:
    int numberOfDoors{};
    std::string bodyStyle;

public:
    Car() = default;
    Car(const std::string& user, const std::string& manufacturer, const std::string& model, const std::string& modelVariant,
        int year, double price, const std::string& VIN, const std::string& colour,
        const std::string& fuelType, double engineSize, const std::string& transmissionType,
        double mileage, const std::string& condition, int numberOfPreviousOwners,
        const std::string& description, int numberOfDoors, const std::string& bodyStyle);

    std::string displayInfo() const override;
    int getNumberOfDoors() const { return numberOfDoors; }
    std::string getBodyStyle() const { return bodyStyle; }
    void setNumberOfDoors(int newNumberOfDoors);
    void setBodyStyle(const std::string& newBodyStyle);

    friend std::ostream& operator<<(std::ostream& os, const Car& car);

    std::string getTypeVehicle() const override;
};

#endif //MANAGEMENT_SYSTEM_CAR_H
