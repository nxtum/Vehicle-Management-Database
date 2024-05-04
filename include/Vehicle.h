#ifndef MANAGEMENT_SYSTEM_VEHICLE_H
#define MANAGEMENT_SYSTEM_VEHICLE_H

#include <string>
#include <ostream>
#include <sstream>

class Vehicle {
    // abstract class for the vehicles
private:
    std::string user;
    std::string manufacturer;
    std::string model;
    std::string modelVariant;
    int year{};
    double price{};
    std::string VIN;
    std::string colour;
    std::string fuelType;
    double engineSize{};
    std::string transmissionType;
    double mileage{};
    std::string condition;
    int numberOfPreviousOwners{};
    std::string description;


public:
    Vehicle() = default;

    // constructor for the vehicle, depending on the type of the vehicle

    Vehicle(const std::string &user, const std::string& manufacturer, const std::string& model, const std::string& modelVariant,
            int year, double price, const std::string& VIN, const std::string& colour,
            const std::string& fuelType, double engineSize, const std::string& transmissionType,
            double mileage, const std::string& condition, int numberOfPreviousOwners,
            const std::string& description, int numberOfDoors, const std::string& bodyStyle)
            : user(user), manufacturer(manufacturer), model(model), modelVariant(modelVariant),
              year(year), price(price), VIN(VIN), colour(colour), fuelType(fuelType),
              engineSize(engineSize), transmissionType(transmissionType), mileage(mileage),
              condition(condition), numberOfPreviousOwners(numberOfPreviousOwners),
              description(description) {

    }

    Vehicle(const std::string &user, const std::string& manufacturer, const std::string& model, const std::string& modelVariant,
            int year, double price, const std::string& VIN, const std::string& colour,
            const std::string& fuelType, double engineSize, const std::string& transmissionType,
            double mileage, const std::string& condition, int numberOfPreviousOwners,
            const std::string& description, int numberOfWheels)
            : user(user),manufacturer(manufacturer), model(model), modelVariant(modelVariant),
              year(year), price(price), VIN(VIN), colour(colour), fuelType(fuelType),
              engineSize(engineSize), transmissionType(transmissionType), mileage(mileage),
              condition(condition), numberOfPreviousOwners(numberOfPreviousOwners),
              description(description) {

    }

    virtual ~Vehicle() = default;

    virtual std::string getUsername() const {return user;}
    virtual std::string getManufacturer() const {return manufacturer;}
    virtual std::string getModel() const {return model;}
    virtual std::string getModelVariant() const {return modelVariant;}
    virtual int getYear() const {return year;}
    virtual double getPrice() const {return price;}
    virtual std::string getVIN() const {return VIN;}
    virtual std::string getColour() const { return colour; }
    virtual std::string getFuelType() const { return fuelType; }
    virtual double getEngineSize() const { return engineSize; }
    virtual std::string getTransmissionType() const { return transmissionType; }
    virtual double getMileage() const { return mileage; }
    virtual std::string getCondition() const { return condition; }
    virtual int getNumberOfPreviousOwners() const { return numberOfPreviousOwners; }
    virtual std::string getDescription() const { return description; } // Getter for description

    virtual std::string getTypeVehicle() const = 0;
    virtual std::string displayInfo() const;


    // Setters
    virtual void setManufacturer(const std::string& newMake) {manufacturer = newMake;}
    virtual void setModel(const std::string& newModel) {model = newModel;}
    virtual void setModelVariant(const std::string& newModelVariant) {modelVariant = newModelVariant;}
    virtual void setYear(int newYear) {year = newYear;}
    virtual void setPrice(double newPrice) {price = newPrice;}
    virtual void setVIN(const std::string& newVIN) {VIN = newVIN;}
    virtual void setColour(const std::string& newColour) { colour = newColour; }
    virtual void setFuelType(const std::string& newFuelType) { fuelType = newFuelType; }
    virtual void setEngineSize(double newSize) { engineSize = newSize; }
    virtual void setTransmissionType(const std::string& newTransmissionType) { transmissionType = newTransmissionType; }
    virtual void setMileage(double newMileage) { mileage = newMileage; }
    virtual void setCondition(const std::string& newCondition) { condition = newCondition; }
    virtual void setNumberOfPreviousOwners(int newOwners) { numberOfPreviousOwners = newOwners; }
    virtual void setDescription(const std::string& newDescription) { description = newDescription; } // Setter for description

    friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);
};
#endif //MANAGEMENT_SYSTEM_VEHICLE_H
