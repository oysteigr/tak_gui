#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

static const gint X_SIZE = 10;
static const gint Y_SIZE = 6;

struct Frame{
	gint id;
	gchar*** frame;
	struct Frame* next_frame;
	struct Frame* prev_frame;
};
typedef struct Frame Frame;

typedef struct{
	gint counter;
	gint selected_number;
	gint last_id_added;
	Frame* start_frame;
	Frame* current_frame;
	Frame* end_frame;
} Frame_header;

GtkColorButton *color_master;
GtkColorButton*** color_button;
GtkToggleButton*** toggle_button;
GdkRGBA*** color_copy;
gboolean*** bool_marked;

GtkWidget *label_frame_number;
GtkWindow *window;

Frame_header* frame_header;

gchar* window_title;

#endif
