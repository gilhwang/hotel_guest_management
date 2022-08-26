/**
 * File: AddWindow.cpp
 * Description: Implementation for window class for adding guest
 */
#include "AddWindow.hpp"
#include "globals.hpp"
#include "MainWindow.hpp"
#include "Customer.hpp"
#include "CustomerInfo.hpp"

/* Constructor */
AddWindow::AddWindow() 
: m_title("Please fill in the following information"),
  m_label_first("First Name"),
  m_label_last("Last Name"),
  m_button_add("Check In"),
  m_button_quit("Quit"),
  m_entry_start("From ", this),
  m_entry_end("To  ", this),
  m_label_error(""),
  m_label_room("Room")
  {
    // Set window property
    set_position(Gtk::WIN_POS_CENTER);
    set_resizable(FALSE);
    set_titlebar(m_header);
    set_title("Guest Check In");

    // Set entry property
    m_entry_first.set_text("John");
    m_entry_last.set_text("Smith");

    // Set info bar
    m_infobar.add_button(Gtk::Stock::OK, 0);
    Gtk::Container* infoBarContainer = dynamic_cast<Gtk::Container*>(m_infobar.get_content_area());
    if (infoBarContainer) 
        infoBarContainer->add(m_label_error);


    // Set gender radio buttons
    if (GENDER_STRING.size() > 1) {
        // Initialize first radio button
        Gtk::RadioButton* first = Gtk::manage(new Gtk::RadioButton(GENDER_STRING.at(1)));
        Gtk::RadioButton::Group radioGroup = first->get_group();
        m_radio_gender.push_back(first);

        // Initialize rest
        for (int i = 2; i < GENDER_STRING.size(); i++) {
            Gtk::RadioButton* radioButton = Gtk::manage(new Gtk::RadioButton(GENDER_STRING[i]));
            radioButton->set_group(radioGroup);
            m_radio_gender.push_back(radioButton);
        }
    }

    // Set payment radio buttons
    if (PAYMENT_STRING.size() > 1) {
        // Initialize first radio button
        Gtk::RadioButton* first = Gtk::manage(new Gtk::RadioButton(PAYMENT_STRING.at(1)));
        Gtk::RadioButton::Group radioGroup = first->get_group();
        m_radio_payment.push_back(first);

        // Initialize rest
        for (int i = 2; i < PAYMENT_STRING.size(); i++) {
            Gtk::RadioButton* radioButton = Gtk::manage(new Gtk::RadioButton(PAYMENT_STRING[i]));
            radioButton->set_group(radioGroup);
            m_radio_payment.push_back(radioButton);
        }
    }

    // Add radio buttons to box
    for (int i = 0; i < m_radio_gender.size() || i < m_radio_payment.size(); i++) {
        if (i < m_radio_gender.size())
            m_box_gender.pack_start(*m_radio_gender[i]);
        if (i < m_radio_payment.size())
            m_box_payment.pack_start(*m_radio_payment[i]);
    }

    // Set room combo box
    m_refTreeModel = Gtk::ListStore::create(m_columns);
    m_room.set_model(m_refTreeModel);
    m_room.pack_start(m_columns.m_col_num);

    for (auto it = roomData.begin(); it != roomData.end(); it++) {
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_columns.m_col_num] = it->first;

        // Set default selection
        if (it == roomData.begin())
            m_room.set_active(0);
    }

    // Set add button style
    Glib::RefPtr<Gtk::CssProvider> addProvider = Gtk::CssProvider::create();
    addProvider->load_from_data(c_addbutton_data);
    m_button_add.get_style_context()->add_provider(addProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    dynamic_cast<Gtk::Label*>(m_button_add.get_children().at(0))->override_color(Gdk::RGBA("White"), Gtk::STATE_FLAG_NORMAL);

    // Set quit button style
    Glib::RefPtr<Gtk::CssProvider> quitProvider = Gtk::CssProvider::create();
    quitProvider->load_from_data(c_quitbutton_data);
    m_button_quit.get_style_context()->add_provider(quitProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Attach widgets onto grid
    int row = 0;
    m_grid.attach(m_infobar, 0, row++, 2, 1);
    m_grid.attach(m_title, 0, row++, 2, 1);
    m_grid.attach(m_label_first, 0, row, 1, 1);
    m_grid.attach(m_entry_first, 1, row++, 1, 1);
    m_grid.attach(m_label_last, 0, row, 1, 1);
    m_grid.attach(m_entry_last, 1, row++, 1, 1);
    m_grid.attach(m_box_gender, 0, row++, 2, 1);
    m_grid.attach(m_label_room, 0, row, 1, 1);
    m_grid.attach(m_room, 1, row++, 1, 1);
    m_grid.attach(m_entry_start, 0, row++, 2, 1);
    m_grid.attach(m_entry_end, 0, row++, 2, 1);
    m_grid.attach(m_box_payment, 0, row++, 2, 1);
    m_grid.attach(m_button_quit, 0, row, 1, 1);
    m_grid.attach(m_button_add, 1, row, 1, 1);
    
    // Set alignment
    m_label_first.set_halign(Gtk::Align::ALIGN_START);
    m_label_last.set_halign(Gtk::Align::ALIGN_START);
    m_label_room.set_halign(Gtk::Align::ALIGN_START);
    m_entry_start.set_halign(Gtk::Align::ALIGN_END);
    m_entry_end.set_halign(Gtk::Align::ALIGN_END);

    // Set grid
    m_grid.set_row_spacing(5);
    m_grid.set_margin_left(GRID_MARGIN);
    m_grid.set_margin_right(GRID_MARGIN);
    m_grid.set_margin_top(GRID_MARGIN);
    m_grid.set_margin_bottom(GRID_MARGIN);

    // Signal Handlers
    m_button_add.signal_clicked().connect(sigc::mem_fun(*this, &AddWindow::on_add_button_clicked));
    m_button_quit.signal_clicked().connect(sigc::mem_fun(*this, &AddWindow::close));
    m_infobar.signal_response().connect(sigc::mem_fun(*this, &AddWindow::on_info_response));

    // Display window
    add(m_grid);
    show_all_children();
    m_infobar.hide();
}


/* Destructor */
AddWindow::~AddWindow() {}


/**
 * Add button clicked signal handler 
 * Reference: https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/es/sec-infobar.html
 */
void AddWindow::on_add_button_clicked() {
    // Retrieve input from entries
    std::string firstName = m_entry_first.get_text();
    std::string lastName = m_entry_last.get_text();
    int roomNumber = m_room.get_active()->get_value(m_columns.m_col_num);
    Gender gender = getGenderSelected();
    Date startDate(std::string(m_entry_start.getEntry().get_text()));
    Date endDate(std::string(m_entry_end.getEntry().get_text()));
    Payment payment = getPaymentSelected();

    // Check for date input error
    if (startDate > endDate) {
        m_label_error.set_text("Invalid Date! Please Try again.");
        m_infobar.set_message_type(Gtk::MESSAGE_ERROR);
        m_infobar.show();
        return;
    }

    // Create profile and add to data
    CustomerInfo info(nextGuestNum++, roomNumber, startDate, endDate, payment);
    Customer* newCustomer = new Customer(firstName, lastName, gender, info);
    customerData.insert(std::make_pair(lastName, newCustomer));
    roomData[roomNumber][newCustomer->getInfo().guestNumber] = newCustomer;

    // Append new row to treeview
    MainWindow* window = static_cast<MainWindow*> (get_transient_for());
    window->getStack()->getTreeview()->addGuest(newCustomer);
    close();
}


/* Info bar button click signal handler */
void AddWindow::on_info_response(int /*response_id*/) {
    m_label_error.set_text("");
    m_infobar.hide();
}


/* Retrieve gender info from radiobuttons */
Gender AddWindow::getGenderSelected() {
    for (int i = 0; i < m_radio_gender.size(); i++) {
        if (m_radio_gender[i]->get_active())
            return static_cast<Gender>(i+1);
    }

    return Gender::unselected;
}

/* Retrieve payment info fronm radiobuttons */
Payment AddWindow::getPaymentSelected() {
    for (int i = 0; i < m_radio_payment.size(); i++) {
        if (m_radio_payment[i]->get_active()) 
            return static_cast<Payment>(i+1);
    }

    return Payment::unselected;
}
