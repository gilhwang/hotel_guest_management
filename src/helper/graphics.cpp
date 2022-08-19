/*
 * File: graphics.cpp
 * Descriptoin: Implementation of graphics-related functions
 */
#include "graphics.hpp"
#include <gtkmm-3.0/gtkmm.h>
#include "helper.hpp"
#include "events.hpp"
#include "globals.hpp"
#include <stdlib.h>
#include "LoginWindow.hpp"

// Definitions
#define NUM_TREE_COLUMN 6

// Enumerations
enum {
    FIRST_NAME_COLUMN = 0,
    LAST_NAME_COLUMN,
    GENDER_COLUMN,
    START_DATE_COLUMN,
    END_DATE_COLUMN,
    PAYMENT_COLUMN
};

/* Draws login screen */
bool draw_login_screen(){
    auto app = Gtk::Application::create("org.gtkmm.login");
    LoginWindow window;
    app->run(window);
    return window.loginSuccess;
}


/* Draws the GTK widgets */
void draw_application(int argc, char** argv){
    gtk_init(&argc, &argv);
    
    // Process Login before starting application
    bool success = draw_login_screen();

    if (success == false){
        return;
    }

    // Set window
    static GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    initialize_window(window);

    // Set header
    GtkWidget* header = gtk_header_bar_new();
    initialize_header(window, header);

    // Set box & sidebar
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* sidebar = gtk_stack_sidebar_new();
    gtk_box_pack_start(GTK_BOX(box), sidebar, FALSE, FALSE, 0);

    // Set stack
    GtkWidget* stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(stack));

    // Set separator between sidebar and stack
    GtkWidget* separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(box), separator, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), stack, TRUE, TRUE, 0);

    initialize_stack_pages(stack);
    
    // Display window
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
    gtk_main();
}

/* Initialize stack pages */
void initialize_stack_pages(GtkWidget* stack){
    // Set stack titles
    const gchar* pages[] = {"Room List",
                            "Calendar Schedule",
                            "News",
                            "Setting",
                            NULL
                            };
    const gchar* c = NULL;
    GtkWidget* widget = NULL;

    // Set pages
    for (guint i=0; (c = *(pages+i)) != NULL; i++){
        if (i == 0) {
            widget = gtk_scrolled_window_new(NULL, NULL);
            gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(widget), 
                                                GTK_SHADOW_ETCHED_IN);
            gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widget), 
                                            GTK_POLICY_AUTOMATIC,
                                            GTK_POLICY_AUTOMATIC);
        }
        else {
            widget = gtk_label_new(c);
        }

        gtk_stack_add_named(GTK_STACK(stack), widget, c);
        gtk_container_child_set(GTK_CONTAINER(stack), widget, "title", c, NULL);
    }

    initializeTree(stack);
}


/* Initialie window */
void initialize_window(GtkWidget* window){
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(window, 1000, 700);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), &window);
}


/* Initialize header */
void initialize_header(GtkWidget* window, GtkWidget* header){
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(window), header);
    gtk_window_set_title(GTK_WINDOW(window), "Hotel Guest Management");
}

/* Create Tree Model */
GtkTreeModel* create_model(){
    // Local Variables
    GtkTreeStore* model = gtk_tree_store_new(NUM_TREE_COLUMN, // # of columns
                                             G_TYPE_STRING,   // First name
                                             G_TYPE_STRING,   // Last name
                                             G_TYPE_STRING,   // Gender
                                             G_TYPE_STRING,   // Start date
                                             G_TYPE_STRING,   // End date
                                             G_TYPE_STRING);  // Payment
    // Add all room data
    GtkTreeIter iter;
    for (auto roomIt=roomData.begin(); roomIt != roomData.end(); roomIt++) {
        int roomNumber = roomIt->first;

        // Set room header
        gtk_tree_store_append(model, &iter, NULL);
        gtk_tree_store_set(model, &iter,
                          FIRST_NAME_COLUMN, ("# " + std::to_string(roomNumber)).c_str(),
                          LAST_NAME_COLUMN, "",
                          GENDER_COLUMN, "",
                          START_DATE_COLUMN, "",
                          END_DATE_COLUMN, "", 
                          -1);
        
        // Traverse through all customers staying
        for (auto cusIt = roomIt->second.begin(); cusIt != roomIt->second.end(); cusIt++) {
            // Local Variables
            Customer* customer = cusIt->second;
            GtkTreeIter cust_iter;

            // Append guest list to room header
            gtk_tree_store_append(model, &cust_iter, &iter);
            gtk_tree_store_set(model, &cust_iter,
                               FIRST_NAME_COLUMN, customer->getFirstName().c_str(),
                               LAST_NAME_COLUMN, customer->getLastName().c_str(),
                               GENDER_COLUMN, customer->getGenderString().c_str(),
                               START_DATE_COLUMN, customer->getInfo().startDate.getString().c_str(),
                               END_DATE_COLUMN, customer->getInfo().endDate.getString().c_str(),
                               PAYMENT_COLUMN, customer->getInfo().getPaymentString().c_str(),
                               -1);

        }
    }
    
    return GTK_TREE_MODEL(model);
}


/* Add column to treeview */
void add_columns (GtkTreeView* treeview){
    // First name column
    GtkCellRenderer* renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "xalign", 0.0, 
                 "weight", PANGO_WEIGHT_BOLD, 
                 NULL);

    gint col_offset = gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
                                                                  "Room Number", renderer, 
                                                                  "text", FIRST_NAME_COLUMN, 
                                                                  NULL);
    GtkTreeViewColumn* column = gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), col_offset-1);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(column), GTK_TREE_VIEW_COLUMN_FIXED);
    gtk_tree_view_column_set_clickable(GTK_TREE_VIEW_COLUMN(column), TRUE);

    // Last Name column
    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "xalign", 0.0, NULL);
    col_offset = gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, 
                                                             "Last Name", renderer, 
                                                             "text", LAST_NAME_COLUMN, 
                                                             NULL);
    column = gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), col_offset-1);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(column), GTK_TREE_VIEW_COLUMN_FIXED);
    gtk_tree_view_column_set_clickable(GTK_TREE_VIEW_COLUMN(column), TRUE);

    // Gender column
    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "xalign", 0.0, NULL);
    col_offset = gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                                  -1, "Gender",
                                                                  renderer, "text",
                                                                  GENDER_COLUMN, NULL);
    column = gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), col_offset-1);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(column), GTK_TREE_VIEW_COLUMN_FIXED);
    gtk_tree_view_column_set_clickable(GTK_TREE_VIEW_COLUMN(column), TRUE);

    // Start Date column
    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "xalign", 0.0, NULL);
    col_offset = gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                                  -1, "From",
                                                                  renderer, "text",
                                                                  START_DATE_COLUMN, NULL);
    column = gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), col_offset-1);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(column), GTK_TREE_VIEW_COLUMN_FIXED);
    gtk_tree_view_column_set_clickable(GTK_TREE_VIEW_COLUMN(column), TRUE);

    // End date column
    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "xalign", 0.0, NULL);
    col_offset = gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                                  -1, "To",
                                                                  renderer, "text",
                                                                  END_DATE_COLUMN, NULL);
    column = gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), col_offset-1);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(column), GTK_TREE_VIEW_COLUMN_FIXED);
    gtk_tree_view_column_set_clickable(GTK_TREE_VIEW_COLUMN(column), TRUE);

    // Payment column
    renderer = gtk_cell_renderer_text_new();
    g_object_set(renderer, "xalign", 0.0, NULL);
    col_offset = gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview),
                                                                  -1, "Payment",
                                                                  renderer, "text",
                                                                  PAYMENT_COLUMN, NULL);
    column = gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), col_offset-1);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(column), GTK_TREE_VIEW_COLUMN_FIXED);
    gtk_tree_view_column_set_clickable(GTK_TREE_VIEW_COLUMN(column), TRUE);
}


/* Initialzie Treeview model */
void initializeTree(GtkWidget* stack){
    // Set treeview
    GtkTreeModel* model = create_model();
    GtkWidget* treeview = gtk_tree_view_new_with_model(model);
    g_object_unref(model);
    gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)),
                                GTK_SELECTION_MULTIPLE);
    
    add_columns(GTK_TREE_VIEW(treeview));

    GtkWidget* slidingWindow = gtk_stack_get_child_by_name(GTK_STACK(stack), "Room List");
    gtk_container_add(GTK_CONTAINER(slidingWindow), treeview);

    g_signal_connect(treeview, "realize", G_CALLBACK(gtk_tree_view_expand_all), NULL);
}