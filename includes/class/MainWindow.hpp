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

    // Getters
    GuestStack* getStack();

protected:
    // Methods
    void on_add_button_clicked();
    void on_add_window_closed();
    void on_room_button_clicked();
    void on_pop_button_clicked();
    void on_info_response(int /*response_id*/);

    /* Member widgets */
    Gtk::Overlay m_overlay;

    // Layer 1
    Gtk::HeaderBar m_header;
    Gtk::Box m_box;
    Gtk::StackSidebar m_sidebar;
    GuestStack m_stack;
    Gtk::VBox m_box_stack;
    Gtk::Separator m_separator;
    Gtk::InfoBar m_infobar;
    Gtk::Label m_label_info;

    // Layer 2
    Gtk::Box m_topbox;
    Gtk::VBox m_leftbox;
    Gtk::VBox m_rightbox;
    Gtk::Button m_button_quit;
    Gtk::Button m_button_checkin;
    Gtk::Button m_button_room;
    AddWindow* m_add_window;

    // Popover
    Gtk::Popover m_popover;
    Gtk::VBox m_box_popover;
    Gtk::Label m_label_popover;
    Gtk::Entry m_entry_popover;
    Gtk::Button m_button_popover;

    // Constants
    const int TOPBOX_MARGIN = 10;
    const int RIGHTBOX_SPACING = 10;
};
