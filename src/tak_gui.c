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


#include "frames.h"

GtkColorButton*** color_button;
GtkToggleButton*** toggle_button;
gboolean*** bool_marked;

GtkWidget *label_frame_number;
GtkWidget *window;



static void update_label(){
	gchar label[20];
	sprintf(label,"Frame %d of %d",frame_header->selected_number,frame_header->counter);
	gtk_label_set_text ((GtkLabel*)label_frame_number, label);
}

static void  auto_dim_run ( GtkWidget *widget, gpointer data ){
	printf("Runs auto_dim %d !!\n",(gint)((gpointer*)data)[1]);
	frame_auto_dim((gint)((gpointer*)data)[1], color_button, (gboolean)((gpointer*)data)[0]);
	update_label();
}

static void  auto_dim_popup ( GtkWidget *widget, gpointer data ){
   GtkWidget *dialog, *label, *content_area;
   GtkWidget *button_ok;
   GtkWidget *entry_dim_frames_value;

   GtkEntryBuffer* buffer_dim_frames_value;

   gpointer* data_array = malloc(sizeof(gpointer[2]));
   data_array[0] = data;
   data_array[1] = (gpointer)25;

   dialog = gtk_dialog_new_with_buttons ("Dimmer", (GtkWindow*)window, GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);
   content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
   label = gtk_label_new ("Number of deciseconds");

   button_ok = gtk_dialog_add_button ((GtkDialog*)dialog, "DIM", (gint)GTK_STOCK_OK);

   buffer_dim_frames_value = gtk_entry_buffer_new("0", -1);

   entry_dim_frames_value = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(buffer_dim_frames_value));

   g_signal_connect (button_ok, "clicked", G_CALLBACK (auto_dim_run), data_array);
   g_signal_connect_swapped (button_ok, "clicked", G_CALLBACK (gtk_widget_destroy), dialog);

   gtk_container_add (GTK_CONTAINER (content_area), label);
   gtk_container_add (GTK_CONTAINER (content_area), entry_dim_frames_value);

   gtk_widget_show_all (dialog);
}


static void mark( GtkWidget *widget, gpointer data ){
	int k = atoi((char*)data);
	*bool_marked[k%10][k/10] = gtk_toggle_button_get_active((GtkToggleButton*) widget);
    g_print ("Hello again - %s was pressed\n", (char *) data);
}
static void mark_all( GtkWidget *widget, gpointer data ){
	int i,j;
	for (i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			gtk_toggle_button_set_active(toggle_button[i][j], TRUE);
			*bool_marked[i][j] = TRUE;
		}
	}
    return;
}
static void clear_all( GtkWidget *widget, gpointer data ){
	int i,j;
	for (i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			gtk_toggle_button_set_active(toggle_button[i][j], FALSE);
			*bool_marked[i][j] = FALSE;
		}
	}
    return;
}

static void apply_color( GtkWidget *widget, gpointer data ){
	int i,j;
	GdkRGBA rgba;
	for (i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			if(*bool_marked[i][j]){
				gtk_color_button_get_rgba((GtkColorButton*)data,&rgba);
				gtk_color_button_set_rgba(color_button[i][j], &rgba);

			}
		}
	}
    return;
}

static gboolean delete_event( GtkWidget *widget, GdkEvent  *event, gpointer data ){
    gtk_main_quit ();
    return FALSE;
}


static void update_current(GtkWidget *widget, gpointer data){
	int i, j;
	frame_update_current(color_button);
	printf("[%d]",frame_header->current_frame->id);
	printf("[next:%p]",frame_header->current_frame->next_frame);
	printf("[prev:%p]",frame_header->current_frame->prev_frame);
	for(i = 0; i<6; i++){
		for(j = 0; j<10; j++){
			printf("[%s]",frame_header->current_frame->frame[j][i]);
		}
		printf("\n");
	}

}
static void insert_before(GtkWidget *widget, gpointer data){
	frame_insert_front(color_button);

	update_label();
//	frame_show_next(color_button);

}
static void insert_behind(GtkWidget *widget, gpointer data){
	frame_insert_back(color_button);

	update_label();

//	frame_show_prev(color_button);

}

static void color_changed(GtkWidget *widget, gpointer data){
	printf("Color_changed_starts\n");
	int i, j;
	GdkRGBA rgba;
	gchar color_string[13];
	for(i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			gtk_color_button_get_rgba(color_button[i][j], &rgba);
			//free(frame_header->current_frame->frame[i][j]);
			get_short_color_string(color_string, rgba);
			gtk_button_set_label ((GtkButton*)toggle_button[i][j], color_string);
		}
	}
	printf("Color_changed_ends\n");
//	GdkColor color;
//	int i, j;
//	gchar* color_string;
/*	for(i = 0; i<10;i++){
		for(j = 0; j<6;j++){
			gtk_color_button_get_color(color_button[i][j], &color);
			strcpy(color_string, gdk_color_to_string (&color));
			get_short_color_string(color_string);
			gtk_button_set_label ((GtkButton*)toggle_button[i][j], color_string);
		}
	}*/
	printf("Color_changed_ends\n");
	//free(color_string);
}

static void show_prev(GtkWidget *widget, gpointer data){
	frame_show_prev(color_button);
	color_changed(widget, NULL);
	update_label();
}

static void show_next(GtkWidget *widget, gpointer data){
	frame_show_next(color_button);
	color_changed(widget, NULL);
	update_label();
}

static void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data){
    switch (event->keyval)
    {
        case GDK_KEY_Left:
        	show_prev(widget, data);
            break;
        case GDK_KEY_Right:
        	show_next(widget, data);
            break;
        default:
            return;  /* propogate event */
    }
}

void grid_init(GtkGrid *grid){
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
			g_signal_connect ((GtkWidget*)color_button[i][j], "color-set", G_CALLBACK (color_changed), (gpointer) strpoint);
			g_signal_connect ((GtkWidget*)toggle_button[i][j], "clicked", G_CALLBACK (mark), (gpointer) strpoint);

		}
	}
}





int main( int argc, char *argv[] ){



    GtkWidget *button_quit, *button_mark, *button_clear, *button_apply_color;
    GtkWidget *button_insert_back, *button_insert_front, *button_update_current;
    GtkWidget *button_prev, *button_next, *button_fb, *button_ff, *button_start, *button_end;
    GtkWidget *button_dim_f, *button_dim_b;



    GtkColorButton *color_master;
    GtkGrid *grid;

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

    printf("etter\n");
    frame_header_init();
    gtk_init (&argc, &argv);


    /* Adding window with options */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Table");
    g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    /* Adding grid with options */
    grid = (GtkGrid*)gtk_grid_new();
    grid_init(grid);
    gtk_grid_set_row_homogeneous(grid, TRUE);
    gtk_grid_set_column_homogeneous(grid, TRUE);

    gtk_container_add (GTK_CONTAINER (window), (GtkWidget*)grid);

    button_quit = gtk_button_new_with_label("Quit");
    button_mark = gtk_button_new_with_label("Mark all");
    button_clear = gtk_button_new_with_label("Clear all");

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

    gtk_button_set_image ((GtkButton*)button_prev, gtk_image_new_from_file ("images/prev.png"));
    gtk_button_set_image ((GtkButton*)button_next, gtk_image_new_from_file ("images/next.png"));
    gtk_button_set_image ((GtkButton*)button_fb, gtk_image_new_from_file ("images/fb.png"));
    gtk_button_set_image ((GtkButton*)button_ff, gtk_image_new_from_file ("images/ff.png"));
    gtk_button_set_image ((GtkButton*)button_start, gtk_image_new_from_file ("images/start.png"));
    gtk_button_set_image ((GtkButton*)button_end, gtk_image_new_from_file ("images/end.png"));



    label_frame_number = gtk_label_new ("Frame 1 of 1");
    update_label();



    color_master = (GtkColorButton*)gtk_color_button_new ();

    g_signal_connect (button_mark, "clicked", G_CALLBACK (mark_all), NULL);
    g_signal_connect (button_clear, "clicked", G_CALLBACK (clear_all), NULL);
    g_signal_connect (button_quit, "clicked", G_CALLBACK (delete_event), NULL);
    g_signal_connect (button_apply_color, "clicked", G_CALLBACK (apply_color), (gpointer) color_master);
    g_signal_connect (button_apply_color, "clicked", G_CALLBACK (color_changed), NULL);
    g_signal_connect (button_update_current, "clicked", G_CALLBACK (update_current), NULL);
    g_signal_connect (button_prev, "clicked", G_CALLBACK (show_prev), NULL);
    g_signal_connect (button_next, "clicked", G_CALLBACK (show_next), NULL);
    g_signal_connect (button_insert_back, "clicked", G_CALLBACK (insert_behind), NULL);
    g_signal_connect (button_insert_front, "clicked", G_CALLBACK (insert_before), NULL);
    g_signal_connect (button_dim_f, "clicked", G_CALLBACK (auto_dim_popup), (gpointer) TRUE);
    g_signal_connect (button_dim_b, "clicked", G_CALLBACK (auto_dim_popup), (gpointer) FALSE);


    g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (on_key_press), NULL);


	for(i = 0; i<10;i++){
		for(j = 0; j<6;j++){
			gtk_grid_attach(grid,(GtkWidget*) color_button[i][j], i, j*3+1, 1, 2);
			gtk_grid_attach(grid,(GtkWidget*) toggle_button[i][j], i, j*3+3, 1, 1);
			gtk_widget_show ((GtkWidget*)color_button[i][j]);
			gtk_widget_show ((GtkWidget*)toggle_button[i][j]);
		}
	}
    gtk_grid_attach (grid, (GtkWidget*)button_mark, 0, 20, 5, 1);
    gtk_grid_attach (grid, (GtkWidget*)button_clear, 5, 20, 5, 1);
    gtk_grid_attach (grid, (GtkWidget*)button_quit, 0, 21, 10, 1);

    gtk_grid_attach (grid, (GtkWidget*)color_master, 11, 10, 1, 2);
    gtk_grid_attach (grid, (GtkWidget*)button_apply_color, 10, 12, 3, 1);

    gtk_grid_attach (grid, (GtkWidget*)button_update_current, 11, 5, 6, 1);
    gtk_grid_attach (grid, (GtkWidget*)button_insert_back, 11, 6, 3, 1);
    gtk_grid_attach (grid, (GtkWidget*)button_insert_front, 14, 6, 3, 1);

    gtk_grid_attach (grid, (GtkWidget*)button_prev, 2, 0, 1, 1);
    gtk_grid_attach (grid, (GtkWidget*)button_next, 7, 0, 1, 1);
    gtk_grid_attach (grid, (GtkWidget*)button_fb, 1, 0, 1, 1);
	gtk_grid_attach (grid, (GtkWidget*)button_ff, 8, 0, 1, 1);
	gtk_grid_attach (grid, (GtkWidget*)button_start, 0, 0, 1, 1);
	gtk_grid_attach (grid, (GtkWidget*)button_end, 9, 0, 1, 1);

	gtk_grid_attach (grid, (GtkWidget*)button_dim_f, 14, 8, 3, 1);
	gtk_grid_attach (grid, (GtkWidget*)button_dim_b, 11, 8, 3, 1);

    gtk_grid_attach (grid, (GtkWidget*)label_frame_number, 3, 0, 4, 1);

    //gtk_grid_attach (grid, (GtkWidget*)entry_dim_frames_value, 11, 0, 3, 1);

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

	gtk_widget_show ((GtkWidget*)color_master);
	gtk_widget_show (button_apply_color);

	gtk_widget_show (label_frame_number);



//	gtk_widget_show (frame_label_frame_number);

	gtk_widget_show ((GtkWidget*)grid);

	gtk_widget_show (window);


    gtk_main ();

    return 0;
}

