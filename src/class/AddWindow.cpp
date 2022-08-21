/**
 * File: AddWindow.cpp
 * Description: Implementation for window class for adding guest
 */
#include "AddWindow.hpp"
#include "globals.hpp"
#include "MainWindow.hpp"

/* Constructor */
AddWindow::AddWindow() :
m_title("Please fill in the following information"),
m_label_first("First Name"),
m_label_last("Last Name"),
m_button_add("Check In"),
m_button_quit("Quit")
{
    // Set window property
    set_position(Gtk::WIN_POS_CENTER);
    set_resizable(FALSE);
    set_titlebar(m_header);
    set_title("Guest Check In");

    // Set entry property
    m_entry_first.set_placeholder_text("John");
    m_entry_last.set_placeholder_text("Smith");

    // Set gender radio buttons
    if (GENDER_STRING.size()) {
        // Initialize first radio button
        Gtk::RadioButton* first = Gtk::manage(new Gtk::RadioButton(GENDER_STRING.front()));
        Gtk::RadioButton::Group radioGroup = first->get_group();
        m_radio_gender.push_back(first);

        // Initialize rest
        for (int i = 1; i < GENDER_STRING.size(); i++) {
            Gtk::RadioButton* radioButton = Gtk::manage(new Gtk::RadioButton(GENDER_STRING[i]));
            radioButton->set_group(radioGroup);
            m_radio_gender.push_back(radioButton);
        }
    }

    // Set payment radio buttons
    if (PAYMENT_STRING.size()) {
        // Initialize first radio button
        Gtk::RadioButton* first = Gtk::manage(new Gtk::RadioButton(PAYMENT_STRING.front()));
        Gtk::RadioButton::Group radioGroup = first->get_group();
        m_radio_payment.push_back(first);

        // Initialize rest
        for (int i = 1; i < PAYMENT_STRING.size(); i++) {
            Gtk::RadioButton* radioButton = Gtk::manage(new Gtk::RadioButton(PAYMENT_STRING[i]));
            radioButton->set_group(radioGroup);
            m_radio_payment.push_back(radioButton);
        }
    }

    // Add radio buttons to box
    for (int i = 0; i < m_radio_gender.size() || i < m_radio_payment.size(); i++) {
        if (i < m_radio_gender.size())
            m_box_radio.pack_start(*m_radio_gender[i]);
        if (i < m_radio_payment.size())
            m_box_payment.pack_start(*m_radio_payment[i]);
    }

    // NOTE: START AND END DATE -> List store as dropdown menu
                            //  -> customize GtkCellRenderer to have GtkCalendar in 1 liststore

    // Attach widgets onto grid
    m_grid.attach(m_title, 0, 0, 2, 1);
    m_grid.attach(m_label_first, 0, 1, 1, 1);
    m_grid.attach(m_entry_first, 1, 1, 1, 1);
    m_grid.attach(m_label_last, 0, 2, 1, 1);
    m_grid.attach(m_entry_last, 1, 2, 1, 1);
    m_grid.attach(m_box_radio, 0, 3, 1, 1);
    m_grid.attach(m_box_payment, 0, 4, 1, 1);
    m_grid.attach(m_button_add, 0, 5, 1, 1);
    m_grid.attach(m_button_quit, 1, 5, 1, 1);

    // Set grid
    m_grid.set_row_spacing(5);
    m_grid.set_margin_left(GRID_MARGIN);
    m_grid.set_margin_right(GRID_MARGIN);
    m_grid.set_margin_top(GRID_MARGIN);
    m_grid.set_margin_bottom(GRID_MARGIN);

    // Signal Handlers
    m_button_add.signal_clicked().connect(sigc::mem_fun(*this, &AddWindow::on_add_button_clicked));
    m_button_quit.signal_clicked().connect(sigc::mem_fun(*this, &AddWindow::close));

    // Add widget to window
    add(m_grid);
    show_all_children();
}


/* Destructor */
AddWindow::~AddWindow() {}


/* Add button clicked signal handler */
void AddWindow::on_add_button_clicked() {
    // Retrieve input from entries

    // Create a new Customer object

    // Update customer data -> insert to multimap<string, Customer> 

    // Update room date -> insert to unordered_map<int, unordered_map<int, Customer *> roomData;

    customerData.clear();
    roomData.clear();
    
    MainWindow* window = dynamic_cast<MainWindow*> (get_transient_for());
    window->refresh();

    // Force the treeview to redraw
    // Use Gtk::Widget::queue_draw for Gtk::TreeView

    close();
}