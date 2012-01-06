#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "frames.h"
#include "load_save.h"
#include "callbacks.h"
#include "global_variables.h"


void window_update_label(){
	gchar label[20];
	sprintf(label,"Frame %d of %d",frame_header->selected_number,frame_header->counter);
	gtk_label_set_text ((GtkLabel*)label_frame_number, label);
}

void window_colorbuttons_init(){
	GdkRGBA rgba;
    char *strpoint;
    int i, j;
    gdk_rgba_parse(&rgba,"#000000");
	for(i = 0; i<10;i++){
		for(j = 0; j<6;j++){
			strpoint = malloc(sizeof(char[12]));
			sprintf(strpoint, "%d",j*10+i);

			color_button[i][j] = (GtkColorButton*)gtk_color_button_new ();
			toggle_button[i][j] = (GtkToggleButton*)gtk_toggle_button_new_with_label("#000000");
			*bool_marked[i][j] = FALSE;

			gtk_color_button_set_rgba(color_button[i][j], &rgba);
			g_signal_connect ((GtkWidget*)color_button[i][j], "color-set", G_CALLBACK (callback_color_changed), (gpointer) strpoint);
			g_signal_connect ((GtkWidget*)toggle_button[i][j], "clicked", G_CALLBACK (callback_mark), (gpointer) strpoint);

		}
	}
}
void window_popup_warning(char* message){

	   GtkWidget *dialog_warning_message, *label, *content_area;
	   GtkWidget *button_ok;

	   dialog_warning_message = gtk_dialog_new_with_buttons ("You fool!",(GtkWindow*) window, GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);
	   content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog_warning_message));
	   label = gtk_label_new (message);

	   button_ok = gtk_dialog_add_button ((GtkDialog*)dialog_warning_message, "I understand", (gint)GTK_STOCK_OK);

	   g_signal_connect_swapped (button_ok, "clicked", G_CALLBACK (gtk_widget_destroy), dialog_warning_message);

	   gtk_container_add (GTK_CONTAINER (content_area), label);

	   gtk_widget_show_all (dialog_warning_message);
}
