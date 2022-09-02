/**
 * File: GuestStack.hpp
 * Description: Header file for Guest stack widget class
 */
#pragma once

#include <gtkmm-3.0/gtkmm.h>
#include <vector>
#include "GuestTreeView.hpp"
#include "NewsListBox.hpp"

class GuestStack : public Gtk::Stack {
public:
    // Constructors&Destructors
    GuestStack();
    virtual ~GuestStack();

    // Getters
    GuestTreeView* getTreeview();

protected:
    // Member variables
    const std::vector<Glib::ustring> c_pages;

    // Member widgets
    std::vector<Gtk::Label*> m_labels;
    Gtk::ScrolledWindow m_scroll_tree;
    Gtk::ScrolledWindow m_scroll_news;
    GuestTreeView m_treeView;
    NewsListBox m_listBox;
};