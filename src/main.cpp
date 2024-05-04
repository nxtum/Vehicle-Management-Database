#include "Dealership.h"
#include "AuthenticationManager.h"
#include "UtilityFunctions.h"
#include <iomanip>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

int getUserChoice();
int getTerminalWidth();
void printCentered(const std::string& text);

int displayMainMenu(AuthenticationManager& authManager, Dealership& dealership){
    //dealership.loadFromFile("inventory.db", "sold_inventory.db");
    //authManager.loadUsers("users.db");

    do {
        printCentered("Welcome to the dealership!");
        printCentered("To get started, please select a role:");
        printCentered("\n\n1. Log in as Admin");
        printCentered("\n2. Log in as Employee");
        printCentered("\n3. Log in as Customer");
        printCentered("\n4. Register as Customer");
        printCentered("\n5. Exit");

        int userChoice = getUserChoice();
        std::string selectedRole;

        switch (userChoice) {
            case 1:
                selectedRole = "admin";
                break;
            case 2:
                selectedRole = "employee";
                break;
            case 3:
                selectedRole = "customer";
                break;
            case 4: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (authManager.registerUser(username, password, "customer")) {
                    std::cout << "Registration successful. You can now log in.\n";
                } else {
                    std::cout << "Registration failed. Please try again.\n";
                }

                authManager.saveUsers("users.db");

                continue;

            }
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a valid number.\n";
                continue;
        }



        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        auto [loginSuccessful, loggedInUser] = authManager.login(username, password, selectedRole);

        if (loginSuccessful && loggedInUser) {
            loggedInUser->roleMenu(dealership, username, authManager);
        }

    } while (true);
}

int main() {
    AuthenticationManager authManager;
    Dealership dealership;


    authManager.registerUser("admin", "adminpass", "admin");
    authManager.registerUser("employee", "employeepass", "employee");
    authManager.registerUser("customer", "customerpass", "customer");


    UtilityFunctions::clearScreen();
    displayMainMenu(authManager, dealership);

    return 0;
}

int getUserChoice() {
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}

int getTerminalWidth() {
#ifdef _WIN32
CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
#endif
}

void printCentered(const std::string& text) {
    int terminalWidth = getTerminalWidth();
    int padding = (terminalWidth - text.length()) / 2;
    std::cout << std::setw(padding + text.length()) << std::right << text << std::endl;
}