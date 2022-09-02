/**
 * File: NewsListBox.hpp
 * Description: Header file for list box of news and news row
 */
#pragma once
#include <gtkmm-3.0/gtkmm.h>
#include <curl/curl.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;

/* Row class */
class NewsRow : public Gtk::VBox {
public:
    // Constructor
    NewsRow();

    // Member widgets
    Gtk::HBox m_topbox;
    Gtk::HBox m_bottombox;
    Gtk::Label m_title;
    Gtk::Label m_date;
    Gtk::Button m_button;
};

/* NewsListBox class */
class NewsListBox : public Gtk::ListBox {
public:
    // Constructor&Destructor
    NewsListBox();
    ~NewsListBox();

protected:
    // Methods
    bool initializeCurl();
    static size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp);
    void initializeRows(ptree& ptRoot);

    // Member widget
    NewsRow* m_row;

    // News data struct
    typedef struct {
        char* url = nullptr;
        unsigned int size = 0;
        char* response = nullptr;
    } News;

    // Member variables
    CURL* m_curlHandle;
    ptree m_ptRoot;
};