/**
 * File: GuestStack.hpp
 * Description: Header file for Guest stack widget class
 */
#pragma once

#include <gtkmm-3.0/gtkmm.h>
#include <vector>
#include "GuestTreeView.hpp"

class GuestStack : public Gtk::Stack {
public:
    GuestStack();
    virtual ~GuestStack();

protected:
    /* Member variables */
    const std::vector<Glib::ustring> c_pages;

    /* Member widgets */
    std::vector<Gtk::Label*> m_labels;
    Gtk::ScrolledWindow m_scroll;
    GuestTreeView m_treeView;
};