/**
 * File: GuestTreeView.hpp
 * Description: Header file for Guest tree view class
 * Reference: https://developer-old.gnome.org/gtkmm-tutorial/stable/sec-treeview-examples.html.en
 */
#pragma once

#include <gtkmm-3.0/gtkmm.h>
#include <vector>
#include "Customer.hpp"

/* Model columns class */
class ModelColumns : public Gtk::TreeModel::ColumnRecord {
public:
    ModelColumns() { add(m_col_first_name); 
                     add(m_col_last_name);
                     add(m_col_gender);
                     add(m_col_start_date);
                     add(m_col_end_date);
                     add(m_col_payment);
                     add(m_col_bold);}

    // Columns
    Gtk::TreeModelColumn<Glib::ustring> m_col_first_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_last_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_gender;
    Gtk::TreeModelColumn<Glib::ustring> m_col_start_date;
    Gtk::TreeModelColumn<Glib::ustring> m_col_end_date;
    Gtk::TreeModelColumn<Glib::ustring> m_col_payment;
    Gtk::TreeModelColumn<bool> m_col_bold;

    // Methods
    Gtk::TreeModelColumn<Glib::ustring> getColumn(int col);
};


/* Guest tree view class */
class GuestTreeView : public Gtk::TreeView {
public:
    // Constructor
    GuestTreeView();

    // Methods
    void addGuest(Customer* newCustomer);
    

protected:
    // Methods
    void on_cell_data(Gtk::CellRenderer* renderer,
                      const Gtk::TreeModel::iterator& iter);

    // Member variables
    Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
    ModelColumns m_columns;
    Gtk::TreeViewColumn m_first_column;

    // Constants
    const int FIRSTNAME_COL_WIDTH = 150;
    const int LASTNAME_COL_WIDTH = 150;
    const Glib::ustring ROOM_FONT = "Sans Bold 20";
    const Glib::ustring NORMAL_FONT = "Sans Normal 13";
    std::vector<Glib::ustring> c_titles = {"First Name",
                                           "Last Name",
                                           "Gender",
                                           "From",
                                           "To",
                                           "Payment"};
    std::vector<int> c_widths = {150,
                                 150,
                                 100,
                                 130,
                                 130,
                                 70};
};


