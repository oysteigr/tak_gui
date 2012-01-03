#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "frames.h"

Frame* frame_new(){
	int i, j;
	Frame *new_frame;
	new_frame = malloc(sizeof(Frame));
	new_frame->frame = malloc(10*sizeof(gchar**));
    for(i = 0; i<10;i++){
    	new_frame->frame[i] = malloc(6*sizeof(gchar*));
    	for(j = 0; j<6; j++){
    		new_frame->frame[i][j] = NULL;
    		new_frame->frame[i][j] = malloc(8*sizeof(char));
    	}
    }
    new_frame->next_frame = NULL;
    new_frame->prev_frame = NULL;
    frame_header->last_id_added++;
	frame_header->counter++;
    new_frame->id = frame_header->last_id_added++;

    return new_frame;
}

void frame_header_init(){
	frame_header = malloc(sizeof(Frame_header));
	frame_header->counter = 0;
	frame_header->last_id_added = 0;

	Frame *new_frame = frame_new();
	frame_header->start_frame = new_frame;
	frame_header->end_frame = new_frame;
	frame_header->current_frame = new_frame;
	frame_header->selected_number = 1;
	printf("ran frame_header_init\n");

}

void frame_free(Frame *delete_frame){
	int i, j;
    for(i = 0; i<10; i++){
    	for(j = 0; j<6; j++){
    		free(delete_frame->frame[i][j]);
    	}
    	free(delete_frame->frame[i]);
    }
    free(delete_frame->frame);
	free(delete_frame);
}

void frame_delete(){

}

void frame_update_current(GtkColorButton*** color_buttons){
	int i, j;
	GdkRGBA rgba;
	for(i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			gtk_color_button_get_rgba(color_buttons[i][j], &rgba);
			get_short_color_string(frame_header->current_frame->frame[i][j], rgba);
		}
	}
	printf("updated current\n");
}

void frame_create_front_frame(){
		Frame *new_frame = frame_new();
		if(frame_header->current_frame->next_frame == NULL){

			frame_header->end_frame = new_frame;
			new_frame->next_frame = NULL;
			frame_header->current_frame->next_frame = new_frame;
			new_frame->prev_frame = frame_header->current_frame;
		}
		else{
			frame_header->current_frame->next_frame->prev_frame = new_frame;
			new_frame->next_frame = frame_header->current_frame->next_frame;
			frame_header->current_frame->next_frame = new_frame;
			new_frame->prev_frame = frame_header->current_frame;
		}
		frame_header->current_frame = new_frame;
		frame_header->selected_number++;

}

void frame_insert_front(GtkColorButton*** color_buttons){

	frame_create_front_frame();

	frame_update_current(color_buttons);


	printf("inserted front\n");


}

void frame_create_back_frame(){
		Frame *new_frame = frame_new();
		if(frame_header->current_frame->prev_frame == NULL){
			frame_header->start_frame = new_frame;
			new_frame->prev_frame = NULL;
			frame_header->current_frame->prev_frame = new_frame;
			new_frame->next_frame = frame_header->current_frame;
		}
		else{
			frame_header->current_frame->prev_frame->next_frame = new_frame;
			new_frame->prev_frame = frame_header->current_frame->prev_frame;
			frame_header->current_frame->prev_frame = new_frame;
			new_frame->next_frame = frame_header->current_frame;
		}
		frame_header->current_frame = new_frame;
}

void frame_insert_back(GtkColorButton*** color_buttons){
	frame_create_back_frame();

	frame_update_current(color_buttons);

	printf("inserted back\n");
}


void frame_load_colors(GtkColorButton*** color_buttons){
	int i, j;
	GdkRGBA rgba;
	for(i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			gdk_rgba_parse(&rgba, frame_header->current_frame->frame[i][j]);
			gtk_color_button_set_rgba(color_buttons[i][j], &rgba);
		}
	}
	printf("loaded colors\n");
}

void frame_show_prev(GtkColorButton*** color_buttons){
	if(frame_header->current_frame->prev_frame == NULL){
		printf("show next but prev frame=NULL\n");
		return;
	}
	else{
		frame_header->current_frame = frame_header->current_frame->prev_frame;
		printf("show prev\n");
		frame_load_colors(color_buttons);
		frame_header->selected_number--;
	}

}

void frame_show_next(GtkColorButton*** color_buttons){
	if(frame_header->current_frame->next_frame == NULL){
		printf("show next but next frame=NULL\n");
		return;
	}
	else{
		frame_header->current_frame = frame_header->current_frame->next_frame;
		printf("show next\n");
		frame_load_colors(color_buttons);
		frame_header->selected_number++;
	}

}

void frame_auto_dim(gint number_of_steps, GtkColorButton*** color_buttons, gboolean forward){
	int i, j, k;
	GdkRGBA rgba_temp, rgba_start, rgba_end;
	Frame *frame_start, *frame_end;
	frame_start = frame_header->current_frame;
	if(forward){
		frame_end = frame_header->current_frame->next_frame;
	}
	else{
		frame_end = frame_header->current_frame->prev_frame;
	}

	for(k = 1; k<number_of_steps - 1; k++){
		if(forward){frame_create_front_frame();}
		else{frame_create_back_frame();}

		for(i = 0; i<10; i++){
			for(j = 0; j<6; j++){
				gdk_rgba_parse(&rgba_start, frame_start->frame[i][j]);
				gdk_rgba_parse(&rgba_end, frame_end->frame[i][j]);
				rgba_temp.red = rgba_start.red + (rgba_end.red - rgba_start.red)*k/number_of_steps;
				rgba_temp.green = rgba_start.green + (rgba_end.green - rgba_start.green)*k/number_of_steps;
				rgba_temp.blue = rgba_start.blue + (rgba_end.blue - rgba_start.blue)*k/number_of_steps;
				get_short_color_string(frame_header->current_frame->frame[i][j], rgba_temp);
			}
		}
	}
	if(forward){
		frame_header->current_frame = frame_header->current_frame->next_frame;
		frame_header->selected_number++;
	}
	else{
		frame_header->current_frame = frame_header->current_frame->prev_frame;
		frame_header->selected_number--;
	}
	frame_load_colors(color_buttons);
}

void frame_store_frame(char string[],gboolean create_new){
	int i,j;
	if(create_new){
		frame_create_back_frame();
	}
	printf("The string:%s\n",string);
	for(i = 0; i<10; i++){
		for(j = 0; j<6; j++){
			strcpy(frame_header->current_frame->frame[i][j],strndup(string+((i*6+j)*7),7));
		}
	}
}

void get_short_color_string(gchar* color_string, GdkRGBA rgba){

	char buffer_r [33], buffer_g [33], buffer_b [33];
	char *buffer_rp, *buffer_gp, *buffer_bp;


	sprintf(buffer_r,"%x",(int)((rgba.red-0.0000001)*256)+256);
	buffer_rp = strndup(buffer_r+1,2);
	sprintf(buffer_g,"%x",(int)((rgba.green-0.0000001)*256)+256);
	buffer_gp = strndup(buffer_g+1,2);
	sprintf(buffer_b,"%x",(int)((rgba.blue-0.0000001)*256)+256);
	buffer_bp = strndup(buffer_b+1,2);
	sprintf(color_string,"#%s%s%s", buffer_rp, buffer_gp, buffer_bp);
	free(buffer_rp);
	free(buffer_gp);
	free(buffer_bp);
	return;
}
