/*
 * File: MainWindow.cpp
 * Description: Implementation of Main window class
 */
#include "MainWindow.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include "AddWindow.hpp"
#include "helper.hpp"

/* Constructor */
MainWindow::MainWindow() :
m_box(Gtk::ORIENTATION_HORIZONTAL, 0),
m_separator(Gtk::ORIENTATION_VERTICAL),
m_topbox(Gtk::ORIENTATION_HORIZONTAL),
m_leftbox(Gtk::ORIENTATION_VERTICAL),
m_rightbox(Gtk::ORIENTATION_VERTICAL),
m_button_quit("Exit"),
m_popover(m_button_room),
m_label_popover("Enter Room Number\n(in positive integer)"),
m_button_popover("Add"),
m_label_info("")
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

    // Set infobar
    m_infobar.add_button(Gtk::Stock::OK, 0);
    Gtk::Container* infoBarContainer = dynamic_cast<Gtk::Container*>(m_infobar.get_content_area());
    if (infoBarContainer)
        infoBarContainer->add(m_label_info);

    // Pack widgets
    m_box.pack_start(m_sidebar, FALSE, FALSE, 0);
    m_box.pack_start(m_separator, FALSE, FALSE, 0);
    m_box_stack.set_vexpand(true);
    m_box_stack.pack_start(m_infobar, FALSE, FALSE, 0);
    m_box_stack.pack_start(m_stack, TRUE, TRUE, 0);
    m_box.pack_start(m_box_stack, TRUE, TRUE, 0);
    m_overlay.add_overlay(m_box);

    /* Layer 2 */
    // Set quit button
    m_button_quit.set_halign(Gtk::ALIGN_START);
    m_button_quit.set_valign(Gtk::ALIGN_END);

    // Set add button
    m_button_checkin.set_halign(Gtk::ALIGN_END);
    m_button_checkin.set_valign(Gtk::ALIGN_END);
    m_button_checkin.set_image_from_icon_name("list-add");
    m_button_checkin.set_always_show_image(TRUE);
    m_button_checkin.set_label("Check In");

    // Set delete buttons
    m_button_room.set_halign(Gtk::ALIGN_END);
    m_button_room.set_valign(Gtk::ALIGN_END);
    m_button_room.set_image_from_icon_name("insert-object");
    m_button_room.set_always_show_image(TRUE);
    m_button_room.set_label("Add room");

    // Set left side box
    m_leftbox.set_valign(Gtk::Align::ALIGN_END);
    m_leftbox.pack_start(m_button_quit);

    // Set right side box
    m_rightbox.set_valign(Gtk::Align::ALIGN_END);
    m_rightbox.set_spacing(RIGHTBOX_SPACING);
    m_rightbox.pack_start(m_button_room);
    m_rightbox.pack_start(m_button_checkin);
    
    // Set Top level box
    m_topbox.set_margin_left(TOPBOX_MARGIN);
    m_topbox.set_margin_bottom(TOPBOX_MARGIN);
    m_topbox.set_margin_right(TOPBOX_MARGIN);
    m_topbox.pack_start(m_leftbox);
    m_topbox.pack_start(m_rightbox);

    // Set popover box
    m_box_popover.set_spacing(5);
    m_box_popover.pack_start(m_label_popover, FALSE, FALSE, 0);
    m_box_popover.pack_start(m_entry_popover, FALSE, FALSE, 0);
    m_box_popover.pack_start(m_button_popover, FALSE, FALSE, 0);
    m_box_popover.show();
    m_label_popover.show();
    m_entry_popover.show();
    m_button_popover.show();
    
    // Set popover
    m_popover.set_position(Gtk::POS_TOP);
    m_popover.set_border_width(10);
    m_popover.set_visible(false);
    m_popover.add(m_box_popover);

    // Connect button signal
    m_button_quit.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::close));
    m_button_checkin.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_add_button_clicked));
    m_button_room.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_room_button_clicked));
    m_button_popover.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_pop_button_clicked));
    m_infobar.signal_response().connect(sigc::mem_fun(*this, &MainWindow::on_info_response));

    // Set overlay
    m_overlay.add_overlay(m_topbox);
    m_overlay.set_overlay_pass_through(m_topbox, TRUE);
    add(m_overlay);

    // Set pop-up window
    m_add_window = nullptr;

    // Display widgets
    show_all_children();
    m_infobar.hide();
}


/* Destructor */
MainWindow::~MainWindow()
{}


/* Get protected member variables */
GuestStack* MainWindow::getStack() {
    return &m_stack;
}


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


/* Room button signal handler */
void MainWindow::on_room_button_clicked() {
    if (m_popover.get_visible())
        return;
    else
        m_popover.set_visible(true);
}


/* Popover button signal handler */
void MainWindow::on_pop_button_clicked() {
    // Local Variables
    std::string userInput = m_entry_popover.get_text();

    // Invalid input
    if (!isInteger(userInput)) {
        // Show error message in info bar
        m_popover.set_visible(false);
        m_label_info.set_text("Invalid Room Number! Please Try Again.");
        m_infobar.set_message_type(Gtk::MESSAGE_ERROR);
        m_infobar.show();
        m_popover.set_visible(false);
    }
    // Valid input
    else {
        m_stack.getTreeview()->addRoom(std::stoi(userInput));
        Glib::ustring message = "Room \"" + userInput + "\" added successfully!"; 
        m_label_info.set_text(message);
        m_infobar.set_message_type(Gtk::MESSAGE_INFO);
        m_infobar.show();
        m_popover.set_visible(false);
    }
}


/* Handler when add pop  */
void MainWindow::on_add_window_closed() {
    if (m_add_window) {
        delete m_add_window;
        m_add_window = nullptr;
    }
}


/* Info bar response signal handler */
void MainWindow::on_info_response(int /*response_id*/) {
    m_label_info.set_text("");
    m_infobar.hide();
}