#
# replace 'plugin' on the right side by your plugin's name
#
plugin_LTLIBRARIES = libdlvhexplugin-reversi.la


#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexplugin_reversi_la_SOURCES = Reversi.cpp PawnPlaced.cpp
libdlvhexplugin_reversi_la_LDFLAGS = -avoid-version -module # -L$(top_builddir)/src/ -rpath /
libdlvhexplugin_reversi_la_LIBADD = -ldlvhex-action $(DLVHEX_LIBS)

libdlvhexplugin-reversi-static.la: $(libdlvhexplugin_reversi_la_OBJECTS)
	$(CXXLINK) -avoid-version -module -rpath $(plugindir) $(libdlvhexplugin_reversi_la_OBJECTS) $(libdlvhexplugin_reversi_la_LIBADD)

install-static: libdlvhexplugin-reversi-static.la
	$(LIBTOOL) --mode=install $(INSTALL) -s libdlvhexplugin-reversi-static.la $(DESTDIR)$(plugindir)/libdlvhexplugin-reversi-static.la

uninstall-static:
	$(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(plugindir)/libdlvhexplugin-reversi-static.la
