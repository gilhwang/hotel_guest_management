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

    // Declaration of data
    int column = 0;
    std::string data;
    std::string firstName, lastName;
    Gender gen;
    int roomNumber;
    Date startDate, endDate;
    Payment method;

    // Retrieve data from file
    while (getline(dataFile, data, ',')) {
        switch (column) {
            case 0: firstName = data;
                    column++;

                    // Found an empty room
                    if (firstName == VOID_MARK) {
                        getline(dataFile, data);
                        int roomNumber = stoi(data);
                        roomData.insert(make_pair(roomNumber, 
                                                  std::unordered_map<int,Customer*>()));
                        column = 0;
                    }
                    break;
            
            case 1: lastName = data; 
                    column++;
                    break;

            case 2: gen = static_cast<Gender>(stoi(data));
                    column++;
                    break;

            case 3: roomNumber = stoi(data);
                    column++;
                    break;

            case 4: startDate.setDate(data);
                    column++;
                    break;

            case 5: endDate.setDate(data);
                    
                    // Get last data
                    getline(dataFile, data);
                    method = static_cast<Payment>(stoi(data));
                    column++;

                    // Store data
                    CustomerInfo inf(nextGuestNum, roomNumber, startDate, endDate, method);
                    Customer* customer = new Customer(firstName, lastName, gen, inf);
                    customerData.insert(std::make_pair(lastName, customer));
                    roomData[roomNumber][nextGuestNum++] = customer;

                    column = 0;
                    break;
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


/**
 * Erase data in file
 * Reference: https://cplusplus.com/forum/general/12081/
 */
void deleteInFile(const char* path, std::string data) {
    // Open old and new files
    std::ifstream dataFile;
    std::ofstream temp;
    dataFile.open(path);
    const char* tempPath = "../tempFile.csv";
    temp.open(tempPath);

    // Remove particular line from file
    std::ofstream newFile;
    std::string line;
    while (getline(dataFile, line)) {
        // Re-add all lines except "to-be-deleted" line
        if (line != data) {
            temp << line << std::endl;
        }
    }

    // Replace old file with new file
    temp.close();
    dataFile.close();
    remove(path);
    rename(tempPath, path);
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
