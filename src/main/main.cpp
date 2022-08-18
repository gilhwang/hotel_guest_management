/*
 * Project Title: Hotel Booking System
 * Author: Gil Hwang
 * Start Date: AUG 10 2022
 */

#include <gtk/gtk.h>
#include <iostream>
#include "Customer.hpp"
#include "graphics.hpp"

int main(int argc, char** argv) {
    bool success = loadCustomerData();
    if (success)
        initializeRoomData();
        draw_application(argc, argv);
    return 0;
}



