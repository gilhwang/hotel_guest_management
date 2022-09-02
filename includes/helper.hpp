/*
 * Title: helper.cpp
 * Description: Header file for helper functions
 */

#pragma once

#include "Date.hpp"
#include <string>
#include <map>

/* Enumerations */
// Gender 
enum class Gender{
    unselected = 0,
    male,
    female,
    other
};

// Payment method 
enum class Payment{
    unselected = 0,
    unpaid,
    cash,
    creditcard,
    other
};

// Customer properyty
enum class CustomerProperty {
    firstName = 0,
    lastName,
    gender,
    startDate,
    endDate,
    payMethod,
    unselected
};

/* Data management */
bool loadData(const char* path);
void appendToFile(const char* path, std::string data);
void deleteInFile(const char* path, std::string data);
void clearData();

/* Helper functions */
void printMessage(std::string message);
bool isInteger(std::string s);