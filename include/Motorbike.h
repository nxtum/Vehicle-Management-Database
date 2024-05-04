#ifndef MANAGEMENT_SYSTEM_MOTORBIKE_H
#define MANAGEMENT_SYSTEM_MOTORBIKE_H


#include "Vehicle.h"

class Motorbike : public Vehicle {
private:
    int numberOfWheels{};

public:
    Motorbike()= default;

    Motorbike(const std::string &user, const std::string& manufacturer, const std::string& model, const std::string& variant,
              int year, double price, const std::string& VIN, const std::string& colour,
              const std::string& fuelType, double engineSize, const std::string& transmissionType,
              double mileage, const std::string& condition, int numberOfPreviousOwners,
              const std::string& description, int numberOfWheels)
            : Vehicle(user, manufacturer, model, variant, year, price, VIN, colour, fuelType,
                             engineSize, transmissionType, mileage, condition, numberOfPreviousOwners,
                             description, numberOfWheels), numberOfWheels(numberOfWheels) {}


    std::string displayInfo() const override;

    int getNumberOfWheels() const;

    friend std::ostream& operator<<(std::ostream& os, const Motorbike& motorbike);

    std::string getTypeVehicle() const override;
};


#endif //MANAGEMENT_SYSTEM_MOTORBIKE_H
