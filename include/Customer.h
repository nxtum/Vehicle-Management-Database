#ifndef MANAGEMENT_SYSTEM_CUSTOMER_H
#define MANAGEMENT_SYSTEM_CUSTOMER_H

#include <iostream>
#include "Human.h"
#include "Dealership.h"
#include "AuthenticationManager.h"

class Customer : public Human {
public:
    Customer(const std::string& username, const std::string& password) : Human(username, password, "customer") {}

    void roleMenu(Dealership &dealership, std::string &username, AuthenticationManager &authManager) const override;

};

#endif //MANAGEMENT_SYSTEM_CUSTOMER_H
