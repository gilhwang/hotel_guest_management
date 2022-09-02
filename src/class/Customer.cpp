/*
 * File: Customer.cpp
 * Description: Implementation of Customer class methods
 */

#include "Customer.hpp"
#include <iostream>
#include <fstream>
#include <gtkmm-3.0/gtkmm.h>
#include "globals.hpp"
#include "helper.hpp"

/*
 * Constructors
 */
// Default Constructor
Customer::Customer()
: info() 
{
    firstName = "";
    lastName = "";
    gen = Gender::unselected;
}

// Personal Info Constructor
Customer::Customer(std::string first, std::string last, Gender g) 
: info()
{
    firstName = first;
    lastName = last;
    gen = g;
}

// Full Info Constructor
Customer::Customer(std::string first, std::string last, Gender g, CustomerInfo inf){
    firstName = first;
    lastName = last;
    gen = g;
    info = inf;
}


/*
 * Getters&Setters
 */
// Get first name
std::string Customer::getFirstName() const {
    return firstName;
}

// Get last name
std::string Customer::getLastName() const {
    return lastName;
}

// Get full name
std::string Customer::getName() const {
    return firstName + " " + lastName;
}

// Get gender as string
std::string Customer::getGenderString() const {
    int gender = static_cast<int>(gen);
    return GENDER_STRING.at(gender);
}

// Get detailed info
CustomerInfo Customer::getInfo() const {
    return info;
}

// Set first name
void Customer::setFirstName(std::string first) {
    firstName = first;
}

// Set last name
void Customer::setLastName(std::string last) {
    lastName = last;
}

// Set full name
void Customer::setName(std::string first, std::string last) {
    firstName = first;
    lastName = last;
}

// Set gender
void Customer::setGender(Glib::ustring data) {
    for (int i = 0; i < GENDER_STRING.size(); i++) {
        if (data == GENDER_STRING[i])
            gen = static_cast<Gender>(i);
    }
}

// Set payment method
void Customer::setPayment(Glib::ustring data) {
    for (int i = 0; i < PAYMENT_STRING.size(); i++) {
        if (data == PAYMENT_STRING[i])
            info.payMethod = static_cast<Payment>(i);
    }
}


/* Update customer info based on model column */
void Customer::updateInfo(CustomerProperty property, Glib::ustring data) {
    switch (property) {
        case CustomerProperty::firstName:
            firstName = data;
            return;
        case CustomerProperty::lastName:
            lastName = data;
            return;
        case CustomerProperty::gender:
            setGender(data);
            return;
        case CustomerProperty::startDate:
            info.startDate.setDate(data);
            return;
        case CustomerProperty::endDate:
            info.endDate.setDate(data);
            return;
        case CustomerProperty::payMethod:
            setPayment(data);
            return;
        default: return;
    }
}


/* Create line for output to file */
std::string Customer::createOutput() const {
    return "\n" + 
           firstName + "," +
           lastName + "," +
           std::to_string(static_cast<int>(gen)) + "," +
           std::to_string(info.roomNumber) + "," +
           info.startDate.getString() + "," +
           info.endDate.getString() + "," +
           std::to_string(static_cast<int>(info.payMethod));
}


/**
 * Create output line for new line 
 * This does not skip line in the beginning
 */
std::string Customer::createOutputNew() const {
    return getOutput();
}


/* Get output line within the file */
std::string Customer::getOutput() const {
    return firstName + "," +
           lastName + "," +
           std::to_string(static_cast<int>(gen)) + "," +
           std::to_string(info.roomNumber) + "," +
           info.startDate.getString() + "," +
           info.endDate.getString() + "," +
           std::to_string(static_cast<int>(info.payMethod));
}



/*
 * Operators
 */
// Operator=
Customer Customer::operator=(const Customer& rhs){
    firstName = rhs.firstName;
    lastName = rhs.lastName;
    gen = rhs.gen;
    info = rhs.info;

    return (*this);
}


// Operator<<
std::ostream& operator<<(std::ostream& os, const Customer& obj){
    os << obj.firstName << "|" << obj.lastName << "|"
       << GENDER_STRING[static_cast<int>(obj.gen)] << "|" << obj.info;
    return os;
}




