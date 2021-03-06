/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */
/*
 * Xmusic (Zhwen.org)
 *
 * Copyright (c) 2008-~  Zhwen.org
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: main.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "play.h"

struct xmusic xmusic;

int main (int argc, char *argv[])
{
	GtkWidget *xmusic_window;

#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	gtk_set_locale ();
	gtk_init (&argc, &argv);

	add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
	add_pixmap_directory("../pixmaps");
	add_pixmap_directory("./pixmaps");

	xmusic_window = create_xmusic(&xmusic);
	gtk_widget_show (xmusic_window);
	xmusic_init(&xmusic);
	
	gtk_main ();
	return 0;
}

