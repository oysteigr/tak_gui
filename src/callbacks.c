#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "window.h"
#include "frames.h"
#include "global_variables.h"
#include "load_save.h"

void callback_init(){
    frame_header_init();
    window_colorbuttons_init();
}

void  callback_auto_dim_run ( GtkWidget *widget, gpointer data ){

	GtkEntryBuffer* buffer_dim_frames_value = (GtkEntryBuffer*)((gpointer*)data)[1];
	gint value = atoi(gtk_entry_buffer_get_text(buffer_dim_frames_value));
	value = value*25/10;
	frame_auto_dim(value, color_button, (gboolean)((gpointer*)data)[0]);
	window_update_label();
	free(data);
}

void  callback_auto_dim_popup ( GtkWidget *widget, gpointer data ){
   GtkWidget *dialog, *label, *content_area;
   GtkWidget *button_ok;
   GtkWidget *entry_dim_frames_value;

   GtkEntryBuffer* buffer_dim_frames_value;

   if((gboolean)data && frame_header->current_frame->next_frame == NULL){
	   window_popup_warning("Can't dim to the frame after when there is none after!");
	   return;
   }
   if(!(gboolean)data && frame_header->current_frame->prev_frame == NULL){
	   window_popup_warning("Can't dim to the frame before when there is none before!");
	   return;
   }


   dialog = gtk_dialog_new_with_buttons ("Dimmer", (GtkWindow*)window, GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);
   content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
   label = gtk_label_new ("Number of deciseconds");

   button_ok = gtk_dialog_add_button ((GtkDialog*)dialog, "DIM", (gint)GTK_STOCK_OK);

   buffer_dim_frames_value = gtk_entry_buffer_new("0", -1);

   entry_dim_frames_value = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(buffer_dim_frames_value));

   gpointer* data_array = malloc(sizeof(gpointer[2]));
   data_array[0] = data;
   data_array[1] = (gpointer)buffer_dim_frames_value;

   g_signal_connect (button_ok, "clicked", G_CALLBACK (callback_auto_dim_run), data_array);
   g_signal_connect_swapped (button_ok, "clicked", G_CALLBACK (gtk_widget_destroy), dialog);

   gtk_container_add (GTK_CONTAINER (content_area), label);
   gtk_container_add (GTK_CONTAINER (content_area), entry_dim_frames_value);

   gtk_widget_show_all (dialog);
}




void callback_mark( GtkWidget *widget, gpointer data ){
	int k = atoi((char*)data);
	*bool_marked[k%10][k/10] = gtk_toggle_button_get_active((GtkToggleButton*) widget);
}
void callback_mark_all( GtkWidget *widget, gpointer data ){
	int i,j;
	for (i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			gtk_toggle_button_set_active(toggle_button[i][j], TRUE);
			*bool_marked[i][j] = TRUE;
		}
	}
    return;
}
void callback_clear_all( GtkWidget *widget, gpointer data ){
	int i,j;
	for (i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			gtk_toggle_button_set_active(toggle_button[i][j], FALSE);
			*bool_marked[i][j] = FALSE;
		}
	}
    return;
}

void callback_apply_color( GtkWidget *widget, gpointer data ){
	int i,j;
	gboolean any_selected = FALSE;
	GdkRGBA rgba;
	for (i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			if(*bool_marked[i][j]){
				gtk_color_button_get_rgba((GtkColorButton*)data,&rgba);
				gtk_color_button_set_rgba(color_button[i][j], &rgba);
				any_selected = TRUE;

			}
		}
	}
	if(!any_selected){
		window_popup_warning("Nothing is selected!");
	}
    return;
}

gboolean callback_delete_event( GtkWidget *widget, GdkEvent  *event, gpointer data ){
    gtk_main_quit ();
    return FALSE;
}


void callback_update_current(GtkWidget *widget, gpointer data){
	frame_update_current(color_button);

}
void callback_insert_before(GtkWidget *widget, gpointer data){
	frame_insert_front(color_button);

	window_update_label();
}
void callback_insert_behind(GtkWidget *widget, gpointer data){
	frame_insert_back(color_button);

	window_update_label();
}

void callback_color_changed(GtkWidget *widget, gpointer data){
	int i, j;
	GdkRGBA rgba;
	gchar color_string[13];
	for(i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			gtk_color_button_get_rgba(color_button[i][j], &rgba);
			get_short_color_string(color_string, rgba);
			gtk_button_set_label ((GtkButton*)toggle_button[i][j], color_string);
		}
	}
}

void callback_show_prev(GtkWidget *widget, gpointer data){
	frame_show_prev(color_button);
	frame_load_colors(color_button);
	callback_color_changed(widget, data);
	window_update_label();
}

void callback_show_next(GtkWidget *widget, gpointer data){
	frame_show_next(color_button);
	frame_load_colors(color_button);
	callback_color_changed(widget, data);
	window_update_label();
}

void callback_jump_prev(GtkWidget *widget, gpointer data){
	int i;
	for(i = 0; i<100; i++){
		frame_show_prev(color_button);
	}
	frame_load_colors(color_button);
	callback_color_changed(widget, data);
	window_update_label();
}

void callback_jump_next(GtkWidget *widget, gpointer data){
	int i;
	for(i = 0; i<100; i++){
		frame_show_next(color_button);
	}
	frame_load_colors(color_button);
	callback_color_changed(widget, data);
	window_update_label();
}

void callback_jump_start(GtkWidget *widget, gpointer data){
	frame_header->current_frame = frame_header->start_frame;
	frame_header->selected_number = 1;
	frame_load_colors(color_button);
	callback_color_changed(widget, data);
	window_update_label();
}

void callback_jump_end(GtkWidget *widget, gpointer data){
	frame_header->current_frame = frame_header->end_frame;
	frame_header->selected_number = frame_header->counter;
	frame_load_colors(color_button);
	callback_color_changed(widget, data);
	window_update_label();
}

void callback_on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data){
    switch (event->keyval)
    {
        case GDK_KEY_Left:
        	callback_show_prev(widget, data);
            break;
        case GDK_KEY_Right:
        	callback_show_next(widget, data);
            break;
        default:
            return;
    }
}

void callback_save( GtkWidget *widget, gpointer data){
	save_to_file(widget, data);
}
void callback_save_as( GtkWidget *widget, gpointer data){
	save_as_popup (widget, data);
}
void callback_load( GtkWidget *widget, gpointer data){
	load_select_file_dialog(widget, data);
	frame_load_colors(color_button);
	window_update_label();
}

void callback_delete_current( GtkWidget *widget, gpointer data){
	if(frame_header->current_frame->next_frame == NULL && frame_header->current_frame->prev_frame == NULL){
		window_popup_warning("Can't delete the last frame!");
	}
	else{
		frame_delete();
		frame_load_colors(color_button);
		callback_color_changed(widget, data);
		window_update_label();
	}
}

void callback_delete_all( GtkWidget *widget, gpointer data){
	while(frame_delete());
	frame_make_black();
	frame_load_colors(color_button);
	callback_color_changed(widget, data);
	window_update_label();
}
