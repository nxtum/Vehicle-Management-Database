#include "Admin.h"

void Admin::roleMenu(Dealership& dealership, std::string& username, AuthenticationManager& authManager) const {
    int choice;
    std::string newEmployeeUsername, newEmployeePassword;

    do {
        UtilityFunctions::clearScreen();
        std::cout << "\nAdmin Menu\n";
        std::cout << "1. Add a new vehicle to inventory\n";
        std::cout << "2. Remove a vehicle from inventory\n";
        std::cout << "3. View all vehicles in inventory\n";
        std::cout << "4. View all sold vehicles\n";
        std::cout << "5. Create an employee\n";
        std::cout << "6. View users\n";
        std::cout << "7. Save to file\n";
        std::cout << "8. Load from file\n";
        std::cout << "9. Log out\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Adding a new vehicle to inventory...\n";
                UtilityFunctions::clearScreen();
                dealership.addVehicleToInventory(username, dealership);
                dealership.saveToFile();
                break;
            case 2:
                std::cout << "Removing a vehicle from inventory...\n";
                UtilityFunctions::clearScreen();
                dealership.deleteVehicle(username, "admin");
                dealership.saveToFile();
                break;
            case 3:
                std::cout << "Displaying all vehicles in inventory...\n";
                UtilityFunctions::clearScreen();
                dealership.displayInventory();
                break;
            case 4:
                std::cout << "Displaying all sold vehicles in inventory...\n";
                UtilityFunctions::clearScreen();
                dealership.displaySoldInventory();
                break;
            case 5:
                UtilityFunctions::clearScreen();
                createEmployee(authManager, dealership);
                break;
            case 6:
                int viewChoice;
                UtilityFunctions::clearScreen();
                std::cout << "Do you want to view all users (1) or users with a specific role (2)? Enter your choice: ";
                std::cin >> viewChoice;
                if (viewChoice == 1) {
                    authManager.viewUsers(false, ""); // false indicates not to filter by role
                } else if (viewChoice == 2) {
                    std::string role;
                    std::cout << "Enter the role to filter by: ";
                    std::cin >> role;
                    authManager.viewUsers(true, role); // true indicates to filter by role
                } else {
                    std::cout << "Invalid choice.\n";
                }
                break;
            case 7:
                UtilityFunctions::clearScreen();
                dealership.saveToFile();
                authManager.saveUsers("users.db");
                break;
            case 8:
                UtilityFunctions::clearScreen();
                dealership.loadFromFile("inventory.db", "sold_inventory.db");
                break;
            case 9:
                std::cout << "Logging out...\n";
                return;
            default:

                std::cout << "Invalid choice. Please enter a valid number.\n";
                UtilityFunctions::clearScreen();
        }
    } while (true);
}

void Admin::createEmployee(AuthenticationManager& authManager, Dealership& dealership) const {

    // functions creates a new employee by registering them with the AuthenticationManager

    std::string username, password;

    std::cout << "Enter the username for the new employee: ";
    std::cin >> username;
    std::cout << "Enter the password for the new employee: ";
    std::cin >> password;

    // Get the username of the current admin user
    std::string adminUsername = getUsername();

      // Register the new employee using the AuthenticationManager
    if (authManager.registerUser(username, password, "employee")) {
        std::cout << "Employee created successfully.\n";
        // Log back in automatically
    } else {
        std::cout << "Failed to create employee. Please try again.\n";
    }
}



