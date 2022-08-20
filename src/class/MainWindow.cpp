/*
 * File: MainWindow.cpp
 * Description: Implementation of Main window class
 */
#include "MainWindow.hpp"
#include <gtkmm-3.0/gtkmm.h>

/* Constructor */
MainWindow::MainWindow() :
m_box(Gtk::ORIENTATION_HORIZONTAL, 0),
m_separator(Gtk::ORIENTATION_VERTICAL)
{
    // Set header properties
    m_header.set_show_close_button(TRUE);

    // Set window properties
    set_resizable(TRUE);
    set_position(Gtk::WIN_POS_CENTER);
    set_default_size(1000, 700);
    set_titlebar(m_header);
    set_title("Hotel Guest Management");

    // Set stack properties
    m_sidebar.set_stack(m_stack);

    // Pack widgets
    m_box.pack_start(m_sidebar, FALSE, FALSE, 0);
    m_box.pack_start(m_separator, FALSE, FALSE, 0);
    m_box.pack_start(m_stack, TRUE, TRUE, 0);
    add(m_box);

    // Display widgets
    show_all_children();
}


/* Destructor */
MainWindow::~MainWindow()
{}


/*
 * Signal Handlers
 */

/* Login window closed */
void on_login_closed() {

}