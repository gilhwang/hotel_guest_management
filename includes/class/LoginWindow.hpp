/*
 * File: LoginWindow.hpp
 * Descprtion: Definition of Login window class
 */
#pragma once
#include <gtkmm-3.0/gtkmm.h>

/* Login window */
class LoginWindow : public Gtk::Window {
public:
    LoginWindow();
    virtual ~LoginWindow();

protected:
    /* Signal Handlers */
    void on_button_clicked();
    bool on_keyboard_released(GdkEventKey* event);

    /* Member variables */
    // Login Screen
    Gtk::VBox m_vbox;
    Gtk::Label m_label;
    Gtk::Label m_id_label;
    Gtk::Label m_pw_label;
    Gtk::HBox m_id_hbox;
    Gtk::HBox m_pw_hbox;
    Gtk::Entry m_id_entry;
    Gtk::Entry m_pw_entry;
    Gtk::Button m_button;

    // Popover
    Gtk::Popover m_popover;
    Gtk::Label m_popover_label;
};