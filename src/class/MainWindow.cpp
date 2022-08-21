/*
 * File: MainWindow.cpp
 * Description: Implementation of Main window class
 */
#include "MainWindow.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include "AddWindow.hpp"

/* Constructor */
MainWindow::MainWindow() :
m_box(Gtk::ORIENTATION_HORIZONTAL, 0),
m_separator(Gtk::ORIENTATION_VERTICAL),
m_topbox(Gtk::ORIENTATION_HORIZONTAL),
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
    // Set buttons
    m_button_quit.set_halign(Gtk::ALIGN_START);
    m_button_quit.set_valign(Gtk::ALIGN_END);

    m_button_add.set_halign(Gtk::ALIGN_END);
    m_button_add.set_valign(Gtk::ALIGN_END);
    m_button_add.set_image_from_icon_name("list-add");
    m_button_add.set_always_show_image(TRUE);
    m_button_add.set_label("Check In");

    // Set box
    m_topbox.set_margin_left(TOPBOX_MARGIN);
    m_topbox.set_margin_bottom(TOPBOX_MARGIN);
    m_topbox.set_margin_right(TOPBOX_MARGIN);
    m_topbox.pack_start(m_button_quit);
    m_topbox.pack_start(m_button_add);

    // Connect button signal
    m_button_quit.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::close));
    m_button_add.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_add_button_clicked));

    // Set overlay
    m_overlay.add_overlay(m_topbox);
    m_overlay.set_overlay_pass_through(m_topbox, TRUE);
    add(m_overlay);

    // Set pop-up window
    m_add_window = nullptr;

    // Display widgets
    show_all_children();
}


/* Destructor */
MainWindow::~MainWindow()
{}


/* Add button signal handler */
void MainWindow::on_add_button_clicked() {
    // Check if add guest window is opened
    if (m_add_window) 
        return;

    // Open pop up window
    m_add_window = new AddWindow();
    m_add_window->set_modal(TRUE);
    m_add_window->set_transient_for(*this);
    m_add_window->signal_hide().connect(sigc::mem_fun(*this, &MainWindow::on_add_window_closed));
    m_add_window->show();
}


/* Handler when add pop  */
void MainWindow::on_add_window_closed() {
    if (m_add_window) {
        delete m_add_window;
        m_add_window = nullptr;
    }
}

#include <iostream>
void MainWindow::refresh() {
    
}