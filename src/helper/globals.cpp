/**
 * File: globals.cpp
 * Description: Declaration of all global variables
 */
#include "globals.hpp"

/* Global Variables */
std::multimap<std::string, Customer*> customerData;
std::unordered_map<int, std::unordered_map<int,Customer*>> roomData;
int nextGuestNum = 0;
const char* dataFilePath = "../customerdata.csv";

/* Global Constants */
std::vector<std::string> GENDER_STRING = {"Unselected", "Male", "Female", "Preferred Not to Say"}; 
std::vector<std::string> PAYMENT_STRING = {"Unselected", "Unpaid", "Cash", "Credit Card", "Other"};