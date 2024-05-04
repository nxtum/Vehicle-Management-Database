#ifndef MANAGEMENT_SYSTEM_DATABASEHANDLER_H
#define MANAGEMENT_SYSTEM_DATABASEHANDLER_H

#include <vector>
#include <string>
#include <memory>
#include "Vehicle.h"
#include "Car.h"
#include "Motorbike.h"
#include "Human.h"
#include "Admin.h"
#include "Employee.h"
#include "Customer.h"


class DatabaseHandler {
    // class responsible for saving and loading data from the database, mySQL
public:
    static void saveVehicles(const std::string& dbName, const std::vector<std::shared_ptr<Vehicle>>& vehicles);
    static void loadInventory(const std::string& dbName, std::vector<std::shared_ptr<Vehicle>>& inventory);
    static void saveUsers(const std::string& dbName, const std::vector<std::shared_ptr<Human>>& users);
    static void loadUsers(const std::string& dbName, std::vector<std::shared_ptr<Human>>& users);
};

#endif //MANAGEMENT_SYSTEM_DATABASEHANDLER_H
