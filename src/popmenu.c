#include <gtk/gtk.h>

#include "support.h"
#include "popmenu.h"
#include "callbacks.h"

static 

void
on_xcancel_clicked(GtkButton *button, gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(data));
}

void
on_xopen_clicked(GtkButton *button, gpointer data)
{
	GSList *listfiles = NULL;
	listfiles = gtk_file_chooser_get_filenames (GTK_FILE_CHOOSER (data));
	while(listfiles){
			//printf("data: %s\n", listfiles->data);
			add_new_songs(listfiles->data);
			listfiles = listfiles->next;
	};
	gtk_widget_destroy(GTK_WIDGET(data));
}

void create_xmusichoose (void)
{
	GtkWidget *xmusichoose;
	GtkWidget *dialog_vbox1;
	GtkWidget *dialog_action_area1;
	GtkWidget *xcancel;
	GtkWidget *xopen;
	GtkFileFilter* filter;

	xmusichoose = gtk_file_chooser_dialog_new (_("xmusic"), NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL);
	g_object_set (xmusichoose, "select-multiple", TRUE,	NULL);
	gtk_window_set_position (GTK_WINDOW (xmusichoose), GTK_WIN_POS_CENTER);
	gtk_window_set_destroy_with_parent (GTK_WINDOW (xmusichoose), TRUE);
	//gtk_window_set_decorated (GTK_WINDOW (xmusichoose), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW (xmusichoose), GDK_WINDOW_TYPE_HINT_DIALOG);

	dialog_vbox1 = GTK_DIALOG (xmusichoose)->vbox;
	gtk_widget_show (dialog_vbox1);

	dialog_action_area1 = GTK_DIALOG (xmusichoose)->action_area;
	gtk_widget_show (dialog_action_area1);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

	xcancel = gtk_button_new_from_stock ("gtk-cancel");
	gtk_widget_show (xcancel);
	gtk_dialog_add_action_widget (GTK_DIALOG (xmusichoose), xcancel, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (xcancel, GTK_CAN_DEFAULT);

	xopen = gtk_button_new_from_stock ("gtk-open");
	gtk_widget_show (xopen);
	gtk_dialog_add_action_widget (GTK_DIALOG (xmusichoose), xopen, GTK_RESPONSE_OK);
	gtk_container_set_border_width (GTK_CONTAINER (xopen), 2);
	GTK_WIDGET_SET_FLAGS (xopen, GTK_CAN_DEFAULT);

	filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, _("媒体文件"));
    gtk_file_filter_add_pattern(filter,"*.[Mm][Pp][3]");
    gtk_file_filter_add_pattern(filter,"*.[Dd][Tt][Ss]");
    gtk_file_filter_add_pattern(filter,"*.[Ww][Mm][Aa]");
    gtk_file_filter_add_pattern(filter,"*.[Oo][Gg][Gg]");
    gtk_file_filter_add_pattern(filter,"*.[Ww][Aa][Vv]");
    gtk_file_filter_add_pattern(filter,"*.[Aa][Pp][Ee]");
    gtk_file_filter_add_pattern(filter,"*.[Ff][Ll][Aa][Cc]");
    gtk_file_filter_add_pattern(filter,"*.[AA][Cc][Cc]");
    gtk_file_filter_add_pattern(filter,"*.[Oo][Gg][Vv]");
    gtk_file_filter_add_pattern(filter,"*.[Ww][Mm][Vv]");
    gtk_file_filter_add_pattern(filter,"*.[Dd][Aa][Tt]");
    gtk_file_filter_add_pattern(filter,"*.[Mm][Kk][Vv]");
    gtk_file_filter_add_pattern(filter,"*.[Mm][Pp][Gg]");
    gtk_file_filter_add_pattern(filter,"*.[Mm][Pp][4]");
    gtk_file_filter_add_pattern(filter,"*.[Rr][Mm]");
    gtk_file_filter_add_pattern(filter,"*.[Rr][Mm][Vv][Bb]");
    gtk_file_filter_add_pattern(filter,"*.[Aa][Vv][Ii]");
    gtk_file_filter_add_pattern(filter,"*.[Ff][Ll][Vv]");
    gtk_file_filter_add_pattern(filter,"*.[Cc][Uu][Ee]");
    gtk_file_filter_add_pattern(filter,"*.[Mm][3][Uu]");
    gtk_file_filter_add_pattern(filter,"*.[Mm][4][Aa]");
    gtk_file_filter_add_pattern(filter,"*.[Rr][Aa][Mm]");
    gtk_file_filter_add_pattern(filter,"*.[Aa][Ss][Xx]");
    gtk_file_filter_add_pattern(filter,"*.[Aa][Aa][Cc]");
    gtk_file_filter_add_pattern(filter,"*.[Mm][Ii][Dd]");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(xmusichoose),filter);
    
	g_signal_connect ((gpointer) xcancel, "clicked",
					G_CALLBACK (on_xcancel_clicked),
					(gpointer)xmusichoose);
	g_signal_connect ((gpointer) xopen, "clicked",
					G_CALLBACK (on_xopen_clicked),
					(gpointer)xmusichoose);

	gtk_widget_grab_default (xopen);
	gtk_widget_show_all(xmusichoose);
}

void create_xlist_popmenu() 
{
	GtkWidget *popup_menu_xlist = gtk_menu_new ();
	GtkWidget *ximport;

	ximport = gtk_image_menu_item_new_with_mnemonic (_("Import Files"));
	gtk_widget_show (ximport);
	gtk_menu_append (GTK_MENU_SHELL (popup_menu_xlist), ximport);

	g_signal_connect ((gpointer) ximport, "activate",G_CALLBACK (create_xmusichoose),NULL);

	gtk_widget_show_all(popup_menu_xlist);
	popup_menu(popup_menu_xlist,0,0);
}

void tray_menu() 
{
	GtkWidget *tray_menu = gtk_menu_new ();
	GtkWidget *tray_play;
	GtkWidget *tray_pause;
	GtkWidget *tray_prev;
	GtkWidget *tray_next;
	GtkWidget *tray_quit;
	GtkWidget *image;

	tray_play = gtk_image_menu_item_new_with_mnemonic (_("Play"));
	gtk_widget_show (tray_play);
	gtk_menu_append (GTK_MENU_SHELL (tray_menu), tray_play);

	tray_pause = gtk_image_menu_item_new_with_mnemonic (_("Pause"));
	gtk_widget_show (tray_pause);
	gtk_menu_append (GTK_MENU_SHELL (tray_menu), tray_pause);
	
	tray_prev = gtk_image_menu_item_new_with_mnemonic (_("Prev"));
	gtk_widget_show (tray_prev);
	gtk_menu_append (GTK_MENU_SHELL (tray_menu), tray_prev);

	tray_next = gtk_image_menu_item_new_with_mnemonic (_("Next"));
	gtk_widget_show (tray_next);
	gtk_menu_append (GTK_MENU_SHELL (tray_menu), tray_next);

	tray_quit = gtk_image_menu_item_new_with_mnemonic (_("Quit"));
	gtk_widget_show (tray_quit);
	gtk_menu_append (GTK_MENU_SHELL (tray_menu), tray_quit);

	image = gtk_image_new_from_stock (GTK_STOCK_QUIT, GTK_ICON_SIZE_MENU);
	gtk_widget_show (image);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (tray_quit), image);
	
	g_signal_connect ((gpointer) tray_play, "activate",G_CALLBACK (on_tray_play_pause),NULL);
	g_signal_connect ((gpointer) tray_pause, "activate",G_CALLBACK (on_tray_play_pause),NULL);
	g_signal_connect ((gpointer) tray_prev, "activate",G_CALLBACK (on_tray_prev),NULL);
	g_signal_connect ((gpointer) tray_next, "activate",G_CALLBACK (on_tray_next),NULL);
	g_signal_connect ((gpointer) tray_quit, "activate",G_CALLBACK (on_window_destroy_event),NULL);

	gtk_widget_show_all((GtkWidget *)tray_menu);
	popup_menu(tray_menu,0,0);
}
