#include "Dealership.h"
#include "Car.h"
#include "Motorbike.h"
#include <iostream>
#include <limits>

void Dealership::addVehicleToInventory(std::string &username, Dealership &dealership) {
    int choice;
    std::cout << "Select the type of vehicle to add:\n";
    std::cout << "1. Car\n";
    std::cout << "2. Motorbike\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    std::shared_ptr<Vehicle> newVehicle;

    switch (choice) {
        case 1:
            newVehicle = createVehicle<std::shared_ptr<Vehicle>>("Car", username,dealership);

            break;
        case 2:
            newVehicle = createVehicle<std::shared_ptr<Vehicle>>("Motorbike", username, dealership);

            break;
        default:
            std::cout << "Invalid choice.\n";
            return;
    }

    if (newVehicle) {
        currentInventory.push_back(newVehicle);
        std::cout << "Vehicle added to inventory.\n";
    }

}

void Dealership::displayInventory() const {
    std::cout << "Current Inventory:\n";
    std::cout << "-----------------\n";
    if (currentInventory.empty()) {
        std::cout << "Inventory is empty.\n";
    } else {
        for (const auto& vehicle : currentInventory) {
            std::cout << vehicle->displayInfo();
            std::cout << "-----------------\n";
        }
    }
}

void Dealership::displaySoldInventory() const {

    for (const auto& vehicle : soldVehicles) {
        std::cout << vehicle->displayInfo();
        std::cout << "\n-----------------\n";
    }
}

void Dealership::deleteVehicle(const std::string& username, const std::string &role) {
    std::string vinToDelete;
    std::cout << "Enter the VIN of the vehicle you want to delete: ";
    std::cin >> vinToDelete;


    bool vehicleDeleted = false; // Flag to indicate if the vehicle was found and deleted

    // find the vehicle with the given VIN
    for (auto it = currentInventory.begin(); it != currentInventory.end(); ++it) {
        if ((*it)->getVIN() == vinToDelete) {
            // checks if the user is authorized to delete the vehicle
            if (role == "customer") {
                // Check if the vehicle belongs to the customer
                if ((*it)->getUsername() != username) {
                    std::cout << "You can only delete your own listings.\n";
                    return;
                }
            }
            // erase it from the vector
            currentInventory.erase(it);
            std::cout << "Vehicle with VIN " << vinToDelete << " deleted from inventory.\n";
            vehicleDeleted = true;
            break;
        }
    }

    if (!vehicleDeleted) {
        std::cout << "Vehicle with VIN " << vinToDelete << " not found in inventory.\n";
    }

}

void Dealership::buyVehicle()  {
    std::string vinToBuy;
    std::cout << "Enter the VIN of the vehicle you want to buy: ";
    std::cin >> vinToBuy;

    // find the vehicle with the given VIN

    auto it = std::find_if(currentInventory.begin(), currentInventory.end(), [vinToBuy](const auto& vehicle) {
        return vehicle->getVIN() == vinToBuy; // Find the vehicle in the current inventory
    });

    if (it != currentInventory.end()) {

        soldVehicles.push_back(*it); // Vehicle bought = Current inventory -> Sold
        currentInventory.erase(it);
        std::cout << "Vehicle with VIN " << vinToBuy << " bought successfully.\n";
    } else {
        std::cout << "Vehicle with VIN " << vinToBuy << " not found in inventory.\n";
    }

}

void Dealership::saveToFile() {
    // saves to mySQL database
    DatabaseHandler::saveVehicles("inventory.db", currentInventory);
    DatabaseHandler::saveVehicles("sold_inventory.db", soldVehicles);
}


void Dealership::loadFromFile(const std::string& currentInventoryFile, const std::string& soldInventoryFile) {
    DatabaseHandler::loadInventory(currentInventoryFile, currentInventory);
    DatabaseHandler::loadInventory(soldInventoryFile, soldVehicles);
}


template <typename T>
T Dealership::createVehicle(const std::string& vehicleType, std::string& username, Dealership &dealership) {

    // template since vehicle can be Car or Motorbike

    std::string manufacturer, model, variant, vin, colour, fuelType, transmissionType, condition, description;
    int year, numberOfPreviousOwners;
    double price, engineSize, mileage;

    // Input details
    manufacturer = getInput<std::string>("Manufacturer: ");
    model = getInput<std::string>("Model: ");
    variant = getInput<std::string>("Variant: ");
    year = getInput<int>("Year: ");
    price = getInput<double>("Price: ");
    vin = getInput<std::string>("VIN: ");
    colour = getInput<std::string>("Colour: ");
    fuelType = getInput<std::string>("Fuel Type: ");
    engineSize = getInput<double>("Engine Size: ");
    transmissionType = getInput<std::string>("Transmission Type: ");
    mileage = getInput<double>("Mileage: ");
    condition = getInput<std::string>("Condition: ");
    numberOfPreviousOwners = getInput<int>("Number of Previous Owners: ");
    description = getInput<std::string>("Description: ");

    // Check if the VIN already exists in the inventory
    if (dealership.isVINAlreadyExists(vin)) {
        std::cerr << "Error: Vehicle with VIN " << vin << " already exists in inventory.\n";
        return nullptr;
    }

    // additional attributes based on vehicle type
    int numberOfDoors = 0;
    std::string bodyStyle = "";
    int numberOfWheels = 0;

    if (vehicleType == "Car") {
        numberOfDoors = getInput<int>("Number of Doors: ");
        bodyStyle = getInput<std::string>("Body Style: ");
    } else if (vehicleType == "Motorbike") {
        numberOfWheels = getInput<int>("Number of Wheels: ");
    } else {
        std::cerr << "Unknown vehicle type.\n";
        return nullptr;
    }

    // return the appropriate vehicle object
    if (vehicleType == "Car") {
        return std::make_shared<Car>(
                username, manufacturer, model, variant, year, price, vin, colour, fuelType,
                engineSize, transmissionType, mileage, condition, numberOfPreviousOwners,
                description, numberOfDoors, bodyStyle);
    } else if (vehicleType == "Motorbike") {
        return std::make_shared<Motorbike>(
                username, manufacturer, model, variant, year, price, vin, colour, fuelType,
                engineSize, transmissionType, mileage, condition, numberOfPreviousOwners,
                description, numberOfWheels);
    } else {
        std::cerr << "Unknown vehicle type.\n";
        return nullptr;
    }
}

bool Dealership::isVINAlreadyExists(const std::string& vin) const {
    // Iterate through the current inventory to check if the VIN already exists
    for (const auto& vehicle : currentInventory) {
        if (vehicle->getVIN() == vin) {
            return true; // VIN already exists
        }
    }
    return false; // VIN does not exist
}


template <typename T>
T Dealership::getInput(const std::string& prompt) {
    T value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cerr << "Invalid input. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    return value;
}