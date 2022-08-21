/*
 * File: MainWindow.cpp
 * Description: Implementation of Main window class
 */
#include "MainWindow.hpp"
#include <gtkmm-3.0/gtkmm.h>

/* Constructor */
MainWindow::MainWindow() :
m_box(Gtk::ORIENTATION_HORIZONTAL, 0),
m_separator(Gtk::ORIENTATION_VERTICAL),
m_topbox(Gtk::ORIENTATION_VERTICAL),
m_button_quit("Exit")
{
    /* Layer 1 */
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

    m_overlay.add_overlay(m_box);


    /* Layer 2 */
    // Set button & box on the top
    m_button_quit.set_halign(Gtk::ALIGN_START);
    m_button_quit.set_valign(Gtk::ALIGN_END);
    m_topbox.set_margin_left(10);
    m_topbox.set_margin_bottom(10);

    // Connect button signal
    m_button_quit.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::close));
    
    // Set overlay
    m_topbox.pack_end(m_button_quit);
    m_overlay.add_overlay(m_topbox);
    m_overlay.set_overlay_pass_through(m_topbox, TRUE);
    add(m_overlay);

    // Display widgets
    show_all_children();
}


/* Destructor */
MainWindow::~MainWindow()
{}