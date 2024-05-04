#ifndef MANAGEMENT_SYSTEM_AUTHENTICATIONMANAGER_H
#define MANAGEMENT_SYSTEM_AUTHENTICATIONMANAGER_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "Human.h"
#include "Employee.h"
#include "Customer.h"
#include "Admin.h"

class AuthenticationManager {
private:
    std::vector<std::string> allowedRoles;
    std::vector<std::shared_ptr<Human>> users;
    std::shared_ptr<Human> loggedInUser;

    // TOFIX: Possibly
    // regarding shared_ptr, I think it's better to use unique_ptr instead of shared_ptr
    // but when a user is logged in, and I try to create a new instance of a user, I get a segmentation fault
    // due to the fact when I attempt to move a unique pointer that's already owned by the logged-in user
    // I get a segmentation fault, so I had to use shared_ptr instead of unique_ptr
    // I would need to "central admin" that's not part of the users vector


public:
    AuthenticationManager();

    bool registerUser(const std::string& username, const std::string& password, const std::string& role);
    std::pair<bool, std::shared_ptr<Human>> login(const std::string& username, const std::string& password , const std::string& role);

    void viewUsers(bool filterByRole, const std::string& role) const;
    bool isValidRole(const std::string& role) const;
    bool isUsernameTaken(const std::string& username) const;
    void loadUsers(const std::string& dbName);
    void saveUsers(const std::string& dbName) const;


};

#endif //MANAGEMENT_SYSTEM_AUTHENTICATIONMANAGER_H
