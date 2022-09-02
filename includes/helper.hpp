/*
 * Title: helper.cpp
 * Description: Header file for helper functions
 */

#pragma once

#include "Date.hpp"
#include <gtk/gtk.h>
#include <string>
#include <map>


/* Structs */
typedef struct {
    GtkWidget* id;
    GtkWidget* pw;
    gboolean success;
} Entries;


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
bool gchar_equals(const gchar* lhs, const gchar* rhs);
void printMessage(std::string message);
bool isInteger(std::string s);