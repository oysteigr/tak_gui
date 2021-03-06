void callback_init();

gboolean callback_delete_event( GtkWidget *widget, GdkEvent  *event, gpointer data );

void callback_auto_dim_run ( GtkWidget *widget, gpointer data );
void callback_auto_dim_popup ( GtkWidget *widget, gpointer data );

void callback_mark( GtkWidget *widget, gpointer data );
void callback_mark_all( GtkWidget *widget, gpointer data );
void callback_unmark_all( GtkWidget *widget, gpointer data );
void callback_mark_row( GtkWidget *widget, gpointer data );
void callback_mark_column( GtkWidget *widget, gpointer data );
void callback_mark_inverse( GtkWidget *widget, gpointer data );

void callback_apply_color( GtkWidget *widget, gpointer data );

void callback_update_current(GtkWidget *widget, gpointer data);

void callback_insert_before(GtkWidget *widget, gpointer data);
void callback_insert_behind(GtkWidget *widget, gpointer data);

void callback_color_changed(GtkWidget *widget, gpointer data);

void callback_show_prev(GtkWidget *widget, gpointer data);
void callback_show_next(GtkWidget *widget, gpointer data);
void callback_jump_prev(GtkWidget *widget, gpointer data);
void callback_jump_next(GtkWidget *widget, gpointer data);
void callback_jump_start(GtkWidget *widget, gpointer data);
void callback_jump_end(GtkWidget *widget, gpointer data);

void callback_copy(GtkWidget *widget, gpointer data);
void callback_paste(GtkWidget *widget, gpointer data);

void callback_on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data);


void callback_save( GtkWidget *widget, gpointer data);
void callback_save_as( GtkWidget *widget, gpointer data);
void callback_load( GtkWidget *widget, gpointer data);
void callback_load_new( GtkWidget *widget, gpointer data);

void callback_delete_current( GtkWidget *widget, gpointer data);
void callback_delete_multiple( GtkWidget *widget, gpointer data);
void callback_delete_all( GtkWidget *widget, gpointer data);

void callback_shift_up( GtkWidget *widget, gpointer data);
void callback_shift_down( GtkWidget *widget, gpointer data);
void callback_shift_left( GtkWidget *widget, gpointer data);
void callback_shift_right( GtkWidget *widget, gpointer data);

