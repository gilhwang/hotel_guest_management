/* 
 * File: graphics.hpp
 * Description: Header file for graphics-related functions
 */

#pragma once

#include <gtkmm-3.0/gtkmm.h>
#include "MainWindow.hpp"

/* Draw window */
void draw_application (int argc, char** argv);
bool draw_login_screen();


/**
 * @brief Display dialog on top of window
 * 
 * @param parent parent window of the dialog
 * @param title  bolded message in dialog
 * @param message regular text inside dialog
 * @param messageType message type of dialog
 * @param buttonType buttons type of dialog
 * @return response id after running dialog
 */
bool displayDialog(Gtk::Window* parent, Glib::ustring title, Glib::ustring message, 
                   Gtk::MessageType messageType, Gtk::ButtonsType buttonType);