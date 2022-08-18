/* 
 * File: graphics.hpp
 * Description: Header file for graphics-related functions
 */

#pragma once

#include <gtk/gtk.h>

/* Draw window */
void draw_application (int argc, char** argv);
bool draw_login_screen();

/* Widget Initialization */
void initialize_stack_pages (GtkWidget* stack);
void initialize_window (GtkWidget* window);
void initialize_header (GtkWidget* window, GtkWidget* header);
void initializeTree (GtkWidget* stack);
void add_columns (GtkTreeView* treeview);

/* Create Widget */
GtkTreeModel* create_model ();
GtkWidget* create_popover(GtkWidget*       parent,
                          GtkWidget*       child,
                          GtkPositionType  pos,
                          gboolean         modal);
