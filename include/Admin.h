#ifndef MANAGEMENT_SYSTEM_ADMIN_H
#define MANAGEMENT_SYSTEM_ADMIN_H

#include "Human.h"
#include "AuthenticationManager.h"
#include "Dealership.h"
#include "UtilityFunctions.h"
#include <iostream>

class Admin : public Human {
public:
    Admin(const std::string& username, const std::string& password) : Human(username, password, "admin") {}

    void roleMenu(Dealership& dealership, std::string& username, AuthenticationManager& authManager) const override;
    void createEmployee(AuthenticationManager& authManager, Dealership& dealership)const;
};

#endif //MANAGEMENT_SYSTEM_ADMIN_H
