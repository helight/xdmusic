/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget* create_xmusic (struct xmusic *xmusic)
{
	GtkWidget *xmusic_window;
	GdkPixbuf *panel_icon_pixbuf;
	GtkStatusIcon* trayIcon;
	GtkWidget *vbox1;
	
	GtkWidget *xmusic_title;
	GtkWidget *xlogo_img;
	GtkWidget *xtitle;
	GtkWidget *xmini;
	GtkWidget *xmini_img;
	GtkWidget *xquit;
	GtkWidget *xquit_img;

	GtkWidget *music_ctl;
	GtkWidget *xpre;
	GtkWidget *xpre_img;
	GtkWidget *xplay;
	GtkWidget *xpy_img;
	GtkWidget *xnext;
	GtkWidget *xnt_img;
	GtkWidget *xlist;
	GtkWidget *xls_img;
	GtkWidget *xtime;

	GtkWidget *xmusic_bar;

	GtkWidget *xmusic_note;
	GtkWidget *xmusic_list;
	GtkWidget *scrolle_list;
	GtkWidget *playmusic;
	GtkWidget *xstate;
	
	PangoFontDescription *fontdesc_title_time; 
	GdkPixbuf *xmusic_icon_pixbuf;
	CursorOffset* icon_pos;

	xmusic_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (xmusic_window), _("XDMusic"));
	gtk_window_set_default_size (GTK_WINDOW (xmusic_window), 260, -1);
	gtk_window_set_position(GTK_WINDOW(xmusic_window), GTK_WIN_POS_CENTER);
	//gtk_window_set_destroy_with_parent (GTK_WINDOW (xmusic_window), TRUE);
	gtk_window_set_decorated(GTK_WINDOW (xmusic_window), FALSE);

	gtk_widget_set_events (xmusic_window,
	    gtk_widget_get_events (xmusic_window) |
	    GDK_BUTTON_MOTION_MASK |
	    GDK_POINTER_MOTION_HINT_MASK |
	    GDK_BUTTON_PRESS_MASK);
	
	gtk_widget_realize (xmusic_window);
	xmusic_icon_pixbuf = create_pixbuf ("xdmusic.png");
	if (xmusic_icon_pixbuf)
	{
		gtk_window_set_icon (GTK_WINDOW (xmusic_window), xmusic_icon_pixbuf);
		gdk_pixbuf_unref (xmusic_icon_pixbuf);
	}	
	

	panel_icon_pixbuf = create_pixbuf ("logo.png");
	trayIcon = gtk_status_icon_new_from_pixbuf (panel_icon_pixbuf);
	gtk_status_icon_set_tooltip(trayIcon,"XDMusic");
	g_signal_connect((gpointer)trayIcon, "activate", G_CALLBACK(callback_icon), xmusic_window);
	g_signal_connect((gpointer)trayIcon ,"popup-menu" ,G_CALLBACK(tray_menu),NULL);
	
	vbox1 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox1);
	gtk_container_add (GTK_CONTAINER (xmusic_window), vbox1);
	
	xmusic_title = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (xmusic_title);
	gtk_box_pack_start (GTK_BOX (vbox1), xmusic_title, FALSE, FALSE, 0);

	xlogo_img = create_pixmap("logo.png");
	gtk_widget_show (xlogo_img);
	gtk_box_pack_start (GTK_BOX (xmusic_title), xlogo_img, FALSE, FALSE, 0);
	
	xtitle = gtk_label_new (_(" XDMusic "));
	gtk_widget_show (xtitle);
	gtk_widget_set_size_request (xtitle, 250, 20);
	gtk_misc_set_alignment (GTK_MISC (xtitle), 0.08, 0.5);
	gtk_box_pack_start (GTK_BOX (xmusic_title), xtitle, FALSE, FALSE, 0);
	
	fontdesc_title_time= pango_font_description_from_string("FreeSans Bold 10"); 
	gtk_widget_modify_font(xtitle, fontdesc_title_time); 
	pango_font_description_free(fontdesc_title_time); 

	xmini = gtk_button_new();
	gtk_button_set_relief (GTK_BUTTON (xmini), GTK_RELIEF_NONE);	
	gtk_widget_show (xmini);
	gtk_box_pack_start (GTK_BOX (xmusic_title), xmini, FALSE, FALSE, 0);
	xmini_img = create_pixmap("mini.png");
	gtk_widget_show (xmini_img);
	gtk_container_add (GTK_CONTAINER (xmini), xmini_img);
	
	xquit = gtk_button_new();
	gtk_button_set_relief (GTK_BUTTON (xquit), GTK_RELIEF_NONE);
	gtk_widget_show (xquit);
	gtk_box_pack_start (GTK_BOX (xmusic_title), xquit, FALSE, FALSE, 0);
	xquit_img = create_pixmap("quit.png");
	gtk_widget_show (xquit_img);
	gtk_container_add (GTK_CONTAINER (xquit), xquit_img);
		
	music_ctl = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (music_ctl);
	gtk_box_pack_start (GTK_BOX (vbox1), music_ctl, FALSE, FALSE, 0);

/*.......................................................................................*/

	xlist = gtk_button_new();
	gtk_button_set_relief (GTK_BUTTON (xlist), GTK_RELIEF_NONE);
	gtk_widget_show (xlist);
	gtk_box_pack_start (GTK_BOX (music_ctl), xlist, FALSE, FALSE, 0);
	xls_img = create_pixmap("list.png");
	gtk_widget_show (xls_img);
	gtk_container_add (GTK_CONTAINER (xlist), xls_img);

	xpre = gtk_button_new();
	gtk_widget_show (xpre);
	gtk_button_set_relief (GTK_BUTTON (xpre), GTK_RELIEF_NONE);
	gtk_box_pack_start (GTK_BOX (music_ctl), xpre, FALSE, FALSE, 0);
	xpre_img = create_pixmap("pre.png");
	gtk_widget_show (xpre_img);
	gtk_container_add (GTK_CONTAINER (xpre), xpre_img);

	xplay = gtk_button_new();
	gtk_widget_show (xplay);
	gtk_button_set_relief (GTK_BUTTON (xplay), GTK_RELIEF_NONE);
	gtk_box_pack_start (GTK_BOX (music_ctl), xplay, FALSE, FALSE, 0);
	xpy_img = create_pixmap("play.png");
	gtk_widget_show (xpy_img);
	gtk_container_add (GTK_CONTAINER (xplay), xpy_img);

	xnext = gtk_button_new();
	gtk_widget_show (xnext);
	gtk_button_set_relief (GTK_BUTTON (xnext), GTK_RELIEF_NONE);
	gtk_box_pack_start (GTK_BOX (music_ctl), xnext, FALSE, FALSE, 0);
	xnt_img = create_pixmap("next.png");
	gtk_widget_show (xnt_img);
	gtk_container_add (GTK_CONTAINER (xnext), xnt_img);

	xtime = gtk_label_new (_("00:00 - 00:00"));
	gtk_widget_show (xtime);
	gtk_box_pack_start (GTK_BOX (music_ctl), xtime, FALSE, FALSE, 0);
/*..............................................................................*/
	xmusic_bar = gtk_hscale_new_with_range(0, 100, 1);
	gtk_scale_set_draw_value(GTK_SCALE(xmusic_bar), FALSE);
	gtk_range_set_update_policy(GTK_RANGE(xmusic_bar), GTK_UPDATE_DISCONTINUOUS);
	gtk_widget_show (xmusic_bar);
	gtk_box_pack_start (GTK_BOX (vbox1), xmusic_bar, FALSE, TRUE, 0);
//	g_signal_connect(G_OBJECT(bar), "value_changed", G_CALLBACK(seek_value_changed), NULL);
/*..............................................................................

	music_note = gtk_notebook_new ();
	gtk_widget_show (music_note);
	gtk_box_pack_start (GTK_BOX (vbox1), music_note, TRUE, TRUE, 0);
	gtk_widget_set_size_request (music_note, -1, 150);
*/	
	scrolle_list = gtk_scrolled_window_new (NULL, NULL);
	//gtk_widget_show (scrolle_list);
	gtk_container_add (GTK_CONTAINER (vbox1), scrolle_list);
	//gtk_widget_set_size_request (scrolledwindow_list, 150, -1);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolle_list), GTK_POLICY_NEVER,  GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolle_list), GTK_SHADOW_IN);
	
	xmusic_list = gtk_clist_new (1);
	//gtk_widget_show (music_list);
	gtk_container_add (GTK_CONTAINER (scrolle_list), xmusic_list);
	gtk_widget_set_size_request (xmusic_list, -1, 150);
	
	fontdesc_title_time= pango_font_description_from_string("FreeSans Bold 10"); 
	gtk_widget_modify_font(xmusic_list, fontdesc_title_time); 
	pango_font_description_free(fontdesc_title_time); 
/*
	playmusic = gtk_label_new (_("Play"));
	gtk_widget_show (playmusic);
	gtk_notebook_set_tab_label (GTK_NOTEBOOK (music_note), 
		gtk_notebook_get_nth_page (GTK_NOTEBOOK (music_note), 0), playmusic);
	gtk_misc_set_padding (GTK_MISC (playmusic), 5, 0);

	xstate = gtk_label_new (_("xmusic --- V 0.01"));
	gtk_misc_set_alignment (GTK_MISC (xstate), 0.03, 0.5);
	gtk_widget_show (xstate);
	gtk_box_pack_start (GTK_BOX (vbox1), xstate, FALSE, FALSE, 0);
*/
	xmusic->xwindow = xmusic_window;
	xmusic->xtitle = xtitle;
	xmusic->xtime = xtime;
	xmusic->xplay = xplay;
	xmusic->xbar = xmusic_bar;
	xmusic->xlist = xmusic_list;
	xmusic->xscrolle = scrolle_list;
	xmusic->xstate = xstate;
	
	g_signal_connect (xmusic_window, "button_press_event",
		    G_CALLBACK (shape_pressed), (gpointer *)xmusic_window);
	g_signal_connect (xmusic_window, "motion_notify_event",
		    G_CALLBACK (shape_motion), (gpointer *)xmusic_window);
	icon_pos = g_new (CursorOffset, 1);
	g_object_set_data (G_OBJECT (xmusic_window), "cursor_offset", icon_pos);
	
	g_signal_connect(G_OBJECT(xmini), "clicked", G_CALLBACK(mini_show), xmusic_window);
	g_signal_connect(G_OBJECT(xquit), "clicked", G_CALLBACK(on_window_destroy_event), NULL);	
	g_signal_connect(G_OBJECT(xlist), "clicked", G_CALLBACK(xlist_pressed), (gpointer)xmusic);	
	g_signal_connect(G_OBJECT(xplay), "clicked", G_CALLBACK(xplay_pressed), NULL);
	g_signal_connect(G_OBJECT(xnext), "clicked", G_CALLBACK(xplay_next), NULL);
	g_signal_connect(G_OBJECT(xpre), "clicked", G_CALLBACK(xplay_pre), NULL);
	
	g_signal_connect ((gpointer) xmusic_list, "button_press_event",
                    	G_CALLBACK (xmusic_list_button_press_event),
                    	(gpointer)xmusic);                    				
	g_signal_connect((gpointer) xmusic_list,"select_row",
        		G_CALLBACK(xmusic_list_get_selection_row),
        		NULL);

	g_signal_connect ((gpointer) xmusic_window, "delete_event",
		    G_CALLBACK (on_window_destroy_event), NULL);

	return xmusic_window;
}

