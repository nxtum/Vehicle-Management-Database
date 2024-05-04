#include "Customer.h"

void Customer::roleMenu(Dealership &dealership, std::string &username, AuthenticationManager &manager) const {
    int choice;
    do {
        std::cout << "\nCustomer Menu\n";
        std::cout << "1. Sell a Vehicle\n";
        std::cout << "2. Remove your listings\n";
        std::cout << "3. View all vehicles in inventory\n";
        std::cout << "4. Buy a vehicle\n";
        std::cout << "5. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Adding a new vehicle to inventory...\n";
                dealership.addVehicleToInventory(username, dealership);
                dealership.saveToFile();
                break;
            case 2:
                // Remove a vehicle
                std::cout << "Removing a vehicle from inventory...\n";
                dealership.deleteVehicle(username, "customer");
                dealership.saveToFile();
                break;
            case 3:
                // View all vehicles
                std::cout << "Displaying all vehicles in inventory...\n";
                dealership.displayInventory();
                break;
            case 4:
                dealership.buyVehicle();
                break;
            case 5:
                // Logout
                std::cout << "Logging out...\n";
                return;
            default:
                std::cout << "Invalid choice. Please enter a valid number.\n";
        }
    } while (true);
}
