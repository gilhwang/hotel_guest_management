/*
 * File: graphics.cpp
 * Descriptoin: Implementation of graphics-related functions
 */
#include "graphics.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include "helper.hpp"
#include "events.hpp"
#include "globals.hpp"
#include <stdlib.h>
#include "LoginWindow.hpp"
#include "MainWindow.hpp"

/* Draws login screen */
bool draw_login_screen(){
    auto app = Gtk::Application::create("org.gtkmm.login");
    LoginWindow window;
    app->run(window);
    return window.loginSuccess;
}


/* Draws the GTK widgets */
void draw_application(int argc, char** argv){
    // Process Login before starting application
    bool success = draw_login_screen();

    if (success == false){
        return;
    }

    // Run main application
    auto app = Gtk::Application::create("org.gtkmm.main");
    MainWindow window;
    app->run(window);
}


/* Display dialog on top of window */
bool displayDialog(Gtk::Window* parent, Glib::ustring title, Glib::ustring message, 
                   Gtk::MessageType messageType, Gtk::ButtonsType buttonsType) {
    // Create dialog
    Gtk::MessageDialog dialog(*parent, title, false, messageType, buttonsType, false);
    dialog.set_secondary_text(message);
    return dialog.run();
}