#include "AuthenticationManager.h"

AuthenticationManager::AuthenticationManager() {
    allowedRoles = {"admin", "employee", "customer"};
}

bool AuthenticationManager::registerUser(const std::string& username, const std::string& password, const std::string& role) {
    if (isUsernameTaken(username)) {
        std::cout << "Username already exists. Please choose a different username.\n";
        return false;
    }

    // New user created by calling constructor of the appropriate class
    // and stored in a shared_ptr of users

    std::shared_ptr<Human> newUser;
    if (isValidRole(role)) {
        if (role == "admin") {
            newUser = std::make_shared<Admin>(username, password);
        } else if (role == "employee") {
            newUser = std::make_shared<Employee>(username, password);
        } else if (role == "customer") {
            newUser = std::make_shared<Customer>(username, password);
        }
        users.push_back(newUser);
        std::cout << "User registered successfully.\n";
        return true;
    } else {
        std::cout << "Invalid role. Please choose a valid role.\n";
        return false;
    }
}

std::pair<bool, std::shared_ptr<Human>> AuthenticationManager::login(const std::string& username, const std::string& password, const std::string& role) {

    // functions returns a pair of bool and shared_ptr<Human>
    // bool indicates if the login was successful
    // shared_ptr<Human> is the user that logged in

    if (!isValidRole(role)) {
        std::cout << "Invalid role. Please enter a valid role.\n";
        return {false, nullptr};
    }

    // Find the user with the given username and role
    auto it = std::find_if(users.begin(), users.end(), [username, role](const auto& user) {
        return user->getUsername() == username && user->getRole() == role;
    });

    if (it != users.end()) {
        if ((*it)->getPassword() == password) {
            std::cout << "Login successful. Role: " << (*it)->getRole() << "\n";
            loggedInUser = *it; // No need for std::move
            return {true, loggedInUser}; // Return the loggedInUser as a shared_ptr
        } else {
            std::cout << "Incorrect password.\n";
            return {false, nullptr}; // Incorrect password
        }
    } else {
        std::cout << "User not found.\n";
        return {false, nullptr}; // User not found
    }
}




void AuthenticationManager::viewUsers(bool filterByRole, const std::string& role) const {

    // function to display all users or users with a specific role

    if (filterByRole) {
        std::cout << "Users with role '" << role << "':\n";
        for (const auto& user : users) {
            if (user && user->getRole() == role) {
                std::cout << "Username: " << user->getUsername() << ", Role: " << user->getRole() << "\n";
            }
        }
    } else {
        std::cout << "All users:\n";
        for (const auto& user : users) {
            if (user) {
                std::cout << "Username: " << user->getUsername() << ", Role: " << user->getRole() << "\n";
            }
        }
    }
}


bool AuthenticationManager::isUsernameTaken(const std::string& username) const {

    // search for a user with the given username

    return std::any_of(users.begin(), users.end(), [username](const auto& user) {
        return user->getUsername() == username;
    });
}

bool AuthenticationManager::isValidRole(const std::string& role) const {
    return std::find(allowedRoles.begin(), allowedRoles.end(), role) != allowedRoles.end();
}


void AuthenticationManager::loadUsers(const std::string &dbName) {
    DatabaseHandler::loadUsers(dbName, users);
}

void AuthenticationManager::saveUsers(const std::string &dbName) const
{
    DatabaseHandler::saveUsers(dbName, users);

}

