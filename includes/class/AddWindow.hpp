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
    void on_info_response(int /* response_id*/);
    Gender getGenderSelected();
    Payment getPaymentSelected();

    /* Member widgets */
    // Basis
    Gtk::Grid m_grid;
    Gtk::HeaderBar m_header;
    Gtk::Label m_title;
    Gtk::InfoBar m_infobar;
    Gtk::Label m_label_error;

    // Names
    Gtk::Label m_label_first;
    Gtk::Entry m_entry_first;
    Gtk::Label m_label_last;
    Gtk::Entry m_entry_last;

    // Radio Button
    Gtk::Label m_label_gender;
    std::vector<Gtk::RadioButton*> m_radio_gender;
    std::vector<Gtk::RadioButton*> m_radio_payment;
    
    // Dates
    DateEntry m_entry_start;
    DateEntry m_entry_end;
    Gtk::Box m_box_gender;
    Gtk::Box m_box_payment;

    // Room column class
    class RoomColumns : public Gtk::TreeModel::ColumnRecord {
        public:
            RoomColumns() {add(m_col_num);}
            Gtk::TreeModelColumn<int> m_col_num;
    };   

    // Combo box
    Gtk::Label m_label_room;
    RoomColumns m_columns;
    Gtk::ComboBox m_room;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    // Buttons
    Gtk::Button m_button_add;
    Gtk::Button m_button_quit;

    // Constants
    const int GRID_MARGIN = 10;
    Glib::ustring c_addbutton_data = "button {background-image : image(green);}\
                                      button:hover {background-image: image(darkgreen);}\
                                      button:active {background-image: image(gray);}";
    Glib::ustring c_quitbutton_data = "button {background-image : image(gray);}\
                                       button:hover {background-image: image(darkgray);}\
                                       button:active {background-image: image(gray);}";
};