/*
 * File: Date.cpp
 * Description: Implmentation of Date class methods
 */

#include "Date.hpp"

#include <iostream>
#include <string>
#include <sstream>

/*
 * Constructors
 */

// Default Constructor
Date::Date(){
    day = 24;
    month = 8;
    year = 2022;
}

// int Constructor
Date::Date(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

// String Constructor
Date::Date(const std::string& src) {
    // Local Variables
    std::stringstream ss(src);
    std::string data;

    getline(ss, data, '/');
    year = stoi(data);
    getline(ss, data, '/');
    month = stoi(data);
    ss >> data;
    day = stoi(data);
}

// Copy Constructor
Date::Date(Date& src) {
    day = src.day;
    month = src.month;
    year = src.year;
}

/*
 * Getter methods:
 * day, month, year
 */
int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

std::string Date::getString() const {
    return (std::to_string(year) + "/" +
            std::to_string(month) + "/" +
            std::to_string(day));
}


/*
 * Setter methods:
 * day, month, year
 */
void Date::setDay(int d) {
    day = d;
}

void Date::setMonth(int m) {
    month = m;
}

void Date::setYear(int y ){
    year = y;
}

void Date::setDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}


// Print date object
void Date::print() const {
    std::cout << year << "/" << month << "/" << day << std::endl;
}

/*
 * Operators
 */

// Operator=
Date Date::operator=(const Date& rhs) {
    day = rhs.day;
    month = rhs.month;
    year = rhs.year;

    return (*this);
}

// Operator==
bool Date::operator==(const Date& rhs) {
    if (day == rhs.day &&
        month == rhs.month &&
        year == rhs.year){
        return true;
    }
    return false;
}

// << Operator
std::ostream& operator<<(std::ostream& os, const Date& obj) {
    os << obj.year << "/" << obj.month << "/" << obj.day;
    return os;
}

// Operator <
bool Date::operator<(const Date& rhs) {
    // Check if the date is earlier than rhs
    if (year < rhs.year) 
        return true;
    else if (year == rhs.year) {
        if (month < rhs.month) 
            return true;
        else if (month == rhs.month && day < rhs.day)
            return true;
    }
    
    return false;
}

// Operator >
bool Date::operator>(const Date& rhs) {
    if (*this < rhs)
        return false;
    else if (*this == rhs)
        return false;
    else
        return true;
}