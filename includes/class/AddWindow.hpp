/**
 * File: AddWindow.hpp
 * Description: Header file for window class for adding guest
 */
#pragma once
#include <gtkmm-3.0/gtkmm.h>
#include <vector>
#include "DateEntry.hpp"
#include "Date.hpp"
#include "helper.hpp"

class AddWindow : public Gtk::Window {
public:
    AddWindow();
    virtual ~AddWindow();

protected:
    // Methods
    void on_quit_button_clicked();
    void on_add_button_clicked();
    Gender getGender();
    Payment getPayment();

    // Member widgets
    Gtk::Grid m_grid;
    Gtk::HeaderBar m_header;
    Gtk::Label m_title;

    Gtk::Label m_label_first;
    Gtk::Entry m_entry_first;
    Gtk::Label m_label_last;
    Gtk::Entry m_entry_last;
    Gtk::Label m_label_gender;
    std::vector<Gtk::RadioButton*> m_radio_gender;
    std::vector<Gtk::RadioButton*> m_radio_payment;
    DateEntry m_entry_start;
    DateEntry m_entry_end;
    Gtk::Box m_box_radio;
    Gtk::Box m_box_payment;

    Gtk::Button m_button_add;
    Gtk::Button m_button_quit;

    // Constants
    const int GRID_MARGIN = 10;
};