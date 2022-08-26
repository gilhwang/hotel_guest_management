/*
 * File: globals.hpp
 * Description: Declaration of global variables
 */

#pragma once
#include <map>
#include <unordered_map>
#include "Customer.hpp"
#include <vector>
#include <string>

/* Containers */
extern std::multimap<std::string, Customer> customerData;
extern std::unordered_map<int, std::unordered_map<int, Customer*>> roomData;
extern int nextGuestNum;
extern const char* dataFilePath;

/* Constants */
extern std::vector<std::string> GENDER_STRING; 
extern std::vector<std::string> PAYMENT_STRING;