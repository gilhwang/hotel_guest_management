/**
 * File: GuestTreeView.cpp
 * Description: Implmentation of Guest tree view class
 */
#include "GuestTreeView.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include "globals.hpp"


/* Constructor */
GuestTreeView::GuestTreeView() {
    // Create tree model
    m_refTreeModel = Gtk::TreeStore::create(m_columns);
    set_model(m_refTreeModel);

    // Append column to tree view
    append_column("First Name", m_columns.m_col_first_name);
    append_column("Last Name", m_columns.m_col_last_name);
    append_column("Gender", m_columns.m_col_gender);
    append_column("From", m_columns.m_col_start_date);
    append_column("To", m_columns.m_col_end_date);
    append_column("Payment", m_columns.m_col_payment);

    // Append data to tree model row
    for (auto it = roomData.begin(); it != roomData.end(); it++) {
        // Local Variables
        Glib::ustring roomNumber = std::to_string(it->first);
        std::unordered_map<int,Customer*> data = it->second;

        // Append room number
        auto row = *(m_refTreeModel->append());
        row[m_columns.m_col_first_name] = roomNumber;

        // Append customer data of the room
        for (auto childIt = data.begin(); childIt != data.end(); childIt++) {
            // Local Variables
            Customer* customer = childIt->second;

            auto childRow = *(m_refTreeModel->append(row.children()));
            childRow[m_columns.m_col_first_name] = customer->getFirstName();
            childRow[m_columns.m_col_last_name] = customer->getLastName();
            childRow[m_columns.m_col_gender] = customer->getGenderString();
            childRow[m_columns.m_col_start_date] = customer->getInfo().startDate.getString();
            childRow[m_columns.m_col_end_date] = customer->getInfo().endDate.getString();
            childRow[m_columns.m_col_payment] = customer->getInfo().getPaymentString();
        }
        
    }
    
    
}