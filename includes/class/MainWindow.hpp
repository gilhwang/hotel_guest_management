/*
 * File: MainWindow.hpp
 * Description: Defintion of Main window class
 */
#pragma once

#include <gtkmm-3.0/gtkmm.h>

/* Main application window */
class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    /* Signal Handlers */
    void on_login_closed();

    /* Member variables */
    Gtk::Window m_login;
};
