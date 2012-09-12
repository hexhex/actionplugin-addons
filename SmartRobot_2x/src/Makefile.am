#
# replace 'plugin' on the right side by your plugin's name
#
plugin_LTLIBRARIES = libdlvhexplugin-smartRobot_action.la


#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexplugin_smartRobot_action_la_SOURCES = SmartRobotActionPlugin.cpp
libdlvhexplugin_smartRobot_action_la_LDFLAGS = -avoid-version -module # -L$(top_builddir)/src/ -rpath /
libdlvhexplugin_smartRobot_action_la_LIBADD = -ldlvhex-action $(DLVHEX_LIBS)

libdlvhexplugin-smartRobot_action-static.la: $(libdlvhexplugin_smartRobot_action_la_OBJECTS)
	$(CXXLINK) -avoid-version -module -rpath $(plugindir) $(libdlvhexplugin_smartRobot_action_la_OBJECTS) $(libdlvhexplugin_smartRobot_action_la_LIBADD)

install-static: libdlvhexplugin-smartRobot_action-static.la
	$(LIBTOOL) --mode=install $(INSTALL) -s libdlvhexplugin-smartRobot_action-static.la $(DESTDIR)$(plugindir)/libdlvhexplugin-smartRobot_action-static.la

uninstall-static:
	$(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(plugindir)/libdlvhexplugin-smartRobot_action-static.la
