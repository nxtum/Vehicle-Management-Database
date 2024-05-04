#ifndef MANAGEMENT_SYSTEM_HUMAN_H
#define MANAGEMENT_SYSTEM_HUMAN_H

#include <string>
#include <iostream>

class Dealership;
class AuthenticationManager;

class Human {
    // class for the users of the system
private:
    std::string username;
    std::string password;
    std::string role;


public:
    virtual ~Human() = default;
    Human(const std::string &username, const std::string &password, const std::string &role)
            : username(username), password(password),
              role(role){}

    const std::string& getRole() const {
        return role;
    }



    const std::string& getUsername() const {
        return username;
    }

    const std::string& getPassword() const {
        return password;
    }
    virtual void roleMenu(Dealership &dealership, std::string &string, AuthenticationManager &authManager) const = 0;

    // each human has a role, and each role has a menu


};


#endif //MANAGEMENT_SYSTEM_HUMAN_H
