## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/muhafiz/ui
ui_DATA = muhafiz.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(MUHAFIZ_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = muhafiz

muhafiz_SOURCES = \
	callbacks.c \
	callbacks.h \
	main.c

muhafiz_LDFLAGS = \
	-Wl,--export-dynamic

muhafiz_LDADD = $(MUHAFIZ_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/muhafiz
