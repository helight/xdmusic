/*
 * Xmusic (Zhwen.org)
 *
 * Copyright (c) 2008-~  Zhwen.org
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: play.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#include <gst/gst.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"
#include "play.h"
#include "xfuns.h"

#define LIST_MAX 4

static GstElement *pipeline = NULL;
static GstElement *audio_sink = NULL;
static struct xmusic *xmusicd;
static struct xmusic_lists xmusic_main;
static int isplay = 0;
static guint time_handl;
static gchar ta[60], tb[25], music_title[256];
static gint64 slen, spos;

static gint64 xmusic_get_current_position ()
{
  gint64 song_position;
  GstFormat fmt = GST_FORMAT_TIME;

  gst_element_query_position (pipeline, &fmt, &song_position);
  return ( song_position );
}

gint64 xmusic_get_current_length ()
{
	gint64 song_length;
	GstFormat fmt = GST_FORMAT_TIME;

	gst_element_query_duration (pipeline, &fmt, &song_length);  
	return ( song_length );
}

static void show_time(void)
{
	 //gtk_label_set_label(xmusicd->xtime, (char)xmusic_get_current_length());
	slen = xmusic_get_current_length();
	spos = xmusic_get_current_position();
	g_snprintf(ta,24,"%02u %02u:%02u%d",GST_TIME_ARGS(spos));
	g_snprintf(tb,24,"%02u %02u:%02u%d",GST_TIME_ARGS(slen));

	ta[8] = 0;
	strcpy(ta,strstr(ta," "));
	tb[8] = 0;
	strcpy(tb,strstr(tb," "));
	strcat(ta,"-");
	strcat(ta,tb);
	gtk_label_set_label((GtkLabel *)xmusicd->xtime, ta);

	GtkAdjustment *adj = gtk_range_get_adjustment((GtkRange *)xmusicd->xbar);
	gtk_adjustment_set_value(adj, 1.0 * spos / slen * 100);

}

static void time_task()
{	
	if(isplay){
		if(!time_handl)
			time_handl = gtk_timeout_add(500, (GtkFunction) show_time, NULL);	
	} else {
		if (time_handl)
			gtk_timeout_remove(time_handl);	
			time_handl = 0;
	}
}

static gboolean xmusic_bus_call (GstBus *bus, GstMessage *msg, gpointer data)
{
	switch (GST_MESSAGE_TYPE (msg)) {

	case GST_MESSAGE_EOS:
		g_print ("End of stream\n");
		gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL);
		isplay = 0;
		time_task();
		play_next();
		break;

	case GST_MESSAGE_ERROR: {
		gchar  *debug;
		GError *error;

		gst_message_parse_error (msg, &error, &debug);
		g_free (debug);

		g_printerr ("Error: %s\n", error->message);
		g_error_free (error);
		break;
	}
	default:
		//printf("tttttttt");
		break;
	}

	return TRUE;
}

static void add_test_songs()
{
	gint i = 0;
	gchar *xmname[LIST_MAX] = {"/home/xding/xproject/xmusic/sound.ogg",
						"/home/xding/xproject/xmusic/today.mp3",
						"/home/xding/xproject/xmusic/Beat_it.mp3",
						"/home/xding/xproject/xmusic/今天.mp3"
						};
	for (i = 0; i < LIST_MAX; i++ ){
		add_new_songs(xmname[i]);
	}					
	
}

static void xmusic_lists_init()
{
	xmusic_main.num = 0;
	xmusic_main.songs = NULL;
	xmusic_main.foucs = NULL;
	xmusic_main.last = NULL;
	xmusic_main.next = NULL;
	strcpy(xmusic_main.name, "xmusic");	
	//add_test_songs();
	xmusic_main.foucs = xmusic_main.songs;
}

static void free_song_list()
{
	struct xmusic_songs* song, *tmp;
	song = xmusic_main.songs;
	if(song){
		song->pre->next = NULL;
		while(song){
			tmp = song->next;
			free(song);
			song = tmp;
			xmusic_main.num -= 1;
		};
	}
}

static void do_play(gchar *xmname)
{
	GstState state;
	GtkWidget *xplay_button;
	GtkWidget *oldImage;
	GtkWidget *newImage;
	
	xplay_button = xmusicd->xplay;
	oldImage = GTK_WIDGET(gtk_container_children(GTK_CONTAINER(xplay_button))->data);
	
	gtk_object_ref(GTK_OBJECT(oldImage));
	gtk_container_remove(GTK_CONTAINER(xplay_button), oldImage);
	
	gst_element_get_state(pipeline, &state, NULL, -1);
	if(state == GST_STATE_PLAYING ) {
		gst_element_set_state(pipeline, GST_STATE_PAUSED);
		isplay = 0;
		time_task();
		newImage = create_pixmap("play.png");
		//return;
	} else if (state == GST_STATE_PAUSED){
		gst_element_set_state(pipeline, GST_STATE_PLAYING);
		isplay = 1;
		time_task();
		newImage = create_pixmap("stop.png");
		//return;
	} else {
		gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL);  
		g_object_set( G_OBJECT ( pipeline ), "uri", xmname, NULL );    
		gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);  
		isplay = 1;
		time_task();
		g_snprintf(music_title, 255, "<span> %s</span>", getlast(xmname));
		gtk_label_set_markup((GtkLabel *)xmusicd->xtitle, _(music_title));
		newImage = create_pixmap("stop.png");
	}
	gtk_container_add(GTK_CONTAINER(xplay_button), newImage);
	gtk_widget_show(newImage);
}

static void xmusic_pause()
{	GtkWidget *xplay_button;
	GtkWidget *oldImage;
	GtkWidget *newImage;
	
	xplay_button = xmusicd->xplay;
	oldImage = GTK_WIDGET(gtk_container_children(GTK_CONTAINER(xplay_button))->data);
	
	gtk_object_ref(GTK_OBJECT(oldImage));
	gtk_container_remove(GTK_CONTAINER(xplay_button), oldImage);
	
	newImage = create_pixmap("play.png");
	gtk_container_add(GTK_CONTAINER(xplay_button), newImage);
	gtk_widget_show(newImage);
	
	gst_element_set_state ( GST_ELEMENT ( pipeline ), GST_STATE_PAUSED);
	isplay = 0;
	time_task();
}

static void xmusic_play()
{
	if(xmusic_main.foucs && xmusic_main.foucs->uri)
		do_play(xmusic_main.foucs->uri);
}

/*
 * pos: 0 next, 1 pre
 */
static gchar *get_music(gint pos)
{
	if (pos == 0){
		xmusic_main.foucs = xmusic_main.foucs->next;
	}else{
		xmusic_main.foucs = xmusic_main.foucs->pre;
	}
}

void play_this_num(gint row)
{
	int i = 0;
	struct xmusic_songs* song, *tmp;
	
	song = xmusic_main.songs;
	for (i = 0; i < row; i++ ){
		tmp = song->next;
		song = tmp;
	}
	xmusic_main.foucs = song;
	if ( pipeline != NULL ){
		gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL); 
	}
	do_play(xmusic_main.foucs->uri);
}

void xmusic_init(struct xmusic *xmusic)
{
	GstBus *bus;

	/* initialize GStreamer */
	gst_init ( NULL, NULL );
	pipeline = gst_element_factory_make ( "playbin", "playbin");
	audio_sink = gst_element_factory_make("autoaudiosink", "audio-sink");	
	g_object_set(G_OBJECT(pipeline), "audio-sink", audio_sink,	NULL);
	bus = gst_pipeline_get_bus (GST_PIPELINE ( pipeline ) );
	gst_bus_add_watch ( bus, xmusic_bus_call, NULL );
	gst_element_set_state(pipeline, GST_STATE_READY); 
	gst_object_unref(bus);
	
	xmusicd = xmusic;
	isplay = 0;
	xmusic_lists_init();
}
void play_next()
{
	xmusic_main.foucs = xmusic_main.foucs->next;
	if ( pipeline != NULL ){
		gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL); 
	}
	do_play(xmusic_main.foucs->uri);
}

void play_pre()
{
	xmusic_main.foucs = xmusic_main.foucs->pre;
	if ( pipeline != NULL ){
		gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL); 
	}
	do_play(xmusic_main.foucs->uri);
}

void xmusic_play_pause()
{
	if(isplay == 0){
		xmusic_play();
	}else{
		xmusic_pause();
	}	
}
void stop_pressed()
{ 
	if ( pipeline != NULL )	{
		gst_element_set_state ( GST_ELEMENT ( pipeline ), GST_STATE_NULL );
		gst_object_unref ( GST_OBJECT ( pipeline ) );
		pipeline = NULL;
		isplay = 0;
		time_task();
	}                      
}

void xmusic_quit()
{
	if ( pipeline != NULL ){
		gst_element_set_state ( GST_ELEMENT ( pipeline ), GST_STATE_NULL );
		gst_object_unref ( GST_OBJECT ( pipeline ) );
		pipeline = NULL;
		isplay = 0;
		time_task();
	}
	free_song_list();         
}

void add_new_songs(gchar *song_path){

	struct xmusic_songs *tmp;
	gchar *fname[1][1] = {NULL};
	
	if (xmusic_main.num == 0) {
		xmusic_main.songs = tmp = malloc(sizeof(struct xmusic_songs));
		snprintf(tmp->uri, NAME_LENGTH, "file://%s", song_path);
		strncpy(tmp->name, getlast(tmp->uri), NAME_LENGTH);
				
		tmp->next = tmp;
		tmp->pre = tmp;	
		xmusic_main.num += 1;
		
		fname[0][0] = tmp->name;		
		gtk_clist_append((GtkCList*)xmusicd->xlist, fname[0]);
		xmusic_main.foucs = xmusic_main.songs;
	}else{
		tmp = malloc(sizeof(struct xmusic_songs));
		snprintf(tmp->uri, NAME_LENGTH, "file://%s", song_path);
		strncpy(tmp->name, getlast(tmp->uri), NAME_LENGTH);				
		xmusic_main.last->next = tmp;
		tmp->pre = xmusic_main.songs;
		xmusic_main.num += 1;
		
		fname[0][0] = tmp->name;
		gtk_clist_append((GtkCList*)xmusicd->xlist, fname[0]);
	}		
	tmp->next = xmusic_main.songs;
	xmusic_main.last = tmp;
}
