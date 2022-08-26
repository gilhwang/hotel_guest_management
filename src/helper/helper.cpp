/*
 * File: helper.cpp
 * Description: Implementation of helper functions
 * Reference: gtk3-demo => Stack Slidebar & Treestore
 */
#include <gtk/gtk.h>
#include "helper.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include "Customer.hpp"
#include "globals.hpp"

/* Load Customer data from file */
bool loadData(const char* path) {
    // Local Variables
    const std::string VOID_MARK = "\%void\%";
    
    // Open excel file
    std::ifstream dataFile;
    dataFile.open(path);

    if (dataFile.is_open()) {
        printMessage("File opened successfully.");
    }
    else {
        printMessage("File was not opened due to unknown error!");
        return false;
    }

    // Clear data before initializing
    customerData.clear();
    roomData.clear();

    // Read file line by line
    while (!dataFile.eof() && dataFile.peek() != '\n') {
        // Retrieve data
        std::string data;

        // Get first data
        // Could be first name or void mark
        getline(dataFile, data, ',');
        std::string firstName = data;

        // Found an empty room
        if (firstName == VOID_MARK) {
            getline(dataFile, data);
            int roomNumber = stoi(data);
            roomData.insert(make_pair(roomNumber, std::unordered_map<int,Customer*>()));
        }
        // Regular customer info
        else {
            getline(dataFile, data, ',');
            std::string lastName = data;
            
            getline(dataFile, data, ',');
            Gender gen = static_cast<Gender>(stoi(data));

            getline(dataFile, data, ',');
            int roomNumber = stoi(data);

            getline(dataFile, data, ',');
            Date startDate(data);

            getline(dataFile, data, ',');
            Date endDate(data);

            getline(dataFile, data);
            Payment method = static_cast<Payment>(stoi(data));

            // Store data
            CustomerInfo inf(nextGuestNum, roomNumber, startDate, endDate, method);
            Customer* customer = new Customer(firstName, lastName, gen, inf);
            customerData.insert(std::make_pair(lastName, customer));
            roomData[roomNumber][nextGuestNum++] = customer;
        }
    }

    dataFile.close();
    return true;
}


/* Append data to file */
void appendToFile(const char* path, std::string data) {
    // Open output file
    std::ofstream dataFile;
    dataFile.open(path, std::ios_base::app);
    dataFile << data;
}


/* Clear used data before exit */
void clearData() {
    for (auto it = customerData.begin(); it != customerData.end(); it++) {
        if (it->second)
            delete it->second;
    }
}


/* Print string to stdout */
void printMessage(std::string message) {
    std::cout << message << std::endl;
}


/* Check if string is integer */
bool isInteger(std::string s) {
    if (s.empty())
        return false;
    
    // Check if each char is number(0 - 9)
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }

    return true;
}
