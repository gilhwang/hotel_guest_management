/*
 * Project Title: Hotel Booking System
 * Author: Gil Hwang
 * Start Date: AUG 10 2022
 */
#include "graphics.hpp"
#include "globals.hpp"
#include <curl/curl.h>
#include <iostream>

int main(int argc, char** argv) {
    bool success = loadData(dataFilePath);
    if (success) {
        draw_application(argc, argv);
        clearData();
    }

    return 0;
}



