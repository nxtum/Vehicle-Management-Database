//
// Created by mrtym on 30/12/2023.
//

#include "Employee.h"
#include "AuthenticationManager.h"

void Employee::roleMenu(Dealership &dealership, std::string &username, AuthenticationManager &manager) const {
    int choice;
    do {
        std::cout << "\nEmployee Menu\n";
        std::cout << "1. Add a new vehicle to inventory\n";
        std::cout << "2. Remove a vehicle from inventory\n";
        std::cout << "3. View all vehicles in inventory\n";
        std::cout << "4. View all sold vehicles\n";
        std::cout << "5. View users\n";
        std::cout << "6. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Adding a new vehicle to inventory...\n";
                dealership.addVehicleToInventory(username,dealership);
                dealership.saveToFile();
                break;
            case 2:
                // Remove a vehicle
                std::cout << "Removing a vehicle from inventory...\n";
                dealership.deleteVehicle(username, "admin");
                dealership.saveToFile();
                break;
            case 3:
                // View all vehicles
                std::cout << "Displaying all vehicles in inventory...\n";
                dealership.displayInventory();
                break;
            case 4:
                std::cout << "Displaying all sold vehicles in inventory...\n";
                dealership.displaySoldInventory();
                break;

            case 5:
                int viewChoice;
                std::cout << "Do you want to view all users (1) or users with a specific role (2)? Enter your choice: ";
                std::cin >> viewChoice;
                if (viewChoice == 1) {
                    manager.viewUsers(false, ""); // false indicates not to filter by role
                } else if (viewChoice == 2) {
                    std::string role;
                    std::cout << "Enter the role to filter by: ";
                    std::cin >> role;
                    manager.viewUsers(true, role); // true indicates to filter by role
                } else {
                    std::cout << "Invalid choice.\n";
                }
                break;
            case 6:
                // Logout
                std::cout << "Logging out...\n";
                return;
            default:
                std::cout << "Invalid choice. Please enter a valid number.\n";
        }
    } while (true);
}
