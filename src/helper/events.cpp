/*
 * File: events.cpp
 * Description: Implementation of events-related functions
 */
#include "events.hpp"
#include <gtk/gtk.h>
#include "graphics.hpp"
#include "helper.hpp"

/* Login button callback */
void login_clicked(GtkWidget* button, gpointer data) { 
    // Constants
    const gchar* correctID = "admin";
    const gchar* correctPW = "1";

    // Retrieve information
    GtkWidget* window = gtk_widget_get_toplevel(button);
    Entries* loginEntries = (Entries*) data;
    const gchar* id = gtk_entry_get_text(GTK_ENTRY(loginEntries->id));
    const gchar* pw = gtk_entry_get_text(GTK_ENTRY(loginEntries->pw));

    // Move to main window if entered correctly
    if (gchar_equals(id, correctID) && gchar_equals(pw, correctPW)) {
        loginEntries->success = true;
        gtk_widget_destroy(window);
    }

    // Pop up error message if incorrect
    else {
        GtkWidget* popover = create_popover(button,
                                            gtk_label_new("Incorrect ID or PW!"),
                                            GTK_POS_TOP,
                                            FALSE);  

        gtk_widget_set_visible(popover, true);                                 
    }
}