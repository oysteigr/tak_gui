#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "frames.h"
#include "global_variables.h"
#include "load_save.h"
#include "callbacks.h"

void callback_on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data){
	if(event->state & GDK_CONTROL_MASK){
		switch (event->keyval){
			case GDK_KEY_a:
				callback_mark_all(widget, data);
				break;
			case GDK_KEY_d:
				callback_unmark_all(widget, data);
				break;
			case GDK_KEY_s:
				callback_save(widget, data);
				break;
			case GDK_KEY_l:
				callback_load(widget, data);
				break;
			case GDK_KEY_i:
				callback_mark_inverse(widget, data);
				break;
			case GDK_KEY_c:
				callback_copy(widget, data);
				break;
			case GDK_KEY_v:
				callback_paste(widget, data);
				break;
			case GDK_KEY_KP_1:
				callback_mark_row(widget, (gpointer)0);
				break;
			case GDK_KEY_KP_2:
				callback_mark_row(widget, (gpointer)1);
				break;
			case GDK_KEY_KP_3:
				callback_mark_row(widget, (gpointer)2);
				break;
			case GDK_KEY_KP_4:
				callback_mark_row(widget, (gpointer)3);
				break;
			case GDK_KEY_KP_5:
				callback_mark_row(widget, (gpointer)4);
				break;
			case GDK_KEY_KP_6:
				callback_mark_row(widget,(gpointer) 5);
				break;
			case GDK_KEY_1:
				callback_mark_row(widget, (gpointer)0);
				break;
			case GDK_KEY_2:
				callback_mark_row(widget, (gpointer)1);
				break;
			case GDK_KEY_3:
				callback_mark_row(widget, (gpointer)2);
				break;
			case GDK_KEY_4:
				callback_mark_row(widget, (gpointer)3);
				break;
			case GDK_KEY_5:
				callback_mark_row(widget, (gpointer)4);
				break;
			case GDK_KEY_6:
				callback_mark_row(widget,(gpointer) 5);
				break;
			case GDK_KEY_Left:
				callback_insert_before(widget, data);
				break;
			case GDK_KEY_Right:
				callback_insert_behind(widget, data);
				break;
			default:
				return;
		}
	}
	else if(event->state & GDK_MOD1_MASK){
		switch (event->keyval){
			case GDK_KEY_s:
				callback_update_current(widget, data);
				break;
			case GDK_KEY_a:
				callback_apply_color(widget, (gpointer)color_master);
				break;
			case GDK_KEY_c:
				gtk_button_clicked((GtkButton*)color_master);
				break;
			case GDK_KEY_KP_1:
				callback_mark_column(widget, (gpointer)0);
				break;
			case GDK_KEY_KP_2:
				callback_mark_column(widget, (gpointer)1);
				break;
			case GDK_KEY_KP_3:
				callback_mark_column(widget, (gpointer)2);
				break;
			case GDK_KEY_KP_4:
				callback_mark_column(widget, (gpointer)3);
				break;
			case GDK_KEY_KP_5:
				callback_mark_column(widget, (gpointer)4);
				break;
			case GDK_KEY_KP_6:
				callback_mark_column(widget, (gpointer)5);
				break;
			case GDK_KEY_KP_7:
				callback_mark_column(widget, (gpointer)6);
				break;
			case GDK_KEY_KP_8:
				callback_mark_column(widget, (gpointer)7);
				break;
			case GDK_KEY_KP_9:
				callback_mark_column(widget, (gpointer)8);
				break;
			case GDK_KEY_KP_0:
				callback_mark_column(widget, (gpointer)9);
				break;
			case GDK_KEY_1:
				callback_mark_column(widget, (gpointer)0);
				break;
			case GDK_KEY_2:
				callback_mark_column(widget, (gpointer)1);
				break;
			case GDK_KEY_3:
				callback_mark_column(widget, (gpointer)2);
				break;
			case GDK_KEY_4:
				callback_mark_column(widget, (gpointer)3);
				break;
			case GDK_KEY_5:
				callback_mark_column(widget, (gpointer)4);
				break;
			case GDK_KEY_6:
				callback_mark_column(widget, (gpointer)5);
				break;
			case GDK_KEY_7:
				callback_mark_column(widget, (gpointer)6);
				break;
			case GDK_KEY_8:
				callback_mark_column(widget, (gpointer)7);
				break;
			case GDK_KEY_9:
				callback_mark_column(widget, (gpointer)8);
				break;
			case GDK_KEY_0:
				callback_mark_column(widget, (gpointer)9);
				break;
			case GDK_KEY_Up:
				callback_shift_up(widget, data);
				break;
			case GDK_KEY_Down:
				callback_shift_down(widget, data);
				break;
			case GDK_KEY_Left:
				callback_shift_left(widget, data);
				break;
			case GDK_KEY_Right:
				callback_shift_right(widget, data);
				break;
			default:
				return;
		}
	}
	else{
		switch (event->keyval){
			case GDK_KEY_Left:
				callback_show_prev(widget, data);
				break;
			case GDK_KEY_Right:
				callback_show_next(widget, data);
				break;
			case GDK_KEY_Page_Down:
				callback_jump_prev(widget, data);
				break;
			case GDK_KEY_Page_Up:
				callback_jump_next(widget, data);
				break;
			case GDK_KEY_Home:
				callback_jump_start(widget, data);
				break;
			case GDK_KEY_End:
				callback_jump_end(widget, data);
				break;
			case GDK_KEY_Delete:
				callback_delete_current(widget, data);
				break;
			case GDK_KEY_Escape:
				frame_load_colors(color_button);
				callback_color_changed(widget, data);
				break;
			default:
				return;
		}

	}
}
