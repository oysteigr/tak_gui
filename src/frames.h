

void frame_init();
void frame_header_init();

void frame_update_current(GtkColorButton*** color_buttons);
void frame_insert_front(GtkColorButton*** color_buttons);
void frame_insert_back(GtkColorButton*** color_buttons);
gboolean frame_delete();

void frame_make_black();

void frame_show_prev(GtkColorButton*** color_buttons);
void frame_show_next(GtkColorButton*** color_buttons);
void frame_load_colors(GtkColorButton*** color_buttons);

void frame_auto_dim(gint number_of_steps, GtkColorButton*** color_buttons, gboolean forward);

void frame_store_frame(char string[],gboolean create_new);

void get_short_color_string(gchar* color_string, GdkRGBA rgba);

void frame_shift(gint up, gint left, gint x, gint y);

void frame_copy();
void frame_paste();
