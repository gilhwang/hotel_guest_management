/**
 * File: NewsListBox.cpp
 * Description: Implmentaton of NewsListBox and NewsRow class
 */
#include "NewsListBox.hpp"
#include <curl/curl.h>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <string>

using boost::property_tree::ptree;
using boost::property_tree::read_json;

/* NewsListBox Constructor */
NewsListBox::NewsListBox() {
    if (!initializeCurl())
        return;
    
    initializeRows(m_ptRoot);

    show_all_children();
}


/* NewsListBox Destructor */
NewsListBox::~NewsListBox() {
    // Clean curl data
    curl_easy_cleanup(m_curlHandle);
    m_curlHandle = nullptr;
    curl_global_cleanup();
}


/* Intialize curl related features */
bool NewsListBox::initializeCurl() {
    // Local Variables
    char targetURL[] = "https://newsapi.org/v2/top-headlines?country=us&apiKey=306a6381035346aebb29b2a18d0fdfdc";
    char errbuf[CURL_ERROR_SIZE] = {0};
    News newsData;
    
    // Perform global initialization
    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    if (res != CURLE_OK) {
        std::cout << "ERROR: Unable to initialize libcurl!" << std::endl;
        std::cout << curl_easy_strerror(res) << std::endl;
        return false;
    }

    // Initialize handle
    m_curlHandle = curl_easy_init();
    if (!m_curlHandle) {
        std::cout << "ERROR: Unable to get easy handle." << std::endl;
        return false;
    }

    // Set curlHandle option
    res = curl_easy_setopt(m_curlHandle, CURLOPT_URL, targetURL);
    if (res == CURLE_OK)
        res = curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION, write_data);
    // Specify error message
    if (res == CURLE_OK) 
        res = curl_easy_setopt(m_curlHandle, CURLOPT_ERRORBUFFER, errbuf);
    if (res == CURLE_OK) {
        res = curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, &newsData);
        newsData.url = targetURL;
    }
    if (res == CURLE_OK) {
        res = curl_easy_setopt(m_curlHandle, CURLOPT_USERAGENT, "null");
    }

    // Check if option was set properly
    if (res != CURLE_OK) {
        std::cout << "ERROR: Unable to set libcurl option." << std::endl;
        //std::cout < curl_easy_strerror(res) << std::endl;
        return false;
    } 

    // Transfer data
    res = curl_easy_perform(m_curlHandle);

    // Check if data is transferred properly
    if (res != CURLE_OK) {
        std::cout << "ERROR: res == " << res << std::endl;
        std::cout << errbuf << std::endl;
        return false;
    }

    // Store json data
    std::istringstream issJsonData(newsData.response);
    read_json(issJsonData, m_ptRoot);

    return true;
}


/* Write data callback function */
size_t NewsListBox::write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
    if (buffer && nmemb && userp) {
        News* pData = (News*) userp;

        // Write for first time
        if (pData->response == nullptr) {
            pData->response = new char[nmemb+1];
            strncpy(pData->response, (char*) buffer, nmemb);
        }
        // Append new data to old data
        else {
            char* oldResponse = pData->response;
            pData->response = new char[pData->size + nmemb + 1];
            strncpy(pData->response, oldResponse, pData->size);     // Old data copy
            strncpy(pData->response + pData->size, (char*) buffer, nmemb);  // Append new data
            
            delete [] oldResponse;
        }

        pData->size += nmemb;
        pData->response[pData->size] = '\0';
    }
    
    return nmemb;
}


/* Print parsed JSON data */
void NewsListBox::initializeRows(ptree& ptRoot) {
    // Local Variables
    std::string title;
    std::string source;
    std::string url;
    std::string date;

    BOOST_FOREACH(ptree::value_type& resVal, ptRoot.get_child("articles")) {
        // Check if JSON array under toplevel has name
        if (!resVal.first.empty()) 
            throw "\"results\" child node has a name";

        // Get values
        title = resVal.second.get<std::string>("title");
        url = resVal.second.get<std::string>("url");
        date = resVal.second.get<std::string>("publishedAt");

        // Make a new row
        m_row = Gtk::manage(new NewsRow());
        m_row->m_title.set_text(title);
        m_row->m_date.set_text(date);
        add(*m_row);
    }
}



/* NewsRow Constructor */
NewsRow::NewsRow() : 
m_topbox(Gtk::ORIENTATION_HORIZONTAL),
m_bottombox(Gtk::ORIENTATION_HORIZONTAL),
m_title("title"),
m_date("year-month-day"),
m_button("More")
{
    // Set button
    m_button.set_size_request(50,10);
    m_button.set_hexpand(false);
    m_button.set_halign(Gtk::ALIGN_END);

    // Set labels
    m_title.set_halign(Gtk::ALIGN_START);
    m_date.set_halign(Gtk::ALIGN_END);

    // Set top box
    m_topbox.add(m_title);
    m_topbox.add(m_button);
    m_topbox.set_homogeneous(false);


    // Set buttom box
    m_bottombox.add(m_date);
    m_bottombox.set_halign(Gtk::ALIGN_END);

    // Add widgets
    add(m_topbox);
    add(m_bottombox);
}



