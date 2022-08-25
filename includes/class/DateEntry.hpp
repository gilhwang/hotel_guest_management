/**
 * DateEntry.hpp
 * 
 * Header file for Combobox with date dropdown menu class 
 */
#pragma once
#include <gtkmm-3.0/gtkmm.h>

class DateEntry : public Gtk::HBox {
public:
    // Constructor&Destructor
    DateEntry(Glib::ustring title, Gtk::Window* parent);
    virtual ~DateEntry();

    // Methods
    Gtk::Entry& getEntry();

protected:
    // Methods
    void on_button_clicked();
    bool on_entry_clicked(GdkEventButton* event);
    bool on_button_pressed(GdkEventButton* event);
    void on_day_select();
    void on_month_select();

    // Member widgets
    Gtk::Window* m_parent;
    Gtk::Label m_label;
    Gtk::Entry m_entry;
    Gtk::Button m_button;
    Gtk::Dialog* m_dialog;
    Gtk::Calendar* m_calendar;

    // Member variables
    bool m_month_changed = false;

    // Member constants
    Glib::ustring ENTRY_DEFAULT = "2022/8/24";
};
