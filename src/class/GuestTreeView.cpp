/**
 * File: GuestTreeView.cpp
 * Description: Implmentation of Guest tree view class
 */
#include "GuestTreeView.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include "globals.hpp"
#include "MainWindow.hpp"
#include "graphics.hpp"
#include <sstream>

/* Global variables */
// Constants


/* Constructor */
GuestTreeView::GuestTreeView() 
: m_first_column("First Name"),
  m_menu_delete("Delete")
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

        // Set cell renderer properties
        cell->set_property("editable", true);
        cell->signal_editing_started().connect(sigc::mem_fun(*this, &GuestTreeView::cell_on_editing_started));
        cell->signal_edited().connect(sigc::mem_fun(*this, &GuestTreeView::cell_on_edited));

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
            Customer* customer = childIt->second;
            appendRow(row.children(), customer);
        }
    }

    // Set pop menu
    m_popmenu.add(m_menu_delete);
    m_popmenu.attach_to_widget(*this);
    m_popmenu.hide();
    
    // Set signal handlers
    set_activate_on_single_click(false);
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_row_activated().connect(sigc::mem_fun(*this, &GuestTreeView::on_row_activate));
    signal_button_release_event().connect(sigc::mem_fun(*this, &GuestTreeView::on_button_released));
    m_menu_delete.signal_activate().connect(sigc::mem_fun(*this, &GuestTreeView::on_delete_activated));

    // Set treeview properties
    expand_all();
    set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_HORIZONTAL);
}


/* Destructor */
GuestTreeView::~GuestTreeView() {}


/* Initializee parent window */
void GuestTreeView::setWindow(MainWindow* window) {
    m_window = window;
}

/* Add new guest */
void GuestTreeView::addGuest(Customer* newCustomer, bool firstInRoom) {
    // Local Variables
    Gtk::TreeModel::Children rows = m_refTreeModel->children();
    Glib::ustring room = std::to_string(newCustomer->getInfo().roomNumber);

    // Insert new row under correct room
    for (auto iter = rows.begin(); iter != rows.end(); iter++) {
        if (iter->get_value(m_columns.m_col_bold) && 
            iter->get_value(m_columns.m_col_first_name) == room) {
            appendRow(iter->children(), newCustomer);
        }
    }

    // Append customer data in file
    std::string output;
    if (firstInRoom)
        output = newCustomer->createOutputNew();
    else
        output = newCustomer->createOutput();
    appendToFile(dataFilePath, output);

    expand_all();
}


/* Add new room */
void GuestTreeView::addRoom(int roomNum) {
    // Add new room to data
    roomData.insert(std::make_pair(roomNum, std::unordered_map<int,Customer*>()));

    // Add an empty room to data file
    std::string VOID_MARK = "\%void\%";
    std::string output = "\n" + VOID_MARK + "," + std::to_string(roomNum);
    appendToFile(dataFilePath, output);

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


/* Row double click signal handler */
void GuestTreeView::on_row_activate(const Gtk::TreeModel::Path& path, 
                                     Gtk::TreeViewColumn* column) {
    auto iter = m_refTreeModel->get_iter(path);
    Gtk::TreeRow row = *iter;
    std::cout << row[m_columns.m_col_first_name] << std::endl;
}


/* Mouse button click signal handler */
bool GuestTreeView::on_button_released(GdkEventButton* event) {
    // Return if right button is not clicked
    if ((event->type != GDK_BUTTON_RELEASE) || (event->button != RIGHT_BUTTON))
        return false;

    // Return if row is not selected
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn* column;
    int cellX, cellY;
    if (!get_path_at_pos(event->x, event->y, path, column, cellX, cellY)) 
        return false;

    // Show pop menu & record row to be deleted
    m_popmenu.show_all_children();
    m_popmenu.popup(event->button, event->time);
    m_deleteIter = m_refTreeModel->get_iter(path);
    return true;
}


/* Menu item activate signal handler */
void GuestTreeView::on_delete_activated() {  
    // Check if room is selected
    if (m_deleteIter->get_value(m_columns.m_col_bold)) {
        m_window->displayInfo("Room can not be deleted.", Gtk::MESSAGE_ERROR);
        return;
    }

    // Local Variables 
    std::string lastName = m_deleteIter->get_value(m_columns.m_col_last_name);
    int roomNumber = m_deleteIter->get_value(m_columns.m_col_room_num);
    int guestNumber = m_deleteIter->get_value(m_columns.m_col_guest_num);
    std::string outputLine = customerData.find(guestNumber)->second->getOutput();

    // Remove guest from data
    customerData.erase(guestNumber);
    roomData.at(roomNumber).erase(guestNumber);
    deleteInFile(dataFilePath, outputLine);
    m_refTreeModel->erase(m_deleteIter);
}


/* Cell renderer editing started signal handler */
void GuestTreeView::cell_on_editing_started(Gtk::CellEditable* cell_editable, 
                                            const Glib::ustring& /*path*/) {
    // Check if retrying from an invalid input
    if (m_retry) {
        auto entry = dynamic_cast<Gtk::Entry*>(cell_editable);
        if (entry) {
            entry->set_text(m_invalidText);
            m_retry = false;
            m_invalidText.clear();
        }
    }
    else {
        // Store column to be edited
        Gtk::TreeModel::Path path;
        Gtk::TreeViewColumn* col;
        get_cursor(path, col);
        editColumn = m_columns.getColumn(col->get_title(), this);
    }
}


/* Cell renderer edited signal handler */
/* Reference: https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.4.1/en/sec-dialogs-messagedialog.html */
void GuestTreeView::cell_on_edited(const Glib::ustring& path, const Glib::ustring& text) {
    // Check input validity
    if (!isUpdateValid(getColumnProperty(editColumn), text)) {
        m_window->displayInfo("Invalid Input!", Gtk::MESSAGE_ERROR);
        m_retry = true;
        m_invalidText = text;
        return;
    }

    // Local Variables
    Gtk::TreeRow row = *m_refTreeModel->get_iter(path); 
    int guestNumber = row[m_columns.m_col_guest_num];

    // Ask user for confirmation
    int result = displayDialog(m_window, "Would you update the information?", "Click OK to confirm.", 
                               Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);

    // Ignore if user canceled the update
    if (result == Gtk::RESPONSE_CANCEL)
        return;

    // Update treeview
    row[editColumn] = text;

    // Update data
    Customer* updateGuest = customerData.find(guestNumber)->second;
    updateGuest->updateInfo(getColumnProperty(editColumn), text);
    
    // Update file
    // === TO DO: change specific info within the line in csv file
}


/* Check input if it is valid to update */
bool GuestTreeView::isUpdateValid(CustomerProperty property, Glib::ustring data) {
    // Check empty
    if (data.empty())
        return false;
    
    switch (property) {
        case CustomerProperty::firstName:
            return isValidName(data);
        case CustomerProperty::lastName:
            return isValidName(data);
        case CustomerProperty::gender:
            return isValidGender(data);
        case CustomerProperty::startDate:
            return isValidDate(data);
        case CustomerProperty::endDate:
            return isValidDate(data);
        case CustomerProperty::payMethod:
            return isValidPayment(data);
        default:
            return false;
    }
}


/* Check if name input is valid */
bool GuestTreeView::isValidName(Glib::ustring data) {
    return true;
}


/* Check if gender input is valid */
bool GuestTreeView::isValidGender(Glib::ustring data) {
    for (std::string genderType : GENDER_STRING) {
        if (data == genderType)
            return true;
    }
    return false;
}


/* Check if date input is valid */
bool GuestTreeView::isValidDate(Glib::ustring data) {
    // Local Variables
    std::stringstream ssInput(data);
    std::string year, month, day;

    if (getline(ssInput, year, '/') &&
        getline(ssInput, month, '/') &&
        getline(ssInput, day)) {
        return isInteger(year) && isInteger(month) && isInteger(day);
    }
    else 
        return false;
}


/* Check if payment input is valid */
bool GuestTreeView::isValidPayment(Glib::ustring data) {
    for (std::string payType : PAYMENT_STRING) {
        if (data == payType)
            return true;
    }
    return false;
}


/* Return the property column based on TreeModelColumn */
CustomerProperty GuestTreeView::getColumnProperty(Gtk::TreeModelColumn<Glib::ustring> column) {    
    if (column == m_columns.m_col_first_name) 
        return CustomerProperty::firstName;
    else if (column == m_columns.m_col_last_name)
        return CustomerProperty::lastName;
    else if (column == m_columns.m_col_gender) 
        return CustomerProperty::gender;
    else if (column == m_columns.m_col_start_date)
        return CustomerProperty::startDate;
    else if (column == m_columns.m_col_end_date) 
        return CustomerProperty::endDate;
    else if (column == m_columns.m_col_payment) 
        return CustomerProperty::payMethod;
    else
        return CustomerProperty::unselected;
}


/* Append row to treeview */
void GuestTreeView::appendRow(const Gtk::TreeNodeChildren children, Customer* data) {
    // Local Variables
    auto childRow = *m_refTreeModel->append(children);

    // Visual data
    childRow[m_columns.m_col_first_name] = data->getFirstName();
    childRow[m_columns.m_col_last_name] = data->getLastName();
    childRow[m_columns.m_col_gender] = data->getGenderString();
    childRow[m_columns.m_col_start_date] = data->getInfo().startDate.getString();
    childRow[m_columns.m_col_end_date] = data->getInfo().endDate.getString();
    childRow[m_columns.m_col_payment] = data->getInfo().getPaymentString();

    // Hidden columns
    childRow[m_columns.m_col_bold] = false;
    childRow[m_columns.m_col_guest_num] = data->getInfo().guestNumber;
    childRow[m_columns.m_col_room_num] = data->getInfo().roomNumber;
}


/* Return TreeModelColumn based on column number */
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


/* Return TreeModelColumn with column title */
Gtk::TreeModelColumn<Glib::ustring> ModelColumns::getColumn(Glib::ustring title, GuestTreeView* obj) {
    for (int i = 0; i < obj->getTitles()->size(); i++) {
        if (title == obj->getTitles()->at(i))
            return getColumn(i);
    }

    return getColumn(0);
}