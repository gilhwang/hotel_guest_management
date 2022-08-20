/**
 * File: GuestStack.cpp
 * Description: Implementation of Guest stack widget class
 */
#include "GuestStack.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include "helper.hpp"

/* Constructor */
GuestStack::GuestStack() :
c_pages {"Room List", "Calendar Schedule",
         "News", "Setting"}
{
    // Stack stack properties
    set_transition_type(Gtk::STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);

    // Set scrolled window properties
    m_scroll.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
    m_scroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_scroll.add(m_treeView);

    // Set pages
    for (int page = 0; page < c_pages.size(); page++) {
        switch(page) {
            case 0 :
                add(m_scroll, c_pages[page], c_pages[page]);
                break;
            default:
                Gtk::Label* label = new Gtk::Label(c_pages[page], FALSE);
                add(*label, c_pages[page], c_pages[page]);
                m_labels.push_back(label);
                break;
        }
    }

    // // Create tree model and set to treeview
    // m_refTreeModel = Gtk::TreeStore::create(m_columns);
    // m_treeView.set_model(m_refTreeModel);

    // // Set treeview properties
    // m_treeView.set_reorderable();

    // // Fill treeview model
    // auto row = *(m_refTreeModel->append());
    // row[m_columns.m_col_id] = 11;
    // row[m_columns.m_col_name] = "Billy Bob";

    // m_treeView.append_column("ID", m_columns.m_col_id);
    // m_treeView.append_column("Name", m_columns.m_col_name);

    show_all_children();
}


/* Destructor */
GuestStack::~GuestStack() {
    for (int i = 0; i < m_labels.size(); i++) {
        delete m_labels[i];
    }
}