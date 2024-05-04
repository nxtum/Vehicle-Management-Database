#include "DatabaseHandler.h"
#include <sqlite3.h>
#include <iostream>

void DatabaseHandler::saveVehicles(const std::string& dbName, const std::vector<std::shared_ptr<Vehicle>>& vehicles) {
    sqlite3 *db;
    int result = sqlite3_open(dbName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // create table if not exists
    const char *createTableQuery =
            "CREATE TABLE IF NOT EXISTS Inventory ("
            "Manufacturer TEXT,"
            "Model TEXT,"
            "Variant TEXT,"
            "Year INTEGER,"
            "Price REAL,"
            "VIN TEXT PRIMARY KEY,"
            "Colour TEXT,"
            "FuelType TEXT,"
            "EngineSize REAL,"
            "TransmissionType TEXT,"
            "Mileage REAL,"
            "Condition TEXT,"
            "NumberOfPreviousOwners INTEGER,"
            "Description TEXT,"
            "NumberOfDoors INTEGER,"
            "BodyStyle TEXT,"
            "NumberOfWheels INTEGER"
            ");";

    result = sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error creating table: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // insert vehicles into the database
    const char *insertVehicleQuery =
            "INSERT OR IGNORE INTO Inventory (Manufacturer, Model, Variant, Year, Price, VIN, Colour, FuelType, EngineSize, TransmissionType, Mileage, Condition, NumberOfPreviousOwners, Description, NumberOfDoors, BodyStyle, NumberOfWheels) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    result = sqlite3_prepare_v2(db, insertVehicleQuery, -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    for (const auto &vehicle: vehicles) {
        // Check if the vehicle with the same VIN already exists in the database
        // If it does, skip the insertion
        // To avoid duplicate entries in the database
        const char *selectQuery = "SELECT COUNT(*) FROM Inventory WHERE VIN = ?;";
        sqlite3_stmt *selectStmt;
        result = sqlite3_prepare_v2(db, selectQuery, -1, &selectStmt, nullptr);
        if (result != SQLITE_OK) {
            std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
        sqlite3_bind_text(selectStmt, 1, vehicle->getVIN().c_str(), -1, SQLITE_TRANSIENT);
        result = sqlite3_step(selectStmt);
        if (result != SQLITE_ROW) {
            std::cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(selectStmt);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
        int count = sqlite3_column_int(selectStmt, 0);
        sqlite3_finalize(selectStmt);

        // if count is 0, the vehicle with the same VIN does not exist in the database, so insert it
        if (count == 0) {

            sqlite3_bind_text(stmt, 1, vehicle->getManufacturer().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, vehicle->getModel().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, vehicle->getModelVariant().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 4, vehicle->getYear());
            sqlite3_bind_double(stmt, 5, vehicle->getPrice());
            sqlite3_bind_text(stmt, 6, vehicle->getVIN().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 7, vehicle->getColour().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 8, vehicle->getFuelType().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_double(stmt, 9, vehicle->getEngineSize());
            sqlite3_bind_text(stmt, 10, vehicle->getTransmissionType().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_double(stmt, 11, vehicle->getMileage());
            sqlite3_bind_text(stmt, 12, vehicle->getCondition().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 13, vehicle->getNumberOfPreviousOwners());
            sqlite3_bind_text(stmt, 14, vehicle->getDescription().c_str(), -1, SQLITE_TRANSIENT);

            if (auto carPtr = std::dynamic_pointer_cast<Car>(vehicle)) {
                sqlite3_bind_int(stmt, 15, carPtr->getNumberOfDoors());
                sqlite3_bind_text(stmt, 16, carPtr->getBodyStyle().c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_null(stmt, 17); // No value for NumberOfWheels for Car
            } else if (auto motorbikePtr = std::dynamic_pointer_cast<Motorbike>(vehicle)) {
                sqlite3_bind_null(stmt, 15); // No value for NumberOfDoors for Motorbike
                sqlite3_bind_null(stmt, 16); // No value for BodyStyle for Motorbike
                sqlite3_bind_int(stmt, 17, motorbikePtr->getNumberOfWheels());
            } else {
                // unknown types
                sqlite3_bind_null(stmt, 15);
                sqlite3_bind_null(stmt, 16);
                sqlite3_bind_null(stmt, 17);
            }


            result = sqlite3_step(stmt);
            if (result != SQLITE_DONE) {
                std::cerr << "Error inserting data into table: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return;
            }


            sqlite3_reset(stmt);
        }
    }

}
void DatabaseHandler::loadInventory(const std::string& dbName, std::vector<std::shared_ptr<Vehicle>>& inventory) {
    sqlite3* db;
    int result = sqlite3_open(dbName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    const char* selectQuery = "SELECT * FROM Inventory;";

    sqlite3_stmt* stmt;
    result = sqlite3_prepare_v2(db, selectQuery, -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // get data from the result set
        std::string manufacturer = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string variant = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int year = sqlite3_column_int(stmt, 4);
        double price = sqlite3_column_double(stmt, 5);
        std::string vin = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        std::string colour = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        std::string fuelType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        double engineSize = sqlite3_column_double(stmt, 9);
        std::string transmissionType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
        double mileage = sqlite3_column_double(stmt, 11);
        std::string condition = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12));
        int numberOfPreviousOwners = sqlite3_column_int(stmt, 13);
        std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 14));

        // Check if Car specific columns are not null
        // If they are not null, create a Car object
        if (sqlite3_column_type(stmt, 15) != SQLITE_NULL && sqlite3_column_type(stmt, 16) != SQLITE_NULL) {
            int numberOfDoors = sqlite3_column_int(stmt, 15);
            std::string bodyStyle = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 16));

            inventory.push_back(std::make_shared<Car>(
                    "", manufacturer, model, variant, year, price, vin, colour, fuelType,
                    engineSize, transmissionType, mileage, condition, numberOfPreviousOwners,
                    description, numberOfDoors, bodyStyle));
        }
            // Check if Motorbike specific column is not null
            // If it is not null, create a Motorbike object
        else if (sqlite3_column_type(stmt, 17) != SQLITE_NULL) {
            int numberOfWheels = sqlite3_column_int(stmt, 17);

            inventory.push_back(std::make_shared<Motorbike>(
                    "", manufacturer, model, variant, year, price, vin, colour, fuelType,
                    engineSize, transmissionType, mileage, condition, numberOfPreviousOwners,
                    description, numberOfWheels));
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void DatabaseHandler::saveUsers(const std::string& dbName, const std::vector<std::shared_ptr<Human>>& users) {
    sqlite3* db;
    int result = sqlite3_open(dbName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // create table if not exists
    const char* createTableQuery =
            "CREATE TABLE IF NOT EXISTS Users ("
            "Username TEXT PRIMARY KEY,"
            "Password TEXT,"
            "Role TEXT"
            ");";

    result = sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error creating table: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Inserts users into the database
    const char* insertUserQuery =
            "INSERT OR IGNORE INTO Users (Username, Password, Role) "
            "VALUES (?, ?, ?);";

    sqlite3_stmt* stmt;
    result = sqlite3_prepare_v2(db, insertUserQuery, -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    for (const auto& user : users) {
        // Check if the user with the same username already exists in the database
        // If it does, skip the insertion
        const char* selectQuery = "SELECT COUNT(*) FROM Users WHERE Username = ?;";
        sqlite3_stmt* selectStmt;
        result = sqlite3_prepare_v2(db, selectQuery, -1, &selectStmt, nullptr);
        if (result != SQLITE_OK) {
            std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
        sqlite3_bind_text(selectStmt, 1, user->getUsername().c_str(), -1, SQLITE_TRANSIENT);
        result = sqlite3_step(selectStmt);
        if (result != SQLITE_ROW) {
            std::cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(selectStmt);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
        int count = sqlite3_column_int(selectStmt, 0);
        sqlite3_finalize(selectStmt);

        // If count is 0, the user with the same username does not exist in the database, so insert it
        if (count == 0) {
            // Bind parameters
            sqlite3_bind_text(stmt, 1, user->getUsername().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, user->getPassword().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, user->getRole().c_str(), -1, SQLITE_TRANSIENT);


            result = sqlite3_step(stmt);
            if (result != SQLITE_DONE) {
                std::cerr << "Error inserting data into table: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return;
            }


            sqlite3_reset(stmt);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void DatabaseHandler::loadUsers(const std::string& dbName, std::vector<std::shared_ptr<Human>>& users) {
    sqlite3* db;
    int result = sqlite3_open(dbName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    const char* selectQuery = "SELECT * FROM Users;";

    sqlite3_stmt* stmt;
    result = sqlite3_prepare_v2(db, selectQuery, -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Retrieve data
        std::string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        // Create a User object depending on the role
        if (role == "admin") {
            users.push_back(std::make_shared<Admin>(username, password));
        } else if (role == "employee") {
            users.push_back(std::make_shared<Employee>(username, password));
        } else if (role == "customer") {
            users.push_back(std::make_shared<Customer>(username, password));
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
