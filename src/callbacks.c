#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "popmenu.h"
#include "play.h"

static int ishow = 0, sta = 0;

void callback_icon(GtkStatusIcon *status_icon,gpointer data)
{
	GtkWidget *main = (GtkWidget *)data;
	if (sta == 0) {
		gtk_widget_hide(main);
		sta = 1;
	} else {
		gtk_widget_show (main);
		sta = 0;
	}
}
void mini_show(GtkWidget *widget, gpointer data)
{
	GtkWidget *main = (GtkWidget *)data;
	if (sta == 0) {
		gtk_widget_hide(main);
		sta = 1;
	} else {
		gtk_widget_show (main);
		sta = 0;
	}
}


gboolean on_window_destroy_event (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	printf("bey world;\n");
	stop_pressed();
	xmusic_quit();
	gtk_main_quit();

	return FALSE;
}

void xplay_pressed(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	xmusic_play_pause();
}

void xlist_pressed(GtkWidget *widget, gpointer data)
{
	struct xmusic *tmp = (struct xmusic *)data;
	if (ishow == 0){
		gtk_widget_set_visible(tmp->xscrolle, TRUE);
		gtk_widget_set_visible(tmp->xlist, TRUE);		
		ishow = 1;
		//printf("size:150\n");
	} else {
		gtk_widget_set_visible(tmp->xscrolle, FALSE);
		gtk_widget_set_visible(tmp->xlist, FALSE);
		gtk_window_resize(GTK_WINDOW (tmp->xwindow), 260, 50);
		ishow = 0;
		//printf("size: 0\n");
	}	
}

void xplay_next(GtkWidget *widget, gpointer data)
{
	play_next();
}

void xplay_pre(GtkWidget *widget, gpointer data)
{
	play_pre();
}

gboolean xmusic_list_button_press_event(GtkWidget *widget,
			GdkEventButton  *event,	gpointer user_data)
{
	GtkWidget *popup_menu_xlist;
  
	if(event->button == BUTTON_RIGHT){
		//printf("butten right\n");
		create_xlist_popmenu();
        return TRUE;
    }
    return FALSE;
}

void xmusic_list_get_selection_row(GtkCList *gtkclist,gint row,gint column,
				GdkEventButton *event,gpointer user_data)
{
	if(event->type==GDK_2BUTTON_PRESS){
		play_this_num(row);	
		//printf("row: %d \n", row);
	}
}

gboolean on_tray_play_pause (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	xmusic_play_pause();
}

gboolean on_tray_prev (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	play_pre();
}

gboolean on_tray_next (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	play_next();
}
