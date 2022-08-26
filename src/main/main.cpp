/*
 * Project Title: Hotel Booking System
 * Author: Gil Hwang
 * Start Date: AUG 10 2022
 */

#include <gtk/gtk.h>
#include <iostream>
#include "graphics.hpp"
#include "globals.hpp"
#include <gtkmm-3.0/gtkmm.h>

int main(int argc, char** argv) {
    bool success = loadData(dataFilePath);
    if (success)
        draw_application(argc, argv);

    return 0;
}



