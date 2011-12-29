


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

Frame_header* frame_header;

void frame_init();
void frame_header_init();
void frame_delete(Frame *delete_frame);

void frame_update_current(GtkColorButton*** color_buttons);
void frame_insert_front(GtkColorButton*** color_buttons);
void frame_insert_back(GtkColorButton*** color_buttons);
void frame_remove();

void frame_show_prev(GtkColorButton*** color_buttons);
void frame_show_next(GtkColorButton*** color_buttons);

void frame_auto_dim(gint number_of_steps, GtkColorButton*** color_buttons, gboolean forward);

Frame* frame_new();

void get_short_color_string(gchar* color_string, GdkRGBA rgba);
