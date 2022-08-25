/**
 * File: GuestTreeView.cpp
 * Description: Implmentation of Guest tree view class
 */
#include "GuestTreeView.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include "globals.hpp"

/* Global variables */
// Constants


/* Constructor */
GuestTreeView::GuestTreeView() :
m_first_column("First Name")
{
    // Create tree model
    m_refTreeModel = Gtk::TreeStore::create(m_columns);
    m_refTreeModel->set_sort_column(SORTING_COL, Gtk::SortType::SORT_ASCENDING);
    set_model(m_refTreeModel);

    // Append columns
    for (int i = 0; i < c_titles.size(); i++) {
        // Local Variables
        Glib::ustring title = c_titles.at(i);
        Gtk::CellRendererText* cell = Gtk::manage(new Gtk::CellRendererText());

        // Append column
        int pos = append_column(title, *cell);  
        Gtk::TreeViewColumn* column = get_column(pos-1);

        // Set column properties
        column->set_renderer(*cell, m_columns.getColumn(i));
        column->set_fixed_width(c_widths.at(i));
        column->set_alignment(Gtk::ALIGN_CENTER);

        // Set text renderer
        if (i == 0)
            column->set_cell_data_func(*cell, sigc::mem_fun(*this, &GuestTreeView::on_cell_data));
        else {
            cell->property_font() = NORMAL_FONT;

            // Set sorting column
            if (i == SORTING_COL)
                column->set_sort_column(SORTING_COL);
        }
    }

    // Append data to tree model row
    for (auto it = roomData.begin(); it != roomData.end(); it++) {
        // Local Variables
        Glib::ustring roomNumber = std::to_string(it->first);
        std::unordered_map<int,Customer*> data = it->second;

        // Append room number
        auto row = *(m_refTreeModel->append());
        row[m_columns.m_col_first_name] = roomNumber;
        row[m_columns.m_col_bold] = true;

        // Append customer data of the room
        for (auto childIt = data.begin(); childIt != data.end(); childIt++) {
            // Local Variables
            Customer* customer = childIt->second;

            // Write data to each column
            auto childRow = *(m_refTreeModel->append(row.children()));
            childRow[m_columns.m_col_first_name] = customer->getFirstName();
            childRow[m_columns.m_col_last_name] = customer->getLastName();
            childRow[m_columns.m_col_gender] = customer->getGenderString();
            childRow[m_columns.m_col_start_date] = customer->getInfo().startDate.getString();
            childRow[m_columns.m_col_end_date] = customer->getInfo().endDate.getString();
            childRow[m_columns.m_col_payment] = customer->getInfo().getPaymentString();
            childRow[m_columns.m_col_bold] = false;
        }
    }
    
    // Set treeview properties
    expand_all();
    set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_HORIZONTAL);
}


/* Add new guest */
void GuestTreeView::addGuest(Customer* newCustomer) {
    // Local Variables
    Gtk::TreeModel::Children rows = m_refTreeModel->children();
    Glib::ustring room = std::to_string(newCustomer->getInfo().roomNumber);

    // Insert new row under correct room
    for (auto iter = rows.begin(); iter != rows.end(); iter++) {
        if (iter->get_value(m_columns.m_col_bold) && 
            iter->get_value(m_columns.m_col_first_name) == room) {
            auto childRow = *(m_refTreeModel->append(iter->children()));
            childRow[m_columns.m_col_first_name] = newCustomer->getFirstName();
            childRow[m_columns.m_col_last_name] = newCustomer->getLastName();
            childRow[m_columns.m_col_gender] = newCustomer->getGenderString();
            childRow[m_columns.m_col_start_date] = newCustomer->getInfo().startDate.getString();
            childRow[m_columns.m_col_end_date] = newCustomer->getInfo().endDate.getString();
            childRow[m_columns.m_col_payment] = newCustomer->getInfo().getPaymentString();
            childRow[m_columns.m_col_bold] = false;
        }
    }
    
    expand_all();
}


/* Add new room */
void GuestTreeView::addRoom(int roomNum) {
    // Add new room to data
    roomData.insert(std::make_pair(roomNum, std::unordered_map<int,Customer*>()));

    // Append new row
    Gtk::TreeRow row = *(m_refTreeModel->append());
    row[m_columns.m_col_first_name] = std::to_string(roomNum);
    row[m_columns.m_col_bold] = true;
}

/* Cell data function for room name */
void GuestTreeView::on_cell_data(Gtk::CellRenderer* renderer,
                                 const Gtk::TreeModel::iterator& iter) {
    // Get value from model
    Gtk::TreeModel::Row row = *iter;
    Glib::ustring firstName = row[m_columns.m_col_first_name];
    bool markBold = row[m_columns.m_col_bold];

    Gtk::CellRendererText* textRenderer = dynamic_cast<Gtk::CellRendererText*>(renderer);

    // Safety check
    if (textRenderer == nullptr)
        return;

    // Set text properties
    textRenderer->property_text() = firstName;
    if (markBold)
        textRenderer->property_font() = ROOM_FONT;
    else   
        textRenderer->property_font() = NORMAL_FONT;
}


/* Return TreeModelColumn based on column title */
Gtk::TreeModelColumn<Glib::ustring> ModelColumns::getColumn(int col) {
    switch (col) {
        case 0 : return m_col_first_name;   break;
        case 1 : return m_col_last_name;    break;
        case 2 : return m_col_gender;       break;
        case 3 : return m_col_start_date;   break;
        case 4 : return m_col_end_date;     break;
        case 5 : return m_col_payment;      break;
        default: break;
    }

    return m_col_first_name;
}