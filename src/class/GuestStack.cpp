/**
 * File: GuestStack.cpp
 * Description: Implementation of Guest stack widget class
 */
#include "GuestStack.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include "helper.hpp"

/* Default Constructor */
GuestStack::GuestStack() :
c_pages {"Room List", "Calendar Schedule",
         "News", "Setting"}
{
    // Stack stack properties
    set_transition_type(Gtk::STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);

    // Set guest scrolled window properties
    m_scroll_tree.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
    m_scroll_tree.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_scroll_tree.add(m_treeView);

    // Set news scrolled window properties
    m_scroll_news.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
    m_scroll_tree.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_scroll_news.add(m_listBox);

    // Set pages'
    for (int page = 0; page < c_pages.size(); page++) {
        switch(page) {
            case 0 :
                add(m_scroll_tree, c_pages[page], c_pages[page]);
                break;
            case 2:
                add(m_scroll_news, c_pages[page], c_pages[page]);
                break;
            default:
                Gtk::Label* label = new Gtk::Label(c_pages[page], FALSE);
                add(*label, c_pages[page], c_pages[page]);
                m_labels.push_back(label);
                break;
        }
    }

    show_all_children();
}


/* Get treeview widget */
GuestTreeView* GuestStack::getTreeview() {
    return &m_treeView;
}


/* Destructor */
GuestStack::~GuestStack() {
    for (int i = 0; i < m_labels.size(); i++) {
        delete m_labels[i];
    }
}