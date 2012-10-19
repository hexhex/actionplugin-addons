#
# replace 'plugin' on the right side by your plugin's name
#
plugin_LTLIBRARIES = libdlvhexplugin-sudoku_action.la


#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexplugin_sudoku_action_la_SOURCES = SudokuPlugin.cpp
libdlvhexplugin_sudoku_action_la_LDFLAGS = -avoid-version -module # -L$(top_builddir)/src/ -rpath /
libdlvhexplugin_sudoku_action_la_LIBADD = -ldlvhex-action $(DLVHEX_LIBS)

libdlvhexplugin-sudoku_action-static.la: $(libdlvhexplugin_sudoku_action_la_OBJECTS)
	$(CXXLINK) -avoid-version -module -rpath $(plugindir) $(libdlvhexplugin_sudoku_action_la_OBJECTS) $(libdlvhexplugin_sudoku_action_la_LIBADD)

install-static: libdlvhexplugin-sudoku_action-static.la
	$(LIBTOOL) --mode=install $(INSTALL) -s libdlvhexplugin-sudoku_action-static.la $(DESTDIR)$(plugindir)/libdlvhexplugin-sudoku_action-static.la

uninstall-static:
	$(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(plugindir)/libdlvhexplugin-sudoku_action-static.la
