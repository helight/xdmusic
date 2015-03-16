#include <gtk/gtk.h>

gboolean on_window_destroy_event (GtkWidget *widget, GdkEvent *event,
				gpointer user_data);
void tray_menu() ;
void mini_show(GtkWidget *widget, gpointer data);
void callback_icon(GtkStatusIcon *status_icon,gpointer data);
void xlist_pressed(GtkWidget *widget, gpointer data);
void xplay_pressed(GtkWidget *widget, GdkEventButton *event, gpointer data);
void xplay_next(GtkWidget *widget, gpointer data);
void xplay_pre(GtkWidget *widget, gpointer data);
gboolean xmusic_list_button_press_event(GtkWidget *widget, 
				GdkEventButton  *event,	gpointer user_data);
void xmusic_list_get_selection_row(GtkCList *gtkclist,gint row,gint column,
				GdkEventButton *event,gpointer user_data);
gboolean on_tray_play_pause (GtkWidget *widget, GdkEvent *event, gpointer user_data);
gboolean on_tray_prev (GtkWidget *widget, GdkEvent *event, gpointer user_data);
gboolean on_tray_next (GtkWidget *widget, GdkEvent *event, gpointer user_data);
