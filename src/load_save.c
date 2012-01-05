#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "frames.h"
#include "load_save.h"


void save_to_file( GtkWidget *widget, gpointer data){
	FILE *file;
	int i,j;
	Frame* frame_to_write;

	char filename[20];
	sprintf(filename, "%s.rts",(gchar*)data);

	frame_to_write = frame_header->start_frame;
	file = fopen(filename,"w"); /* apend file (add text to
	a file or create a file if it does not exist.*/
	while(1){
		for(i = 0; i<10; i++){
			for(j = 0; j<6; j++){
				fprintf(file,"%s",frame_to_write->frame[i][j]);
			}
		}
		if(frame_to_write == frame_header->end_frame){break;}
		frame_to_write = frame_to_write->next_frame;
		fprintf(file,"%s","\n");
	}
	fclose(file); /*done!*/
	return;
}

void  save_as_popup ( GtkWidget *widget, gpointer data ){
   GtkWidget *dialog_save_as, *label, *content_area;
   GtkWidget *button_ok;
   GtkWidget *entry_file_name;

   GtkEntryBuffer* buffer_file_name;

   dialog_save_as = gtk_dialog_new_with_buttons ("Save as..",(GtkWindow*) gtk_widget_get_parent_window(widget), GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);
   content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog_save_as));
   label = gtk_label_new ("Enter file name");

   button_ok = gtk_dialog_add_button ((GtkDialog*)dialog_save_as, "Save as", (gint)GTK_STOCK_OK);

   buffer_file_name = gtk_entry_buffer_new("New_file", -1);

   entry_file_name = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(buffer_file_name));

   g_signal_connect (button_ok, "clicked", G_CALLBACK (save_to_file), (gpointer)gtk_entry_buffer_get_text(buffer_file_name));
   g_signal_connect_swapped (button_ok, "clicked", G_CALLBACK (gtk_widget_destroy), dialog_save_as);

   gtk_container_add (GTK_CONTAINER (content_area), label);
   gtk_container_add (GTK_CONTAINER (content_area), entry_file_name);

   gtk_widget_show_all (dialog_save_as);
}

void load_read_file(char *filename){

	FILE *in = fopen(filename, "rt");

	char buffer[500];
	fgets(buffer, 500, in);
	frame_store_frame(buffer, FALSE);

	while(fgets(buffer, 500, in)!=NULL){
		frame_store_frame(buffer, TRUE);
	}
	fclose(in);
	return;
}

void load_select_file_dialog( GtkWidget *widget, gpointer data){
	GtkWidget * file_load_dialog = gtk_file_chooser_dialog_new("Choose show to load..", (GtkWindow*) gtk_widget_get_parent_window(widget), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	GtkFileFilter* file_filter = gtk_file_filter_new();
	gtk_file_filter_set_name(file_filter, "Regi tak show");
	gtk_file_filter_add_pattern(file_filter, "*.rts");
	gtk_file_chooser_set_filter((GtkFileChooser*)file_load_dialog, file_filter);
	gtk_file_chooser_set_current_folder_uri((GtkFileChooser*)file_load_dialog, "/workspace/tak_gui/src");
	if (gtk_dialog_run (GTK_DIALOG (file_load_dialog)) == GTK_RESPONSE_ACCEPT){
	    char *filename;
	    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_load_dialog));
	    load_read_file(filename);
	    g_free (filename);
	}
	gtk_widget_destroy (file_load_dialog);
}
