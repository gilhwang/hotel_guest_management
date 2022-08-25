/**
 * DateEntry.cpp
 * 
 * Implementation of DateEntry class
 */
#include "DateEntry.hpp"
#include <gtkmm-3.0/gtkmm.h>

/**
 * Constructor 
 * Reference: https://www.kksou.com/php-gtk2/sample-codes/setup-a-pulldown-calendar-for-date-selection.php
 */
DateEntry::DateEntry(Glib::ustring title, Gtk::Window* parent) 
: m_button(".."), 
  m_label(title),
  m_dialog(nullptr),
  m_calendar(nullptr)
{
    // Set widget
    m_parent = parent;
    m_entry.set_text(ENTRY_DEFAULT);

    // Pack widgets
    pack_start(m_label, 0, 0);
    pack_start(m_entry, 0, 0);
    pack_start(m_button, 0, 0);

    // Connect signals
    add_events(Gdk::BUTTON_PRESS_MASK);
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &DateEntry::on_button_clicked));
    m_entry.signal_button_press_event().connect(sigc::mem_fun(*this, &DateEntry::on_entry_clicked), false);
}


/* Destructor */
DateEntry::~DateEntry() {
    // Clear pointer data
    if (m_calendar) {
        delete m_calendar;
        m_calendar = nullptr;
    }
}


/* Return entry */
Gtk::Entry& DateEntry::getEntry() {
    return m_entry;
}


/* Entry click signal handler */
bool DateEntry::on_entry_clicked(GdkEventButton* event) {
    on_button_clicked();
    return false;
}


/* Button click signal handler */
void DateEntry::on_button_clicked() {
    // Get pop-up window location
    int entryX = m_entry.get_allocation().get_x();
    int entryY = m_entry.get_allocation().get_y();
    int xShift = 4;
    int yShift = 23 + m_entry.get_allocation().get_height();

    // Determine x, y position
    int x = entryX + xShift;
    int y = entryY + yShift;

    // Set new pop-up window
    m_dialog = new Gtk::Dialog("Choose Date", true);
    m_dialog->set_decorated(false);
    m_dialog->set_default_size(100, 100);
    m_dialog->get_action_area()->set_size_request(-1, 0);
    m_dialog->set_attached_to(m_entry);
    m_dialog->set_transient_for(*m_parent);

    // Set calendar
    m_calendar = new Gtk::Calendar();
    m_dialog->get_vbox()->add(*m_calendar);
    m_dialog->show_all();

    // Connect signals
    add_events(Gdk::BUTTON_PRESS_MASK);
    m_calendar->signal_day_selected().connect(sigc::mem_fun(*this, &DateEntry::on_day_select), false);
    m_calendar->signal_month_changed().connect(sigc::mem_fun(*this, &DateEntry::on_month_select), false);
    m_calendar->signal_button_press_event().connect(sigc::mem_fun(*this, &DateEntry::on_button_pressed), true);
}

#include <iostream>
/* Calendar button press signal handler */
bool DateEntry::on_button_pressed(GdkEventButton* event) {
    // Day is selected
    if (!m_month_changed) {
        guint day, month, year;
        m_calendar->get_date(year, month, day);
        m_entry.set_text(std::to_string(year) + "/" + 
                         std::to_string(month+1) + "/" + 
                         std::to_string(day));  

        // Close dialog
        if (m_dialog) {
            m_dialog->close();
            delete m_dialog;
            m_dialog = nullptr;
        }
    }
    else 
        m_month_changed = false;

    return false;
}


/* Calendar day select signal handler */
void DateEntry::on_day_select() {
    m_month_changed = false;
}


/* Calendar month select signal handler */
void DateEntry::on_month_select() {
    m_month_changed = true;
}
