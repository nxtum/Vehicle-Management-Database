
#ifndef MANAGEMENT_SYSTEM_EMPLOYEE_H
#define MANAGEMENT_SYSTEM_EMPLOYEE_H


#include "Human.h"
#include <iostream>
#include "AuthenticationManager.h"

class Employee : public Human {
public:
    Employee(const std::string& username, const std::string& password) : Human(username, password, "employee") {}
    void roleMenu(Dealership &dealership, std::string &string, AuthenticationManager &authManager) const override;
};


#endif //MANAGEMENT_SYSTEM_EMPLOYEE_H
