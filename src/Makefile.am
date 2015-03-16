## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = xdmusic

xdmusic_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	popmenu.c popmenu.h \
	callbacks.c callbacks.h \
	play.c play.h\
	xfuns.c xfuns.h

xdmusic_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

