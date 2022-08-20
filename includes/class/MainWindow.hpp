/*
 * File: MainWindow.hpp
 * Description: Defintion of Main window class
 */
#pragma once

#include <gtkmm-3.0/gtkmm.h>
#include "GuestStack.hpp"

/* Main application window */
class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    /* Signal Handlers */
    void on_login_closed();

    /* Member widgets */
    Gtk::HeaderBar m_header;
    Gtk::Box m_box;
    Gtk::StackSidebar m_sidebar;
    GuestStack m_stack;
    Gtk::Separator m_separator;
};
