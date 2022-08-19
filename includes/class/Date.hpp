/*
 * File: Date.hpp
 * Descripton: Definition of Date class
 */

#pragma once

#include <iostream>

class Date{
private:
    int day, month, year;

public:
    // Constructors
    Date();
    Date(int d, int m, int y);
    Date(std::string& src);
    Date(Date& src);

    // Methods
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    std::string getString() const;

    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    void print() const;

    // Operators
    Date operator=(const Date& rhs);
    bool operator==(const Date& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Date& obj);
};