/*
 ============================================================================
 Name        : tak_gui.c
 Author      : Øystein
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "global_variables.h"



int main( int argc, char *argv[] ){



    GtkWidget *button_quit, *button_mark, *button_clear, *button_apply_color;
    GtkWidget *button_insert_back, *button_insert_front, *button_update_current;
    GtkWidget *button_prev, *button_next, *button_fb, *button_ff, *button_start, *button_end;
    GtkWidget *button_dim_f, *button_dim_b;
    GtkWidget *button_save, *button_save_as, *button_load;
    GtkWidget *button_delete, *button_delete_multiple, *button_delete_all;
    GtkWidget *button_shift_up, *button_shift_down, *button_shift_left, *button_shift_right;

    GtkWidget *align_frames, *align_panel, *align_window;


    GtkColorButton *color_master;
    GtkGrid *grid_frames, *grid_panel, *grid;

    gint i, j;


    color_button = malloc(10*sizeof(GtkColorButton**));
    toggle_button = malloc(10*sizeof(GtkToggleButton**));
    bool_marked = malloc(10*sizeof(gboolean**));

    for(i = 0; i<10;i++){
    	color_button[i] = malloc(6*sizeof(GtkColorButton*));
    	toggle_button[i] = malloc(6*sizeof(GtkToggleButton*));
    	bool_marked[i] = malloc(6*sizeof(gboolean*));

    	  for(j = 0; j<6;j++){
    	    	color_button[i][j] = malloc(sizeof(GtkColorButton));
    	    	toggle_button[i][j] = malloc(sizeof(GtkToggleButton));
    	    	bool_marked[i][j] = malloc(sizeof(gboolean));
    	  }
    }

    gtk_init (&argc, &argv);


    /* Adding window with options */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (window, "delete-event", G_CALLBACK (callback_delete_event), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);
    /* Adding grid with options */
    grid = (GtkGrid*)gtk_grid_new();
	gtk_grid_set_row_homogeneous(grid, TRUE);
	gtk_grid_set_column_homogeneous(grid, TRUE);
    gtk_grid_set_column_spacing(grid, 20);

    grid_frames = (GtkGrid*)gtk_grid_new();

	gtk_grid_set_row_homogeneous(grid_frames, TRUE);
	gtk_grid_set_column_homogeneous(grid_frames, TRUE);

	grid_panel = (GtkGrid*)gtk_grid_new();
	gtk_grid_set_row_homogeneous(grid_panel, TRUE);
	gtk_grid_set_column_homogeneous(grid_panel, TRUE);
	gtk_grid_set_row_spacing(grid_panel, 10);

	callback_init();


    button_quit = gtk_button_new_with_label("Quit");
    button_mark = gtk_button_new_with_label("Mark all");
    button_clear = gtk_button_new_with_label("Unmark all");

    button_apply_color = gtk_button_new_with_label("Apply to marked");

    button_update_current = gtk_button_new_with_label("Update current");
    button_insert_back = gtk_button_new_with_label("Insert in back");
    button_insert_front = gtk_button_new_with_label("Insert in front");

    button_prev = gtk_button_new();
    button_next = gtk_button_new();
    button_fb = gtk_button_new();
    button_ff = gtk_button_new();
    button_start = gtk_button_new();
    button_end = gtk_button_new();

    button_dim_f = gtk_button_new_with_label("Dim forward");
    button_dim_b = gtk_button_new_with_label("Dim backward");

    button_save = gtk_button_new_with_label("Save show");
    button_save_as = gtk_button_new_with_label("Save show as..");
    button_load = gtk_button_new_with_label("Load show");

    button_delete = gtk_button_new_with_label("Delete current");
    button_delete_multiple = gtk_button_new_with_label("Delete mulitple");
    button_delete_all = gtk_button_new_with_label("Delete all");

    button_shift_up = gtk_button_new_with_label("Shift up");
    button_shift_down = gtk_button_new_with_label("Shift down");
    button_shift_left = gtk_button_new_with_label("Shift left");
    button_shift_right = gtk_button_new_with_label("Shift right");

    gtk_button_set_image ((GtkButton*)button_prev, gtk_image_new_from_file ("images/prev.png"));
    gtk_button_set_image ((GtkButton*)button_next, gtk_image_new_from_file ("images/next.png"));
    gtk_button_set_image ((GtkButton*)button_fb, gtk_image_new_from_file ("images/fb.png"));
    gtk_button_set_image ((GtkButton*)button_ff, gtk_image_new_from_file ("images/ff.png"));
    gtk_button_set_image ((GtkButton*)button_start, gtk_image_new_from_file ("images/start.png"));
    gtk_button_set_image ((GtkButton*)button_end, gtk_image_new_from_file ("images/end.png"));

    align_frames = gtk_alignment_new(0.5, 0.5, 0, 0);
    align_panel = gtk_alignment_new(0.5, 0.5, 1, 0);
    align_window = gtk_alignment_new(0.5, 0.5, 0, 0);

    gtk_container_add (GTK_CONTAINER (align_frames), (GtkWidget*)grid_frames);
    gtk_container_add (GTK_CONTAINER (align_panel), (GtkWidget*)grid_panel);
    gtk_container_add (GTK_CONTAINER (align_window), (GtkWidget*)grid);
    gtk_container_add (GTK_CONTAINER (window), (GtkWidget*)align_window);



    label_frame_number = gtk_label_new ("Frame 1 of 1");



    color_master = (GtkColorButton*)gtk_color_button_new ();

    g_signal_connect (button_mark, "clicked", G_CALLBACK (callback_mark_all), NULL);
    g_signal_connect (button_clear, "clicked", G_CALLBACK (callback_unmark_all), NULL);
    g_signal_connect (button_quit, "clicked", G_CALLBACK (callback_delete_event), NULL);

    g_signal_connect (button_apply_color, "clicked", G_CALLBACK (callback_apply_color), (gpointer) color_master);
    g_signal_connect (button_apply_color, "clicked", G_CALLBACK (callback_color_changed), NULL);
    g_signal_connect (button_update_current, "clicked", G_CALLBACK (callback_update_current), NULL);

    g_signal_connect (button_prev, "clicked", G_CALLBACK (callback_show_prev), NULL);
    g_signal_connect (button_next, "clicked", G_CALLBACK (callback_show_next), NULL);
    g_signal_connect (button_fb, "clicked", G_CALLBACK (callback_jump_prev), NULL);
    g_signal_connect (button_ff, "clicked", G_CALLBACK (callback_jump_next), NULL);
    g_signal_connect (button_start, "clicked", G_CALLBACK (callback_jump_start), NULL);
    g_signal_connect (button_end, "clicked", G_CALLBACK (callback_jump_end), NULL);

    g_signal_connect (button_insert_back, "clicked", G_CALLBACK (callback_insert_behind), NULL);
    g_signal_connect (button_insert_front, "clicked", G_CALLBACK (callback_insert_before), NULL);

    g_signal_connect (button_dim_f, "clicked", G_CALLBACK (callback_auto_dim_popup), (gpointer) TRUE);
    g_signal_connect (button_dim_b, "clicked", G_CALLBACK (callback_auto_dim_popup), (gpointer) FALSE);

    g_signal_connect (button_save, "clicked", G_CALLBACK (callback_save), "test");
    g_signal_connect (button_save_as, "clicked", G_CALLBACK (callback_save_as), NULL);
    g_signal_connect (button_load, "clicked", G_CALLBACK (callback_load), NULL);

    g_signal_connect (button_delete, "clicked", G_CALLBACK (callback_delete_current), NULL);
    g_signal_connect (button_delete_multiple, "clicked", G_CALLBACK (callback_delete_multiple), NULL);
    g_signal_connect (button_delete_all, "clicked", G_CALLBACK (callback_delete_all), NULL);

    g_signal_connect (button_shift_up, "clicked", G_CALLBACK (callback_shift_up), NULL);
    g_signal_connect (button_shift_down, "clicked", G_CALLBACK (callback_shift_down), NULL);
    g_signal_connect (button_shift_left, "clicked", G_CALLBACK (callback_shift_left), NULL);
    g_signal_connect (button_shift_right, "clicked", G_CALLBACK (callback_shift_right), NULL);


    g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (callback_on_key_press), NULL);


	for(i = 0; i<10;i++){
		for(j = 0; j<6;j++){
			gtk_grid_attach(grid_frames,(GtkWidget*) color_button[i][j], i, j*3+1, 1, 2);
			gtk_grid_attach(grid_frames,(GtkWidget*) toggle_button[i][j], i, j*3+3, 1, 1);
			gtk_widget_show ((GtkWidget*)color_button[i][j]);
			gtk_widget_show ((GtkWidget*)toggle_button[i][j]);
		}
	}
    gtk_grid_attach (grid_frames, (GtkWidget*)button_mark, 0, 20, 5, 1);
    gtk_grid_attach (grid_frames, (GtkWidget*)button_clear, 5, 20, 5, 1);
    gtk_grid_attach (grid_frames, (GtkWidget*)button_quit, 0, 21, 10, 1);

    gtk_grid_attach (grid_frames, (GtkWidget*)button_prev, 2, 0, 1, 1);
    gtk_grid_attach (grid_frames, (GtkWidget*)button_next, 7, 0, 1, 1);
    gtk_grid_attach (grid_frames, (GtkWidget*)button_fb, 1, 0, 1, 1);
	gtk_grid_attach (grid_frames, (GtkWidget*)button_ff, 8, 0, 1, 1);
	gtk_grid_attach (grid_frames, (GtkWidget*)button_start, 0, 0, 1, 1);
	gtk_grid_attach (grid_frames, (GtkWidget*)button_end, 9, 0, 1, 1);

    gtk_grid_attach (grid_frames, (GtkWidget*)label_frame_number, 3, 0, 4, 1);

    gtk_grid_attach (grid_panel, (GtkWidget*)color_master, 2, 0, 2, 2);
    gtk_grid_attach (grid_panel, (GtkWidget*)button_apply_color, 0, 4, 6, 1);

    gtk_grid_attach (grid_panel, (GtkWidget*)button_update_current, 0, 7, 6, 1);
    gtk_grid_attach_next_to (grid_panel, (GtkWidget*)button_insert_back, (GtkWidget*)button_update_current, GTK_POS_BOTTOM, 3, 1);
    gtk_grid_attach_next_to (grid_panel, (GtkWidget*)button_insert_front, (GtkWidget*)button_insert_back, GTK_POS_RIGHT, 3, 1);

	gtk_grid_attach (grid_panel, (GtkWidget*)button_dim_f, 3, 9, 3, 1);
	gtk_grid_attach_next_to (grid_panel, (GtkWidget*)button_dim_b,(GtkWidget*)button_dim_f, GTK_POS_LEFT, 3, 1);

	gtk_grid_attach (grid_panel, (GtkWidget*)button_save, 0, 13, 3, 1);
	gtk_grid_attach (grid_panel, (GtkWidget*)button_save_as, 3, 13, 3, 1);
	gtk_grid_attach (grid_panel, (GtkWidget*)button_load, 0, 14, 6, 1);

	gtk_grid_attach (grid_panel, (GtkWidget*)button_delete, 0, 10, 6, 1);
	gtk_grid_attach_next_to (grid_panel, (GtkWidget*)button_delete_multiple, (GtkWidget*)button_delete, GTK_POS_BOTTOM, 6, 1);
	gtk_grid_attach_next_to (grid_panel, (GtkWidget*)button_delete_all, (GtkWidget*)button_delete_multiple, GTK_POS_BOTTOM, 6, 1);


	gtk_grid_attach (grid_panel, (GtkWidget*)button_shift_down, 0, 6, 3, 1);
	gtk_grid_attach_next_to (grid_panel, (GtkWidget*)button_shift_up,(GtkWidget*)button_shift_down, GTK_POS_RIGHT, 3, 1);
	gtk_grid_attach (grid_panel, (GtkWidget*)button_shift_left, 0, 5, 3, 1);
	gtk_grid_attach_next_to (grid_panel, (GtkWidget*)button_shift_right,(GtkWidget*)button_shift_left, GTK_POS_RIGHT, 3, 1);

    gtk_grid_attach (grid, (GtkWidget*)align_frames, 0, 0, 10, 21);
    gtk_grid_attach (grid, (GtkWidget*)align_panel, 10, 0, 6, 21);

    //grid.attach_next_to(button3, button1, Gtk.PositionType.BOTTOM, 1, 2)

	gtk_widget_show (button_mark);
	gtk_widget_show (button_clear);
	gtk_widget_show (button_quit);

	gtk_widget_show (button_update_current);
	gtk_widget_show (button_insert_back);
	gtk_widget_show (button_insert_front);

	gtk_widget_show (button_prev);
	gtk_widget_show (button_next);
	gtk_widget_show (button_fb);
	gtk_widget_show (button_ff);
	gtk_widget_show (button_start);
	gtk_widget_show (button_end);

	gtk_widget_show (button_dim_f);
	gtk_widget_show (button_dim_b);

	gtk_widget_show (button_save);
	gtk_widget_show (button_save_as);
	gtk_widget_show (button_load);

	gtk_widget_show (button_delete);
	gtk_widget_show (button_delete_multiple);
	gtk_widget_show (button_delete_all);

	gtk_widget_show (button_shift_up);
	gtk_widget_show (button_shift_down);
	gtk_widget_show (button_shift_left);
	gtk_widget_show (button_shift_right);

	gtk_widget_show ((GtkWidget*)color_master);
	gtk_widget_show (button_apply_color);

	gtk_widget_show (label_frame_number);

	gtk_widget_show ((GtkWidget*)align_frames);
	gtk_widget_show ((GtkWidget*)align_panel);
	gtk_widget_show ((GtkWidget*)align_window);

	gtk_widget_show ((GtkWidget*)grid_frames);
	gtk_widget_show ((GtkWidget*)grid_panel);
	gtk_widget_show ((GtkWidget*)grid);

	gtk_widget_show (window);


    gtk_main ();

    return 0;
}

