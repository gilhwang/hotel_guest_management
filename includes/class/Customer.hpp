/*
 * File: Customer.hpp
 * Description: Definition of customer class
 */

#pragma once

#include <string>
#include "helper.hpp"
#include "CustomerInfo.hpp"
#include <fstream>

class Customer {
private:
    std::string firstName, lastName;
    Gender gen;
    CustomerInfo info;

public:
    // Constructors
    Customer();
    Customer(std::string first, std::string last, Gender g);
    Customer(std::string first, std::string last, Gender g, CustomerInfo inf);

    // Methods
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getName() const;
    std::string getGenderString() const;
    CustomerInfo getInfo() const;
    std::string createOutput() const;
    std::string createOutputNew() const;
    std::string getOutput() const;

    void setFirstName(std::string first);
    void setLastName(std::string last);
    void setName(std::string first, std::string last);

    // Operators
    Customer operator=(const Customer& rhs);
    bool operator==(const Customer& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Customer& obj);
};