/*
 * File: LoginWindow.cpp
 * Description: Implementation of Login window class
 */
#include "LoginWindow.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include <iostream>

/* Constructor */
LoginWindow::LoginWindow() 
: m_button("Login"), m_label("Please enter ID and password"),
  m_id_label("ID "), m_pw_label("PW"),
  m_vbox(Gtk::ORIENTATION_VERTICAL, 5),
  m_id_hbox(Gtk::ORIENTATION_HORIZONTAL, 5),
  m_pw_hbox(Gtk::ORIENTATION_HORIZONTAL, 5),
  m_popover(m_button), m_popover_label("Incorrect ID or PW!")
{
    // Set properties
    set_border_width(5);
    set_resizable(FALSE);
    set_default_size(300,100);
    set_title("Login");
    set_position(Gtk::WIN_POS_CENTER);

    /* Set children properties */
    // Boxes
    m_vbox.set_border_width(5);
    m_id_hbox.pack_start(m_id_label);
    m_id_hbox.pack_start(m_id_entry);
    m_pw_hbox.pack_start(m_pw_label);
    m_pw_hbox.pack_start(m_pw_entry);
    m_vbox.pack_start(m_label);
    m_vbox.pack_start(m_id_hbox);
    m_vbox.pack_start(m_pw_hbox);
    m_vbox.pack_start(m_button);

    // Popover
    m_popover.set_position(Gtk::POS_TOP);
    m_popover.set_border_width(6);
    m_popover.add(m_popover_label);
    m_popover_label.show();
    m_popover.set_visible(FALSE);

    // Keyboard
    add_events(Gdk::KEY_RELEASE_MASK);

    // Connect signals
    m_button.signal_clicked().connect(sigc::mem_fun(*this, 
                                      &LoginWindow::on_button_clicked));
    this->signal_key_release_event().connect(sigc::mem_fun(*this,
                                              &LoginWindow::on_keyboard_released), false);

    // Add children
    add(m_vbox);

    // Display widget
    show_all_children(); 
}


/* Destructor */
LoginWindow::~LoginWindow()
{}


/* Button Clicked signal handler */
void LoginWindow::on_button_clicked() {
    // Constants
    const Glib::ustring correctID = "admin";
    const Glib::ustring correctPW = "1";

    if (m_popover.get_visible()) {
        m_popover.set_visible(FALSE);
        return;
    }
    
    if (m_id_entry.get_text() == correctID &&
        m_pw_entry.get_text() == correctPW) {
        loginSuccess = true;
        close();
    }
    else {
        m_popover.set_visible(TRUE);
    }
}


/* Keyboard release signal handler */
bool LoginWindow::on_keyboard_released(GdkEventKey* event) {
    if (event->keyval == GDK_KEY_Return) {
        on_button_clicked();
        return false;
    }
    
    return false;
}