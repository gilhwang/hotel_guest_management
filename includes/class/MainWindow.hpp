/*
 * File: MainWindow.hpp
 * Description: Defintion of Main window class
 */
#pragma once

#include <gtkmm-3.0/gtkmm.h>
#include "GuestStack.hpp"
#include "AddWindow.hpp"

/* Main application window */
class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();

    void refresh();

protected:
    // Methods
    void on_add_button_clicked();
    void on_add_window_closed();

    /* Member widgets */
    Gtk::Overlay m_overlay;

    // Layer 1
    Gtk::HeaderBar m_header;
    Gtk::Box m_box;
    Gtk::StackSidebar m_sidebar;
    GuestStack m_stack;
    Gtk::Separator m_separator;

    // Layer 2
    Gtk::Box m_topbox;
    Gtk::Button m_button_quit;
    Gtk::Button m_button_add;
    AddWindow* m_add_window;

    // Constants
    const int TOPBOX_MARGIN = 10;
};
