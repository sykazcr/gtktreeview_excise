/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+
#+     Glade / Gtk Programming
#+
#+     Copyright (C) 2019 by Kevin C. O'Kane
#+
#+     Kevin C. O'Kane
#+     kc.okane@gmail.com
#+     https://www.cs.uni.edu/~okane
#+     http://threadsafebooks.com/
#+
#+ This program is free software; you can redistribute it and/or modify
#+ it under the terms of the GNU General Public License as published by
#+ the Free Software Foundation; either version 2 of the License, or
#+ (at your option) any later version.
#+
#+ This program is distributed in the hope that it will be useful,
#+ but WITHOUT ANY WARRANTY; without even the implied warranty of
#+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#+ GNU General Public License for more details.
#+
#+ You should have received a copy of the GNU General Public License
#+ along with this program; if not, write to the Free Software
#+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#+
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// April 12, 2019

//-----------------------------------------------------------------------------
// Portions of this code, as noted below, are derived from pavumeter which
// is also licensed under GPL 2.
//-----------------------------------------------------------------------------

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <gtk/gtk.h>
#include <sys/ipc.h>
#include <math.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <gtk/gtkx.h>
#include <time.h>
#include <ctype.h>
#include <sys/mman.h>
#include <sys/shm.h>

GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*draw2;
GtkBuilder	*builder; 

gboolean	on_draw2_draw (GtkDrawingArea *widget, cairo_t *cr);
char		bg_color[256] = "black";

#include "clock.h"

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk

//-----------------------
//	GTK interface
//-----------------------

	builder = gtk_builder_new_from_resource ("/part1/part1.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);

        gtk_builder_connect_signals(builder, NULL);

	fixed1		= GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	draw2		= GTK_WIDGET(gtk_builder_get_object(builder, "draw2"));

	g_object_unref(builder);

//	gtk_window_set_keep_above (GTK_WINDOW(window), TRUE); // un-comment to keep on top

	gtk_widget_show(window);

        GdkColor color; // default background color

	if (!gdk_color_parse (bg_color, &color)) { // does color parse?
        	color.blue = 0x0000;
        	color.red = 0x0000;
        	color.green = 0x0000;
		}

        gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color); // set background color

	gtk_window_set_title(GTK_WINDOW(window), "Spark Gap Radio Clock 1.00");

	g_timeout_add_seconds(1, (GSourceFunc) clock_timer_handler, NULL);

	gtk_main();

	return EXIT_SUCCESS;
	}
