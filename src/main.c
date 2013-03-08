 /* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Aydın Demirel 2010 <aydin@demirel.web.tr>
 * 
 * muhafiz is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * muhafiz is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <config.h>

#include <gtk-2.0/gtk/gtk.h>


/*
 * Standard gettext macros.
 */

#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif


void on_filtre_button_1_clicked (GtkObject *object, gpointer user_data);
void on_imagemenuitem10_activate (GtkObject *object, gpointer user_data);
void on_filtre_button_2_clicked (GtkObject *object, gpointer user_data);
void on_duzenleme_button_1_clicked (GtkObject *object, gpointer user_data);
void on_duzenleme_button_2_clicked (GtkObject *object, gpointer user_data);
void on_tarayici_button_1_clicked (GtkObject *object, gpointer user_data);
void on_imagemenuitem20_activate (GtkObject *object, gpointer user_data);
void on_yardim_button_clicked (GtkObject *object, gpointer user_data);

#include "callbacks.h"

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/muhafiz/ui/muhafiz.ui" */
#define UI_FILE "/usr/share/muhafiz-0.1.1/src/muhafiz.xml"

GtkWidget *window_hakkinda,*window_duzenleme,*combo_1,*combo_2,*filtre_button_1,*duz_textview,*tar_checkbutton,*statusbar;
GtkListStore *liststore1,*liststore2;
GtkCellRenderer *renderer_1,*renderer_2;
GtkBuilder *builder;
gint number_1,number_2;
GError                  *err=NULL;
gchar                   *text;
gboolean                result;
GtkTextBuffer           *buffer;

GtkWidget*
create_window (void)
{
	GtkWidget *window_ana;
	
	GError* error = NULL;

	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_warning ("İnşa dosyası yüklenemedi: %s", error->message);
		g_error_free (error);
	}

	/* This is important */
	gtk_builder_connect_signals (builder, NULL);
	window_ana = GTK_WIDGET (gtk_builder_get_object (builder, "ana_Pencere"));
	window_hakkinda = GTK_WIDGET (gtk_builder_get_object (builder, "hakkinda_Penceresi"));
	window_duzenleme = GTK_WIDGET (gtk_builder_get_object (builder ,"duzenleme_Penceresi"));
	combo_1 = GTK_WIDGET (gtk_builder_get_object (builder, "filtre_combobox_1"));
	combo_2 = GTK_WIDGET (gtk_builder_get_object (builder, "filtre_combobox_2"));
	liststore1 = GTK_LIST_STORE (gtk_builder_get_object (builder , "liststore1"));
	liststore2 = GTK_LIST_STORE (gtk_builder_get_object (builder , "liststore2"));
	renderer_1 = GTK_CELL_RENDERER (gtk_builder_get_object(builder,"cellrenderertext3"));
	renderer_2 = GTK_CELL_RENDERER (gtk_builder_get_object(builder,"cellrenderertext4"));
	filtre_button_1 = GTK_WIDGET (gtk_builder_get_object (builder, "filtre_button_1"));
	duz_textview = GTK_WIDGET (gtk_builder_get_object (builder, "duz_textview"));
	tar_checkbutton = GTK_WIDGET (gtk_builder_get_object (builder, "tarayici_checkbutton"));
	statusbar = GTK_WIDGET(gtk_builder_get_object(builder,"statusbar"));


	g_object_unref (builder);
	

	return window_ana;
}


int
main (int argc, char *argv[])
{
 	GtkWidget *window;


#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	
	gtk_set_locale ();
	gtk_init (&argc, &argv);

	window = create_window ();
	gtk_widget_show (window);

	gtk_main ();
	return 0;
}

void 
on_imagemenuitem10_activate (GtkObject *object, gpointer user_data)
{
	
	/*show about dialog*/
    gint response = gtk_dialog_run(GTK_DIALOG(window_hakkinda));
     
    /*for close button*/
    if(response == GTK_RESPONSE_CANCEL){
    gtk_widget_hide(window_hakkinda);
    }
}

void
on_filtre_button_1_clicked (GtkObject *object, gpointer user_data)

{
	
 number_1 = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_1));
	
if(number_1 == 0)
	{
     /*get exceptioniplist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/exceptioniplist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);

	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	} 
	else if(number_1 == 1)
	{
     /*get exceptionmimetypelist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/exceptionmimetypelist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);

	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
	else if(number_1 == 2)
	{
     /*get exceptionfilesitelist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/exceptionfilesitelist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);
			
	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
	else if(number_1 == 3)
	{
     /*get exceptionregexpurllist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/exceptionregexpurllist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);

	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
	else if(number_1 == 4)
	{
     /*get exceptionsitelist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/exceptionsitelist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);

	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
	else if(number_1 == 5)
	{
     /*get exceptionurllist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/exceptionurllist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);
			
	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
		
}

void
on_filtre_button_2_clicked (GtkObject *object, gpointer user_data)

{
	
 number_2 = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_2));
	
if(number_2 == 0)
	{
     /*get bannedextensionlist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/bannedextensionlist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);

	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	} 
	else if(number_2 == 1)
	{
     /*get bannediplist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/bannediplist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);

	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
	else if(number_2 == 2)
	{
     /*get bannedmimetypelist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/bannedmimetypelist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);
			
	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
	else if(number_2 == 3)
	{
     /*get bannedregexpurllist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/bannedregexpurllist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);

	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
	else if(number_2 == 4)
	{
     /*get bannedsitelist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/bannedsitelist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);

	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
	else if(number_2 == 5)
	{
     /*get bannedurllist*/

     result = g_file_get_contents ("/etc/dansguardian/lists/bannedurllist", &text, NULL, &err);

     gtk_widget_set_sensitive (duz_textview, FALSE);
     buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (duz_textview));
     gtk_text_buffer_set_text (buffer, text, -1);
     gtk_text_buffer_set_modified (buffer, FALSE);
     gtk_widget_set_sensitive (duz_textview, TRUE);
     g_free (text);
			
	/*show duzenleme dialog*/
   
	gtk_dialog_run(GTK_DIALOG(window_duzenleme));
	}
		
}
                            
void
on_duzenleme_button_1_clicked (GtkObject *object, gpointer user_data)
{
  gchar *komut;
 
  number_1 = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_1));
  number_2 = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_2));
  
    
		/*exception section*/
	
	if(number_1 == 0)
	{
	     /*create exceptioniplist file*/
	  
    komut = "gksu chmod o+rw /etc/dansguardian/lists/exceptioniplist";
    system(komut);
    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/exceptioniplist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);
 
	} 
	
	if(number_1 == 1)
	{
	     /*create exceptionmimetypelist file*/
komut = "gksu chmod o+rw /etc/dansguardian/lists/exceptionmimetypelist";
system(komut);
  
    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/exceptionmimetypelist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);

	} 
	
	if(number_1 == 2)
	{
	     /*create exceptionfilesitelist file*/
	
komut = "gksu chmod o+rw /etc/dansguardian/lists/exceptionfilesitelist";
system(komut);
  
    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/exceptionfilesitelist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);
  
	} 

	if(number_1 == 3)
	{
	     /*create exceptionregexpurllist file*/
komut = "gksu chmod o+rw /etc/dansguardian/lists/exceptionregexpurllist";
system(komut);

    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/exceptionregexpurllist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);

	}

	if(number_1 == 4)
	{
	     /*create exceptionsitelist file*/
		
komut = "gksu chmod o+rw /etc/dansguardian/lists/exceptionsitelist";
system(komut);

    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/exceptionsitelist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);

	}

    	 if(number_1 == 5)
	{
	     /*create exceptionurllist file*/
komut = "gksu chmod o+rw /etc/dansguardian/lists/exceptionurllist";
system(komut);	

    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/exceptionurllist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);

	}
	
	/*banned section*/
	
	if(number_2 == 0)
	{
	     /*create bannedextensionlist file*/
		
komut = "gksu chmod o+rw /etc/dansguardian/lists/bannedextensionlist";
system(komut);

    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/bannedextensionlist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);

	} 

 	if(number_2 == 1)
	{
	     /*create bannediplist file*/
komut = "gksu chmod o+rw /etc/dansguardian/lists/bannediplist";
system(komut);

    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/bannediplist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);
   
	} 

	 if(number_2 == 2)
	{
	     /*create bannedmimetypelist file*/
komut = "gksu chmod o+rw /etc/dansguardian/lists/bannedmimetypelist";
system(komut);	

    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/bannedmimetypelist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);

	} 

	if(number_2 == 3)
	{
	     /*create bannedregexpurllist file*/
	     
 komut = "gksu chmod o+rw /etc/dansguardian/lists/bannedregexpurllist";
 system(komut);
  
    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/bannedregexpurllist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);

	}

	if(number_2 == 4)
	{
	     /*create bannedsitelist file*/
komut = "gksu chmod o+rw /etc/dansguardian/lists/bannedsitelist";
system(komut);

    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/bannedsitelist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);
	
	}

	if(number_2 == 5)
	{
	     /*create bannedurllist file*/
komut = "gksu chmod o+rw /etc/dansguardian/lists/bannedurllist";
system(komut);	

    FILE *output_1;

    gchar          filename_1[] = "/etc/dansguardian/lists/bannedurllist";
    gchar         *contents_1;
    
    GtkTextIter    start_1,
                     end_1;
    GtkTextBuffer *buffer_1;
    output_1 = g_fopen(filename_1,"w");


    buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW( duz_textview ));
    gtk_text_buffer_get_bounds( buffer_1, &start_1, &end_1 );
    contents_1 = gtk_text_buffer_get_text( buffer_1, &start_1, &end_1, TRUE );

    g_file_set_contents( filename_1, contents_1, -1 , NULL );
    g_free( contents_1 );

    fclose(output_1);
	
	}

 /*update status bar*/

   gtk_statusbar_push(GTK_STATUSBAR(statusbar),0,"Ayarlar Kaydedildi...");
}

void 
on_duzenleme_button_2_clicked (GtkObject *object, gpointer user_data)
{
gtk_widget_hide(window_duzenleme);
}

void
on_tarayici_button_1_clicked (GtkObject *object, gpointer user_data)
{
	gchar *komut;
 
  /*if check button is active*/
 if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tar_checkbutton ))){

  komut = "gksu sh /usr/share/muhafiz-0.1.1/config/firefox_proxy_add.sh";
  g_spawn_command_line_sync(komut,NULL,NULL,NULL,0);

  komut = "gksu sh /usr/share/muhafiz-0.1.1/config/dansguardian.sh";
  g_spawn_command_line_sync(komut,NULL,NULL,NULL,0);

 }else{ /*if checkbox button is deactive*/

     komut = "gksu sh /usr/share/muhafiz-0.1.1/config/firefox_proxy_del.sh";
     g_spawn_command_line_sync(komut,NULL,NULL,NULL,0);
  
 }

   
   /*copy dansguardian.pl file from /usr/share/dansguardian/dansguardian.pl to /var/www/localhost/cgi-bin*/
    if(!g_file_test("/var/www/localhost/cgi-bin/dansguardian.pl",G_FILE_TEST_EXISTS)){
    komut = "gksu cp /usr/share/dansguardian/dansguardian.pl /var/www/localhost/cgi-bin/";
    g_spawn_command_line_sync(komut,NULL,NULL,NULL,0);
    }

 /*update status bar*/

   gtk_statusbar_push(GTK_STATUSBAR(statusbar),0,"Tarayıcı Ayarları Kaydedildi. Lütfen Tarayıcıyı Yeniden Başlatın..");
}

void
on_imagemenuitem20_activate (GtkObject *object, gpointer user)
{
gint hakkinda = gtk_dialog_run(GTK_DIALOG(window_hakkinda));

if(hakkinda == GTK_RESPONSE_CANCEL){
gtk_widget_hide(window_hakkinda);
}
}

void
on_yardim_button_clicked (GtkObject *object, gpointer user_data)
{
gchar *komut;
komut = "okular /usr/share/muhafiz-0.1.1/help/yardim.pdf";
g_spawn_command_line_sync(komut,NULL,NULL,NULL,0);
}
