/*
 * File: helper.cpp
 * Description: Implementation of helper functions
 * Reference: gtk3-demo => Stack Slidebar & Treestore
 */
#include <gtk/gtk.h>
#include "helper.hpp"
#include "graphics.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include "Customer.hpp"
#include "globals.hpp"

/* Load Customer data from CSV file */
bool loadCustomerData() {
    // Open excel file
    std::ifstream dataFile;
    dataFile.open("../customerdata.csv");

    if (dataFile.is_open()) {
        printMessage("File opened successfully.");
    }
    else {
        printMessage("File was not opened due to unknown error!");
        return false;
    }

    // Store data in customer file
    customerData.clear();
    while (!dataFile.eof()) {
        // Retrieve data
        std::string data;

        getline(dataFile, data, ',');
        std::string firstName = data;

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
        CustomerInfo inf(nextGuestNum++, roomNumber, startDate, endDate, method);
        Customer customer(firstName, lastName, gen, inf);
        customerData.insert(std::make_pair(lastName, customer));
    }

    dataFile.close();
    return true;
}


/* Store room data based on customer data */
void initializeRoomData() {
    // Traverse through customer list
    roomData.clear();
    for (auto it=customerData.begin(); it != customerData.end(); it++) {
        // Retrieve current customer info
        Customer* currCustomer = &it->second;
        int guestNumber = currCustomer->getInfo().guestNumber;
        int roomNumber = currCustomer->getInfo().roomNumber;
        
        roomData[roomNumber][guestNumber] = currCustomer;
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
        if (s[i] < '1' || s[i] > '9')
            return false;
    }

    return true;
}
