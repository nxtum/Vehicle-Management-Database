#ifndef MANAGEMENT_SYSTEM_DEALERSHIP_H
#define MANAGEMENT_SYSTEM_DEALERSHIP_H

#include <vector>
#include <memory>
#include "Vehicle.h"
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <sqlite3.h>
#include "DatabaseHandler.h"


class Dealership {
private:
    std::vector<std::shared_ptr<Vehicle>> currentInventory;
    std::vector<std::shared_ptr<Vehicle>> soldVehicles; // Once a person has bought a vehicle, currentI -> sold


public:
    void addVehicleToInventory(std::string &username, Dealership &dealership);
    void displayInventory() const;
    void displaySoldInventory() const;
    void deleteVehicle(const std::string &username, const std::string &role);
    void buyVehicle();


    void saveToFile();
    void loadFromFile(const std::string& filename, const std::string& filename2);

    template <typename T>
    static T createVehicle(const std::string& vehicleType, std::string &username, Dealership &dealership);

    template <typename T>
    static T getInput(const std::string& prompt);

    bool isVINAlreadyExists(const std::string &vin) const;
};

#endif //MANAGEMENT_SYSTEM_DEALERSHIP_H
