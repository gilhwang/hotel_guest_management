/**
 * File: GuestTreeView.hpp
 * Description: Header file for Guest tree view class
 * Reference: https://developer-old.gnome.org/gtkmm-tutorial/stable/sec-treeview-examples.html.en
 */
#pragma once

#include <gtkmm-3.0/gtkmm.h>

/* Model columns class */
class ModelColumns : public Gtk::TreeModel::ColumnRecord {
public:
    ModelColumns() { add(m_col_first_name); 
                     add(m_col_last_name);
                     add(m_col_gender);
                     add(m_col_start_date);
                     add(m_col_end_date);
                     add(m_col_payment);}

    // Columns
    Gtk::TreeModelColumn<Glib::ustring> m_col_first_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_last_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_gender;
    Gtk::TreeModelColumn<Glib::ustring> m_col_start_date;
    Gtk::TreeModelColumn<Glib::ustring> m_col_end_date;
    Gtk::TreeModelColumn<Glib::ustring> m_col_payment;

};


/* Guest tree view class */
class GuestTreeView : public Gtk::TreeView {
public:
    GuestTreeView();

protected:
    // Member variables
    Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
    ModelColumns m_columns;
};


