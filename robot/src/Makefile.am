#
# replace 'plugin' on the right side by your plugin's name
#
plugin_LTLIBRARIES = libdlvhexplugin-robot_action.la

#
# replace 'plugin' on the left side as above and
# add all sources of your plugin
#
libdlvhexplugin_robot_action_la_SOURCES = RobotActionPlugin.cpp

#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS)

libdlvhexplugin_robot_action_la_LDFLAGS = -avoid-version -module -L$(top_builddir)/src/ -rpath /
libdlvhexplugin_robot_action_la_LIBADD = -ldlvhex-action

libdlvhexplugin-robot_action-static.la: $(libdlvhexplugin_robot_action_la_OBJECTS)
	$(CXXLINK) -avoid-version -module -rpath $(plugindir) $(libdlvhexplugin_robot_action_la_OBJECTS) $(libdlvhexplugin_robot_action_la_LIBADD)

install-static: libdlvhexplugin-robot_action-static.la
	$(LIBTOOL) --mode=install $(INSTALL) -s libdlvhexplugin-robot_action-static.la $(DESTDIR)$(plugindir)/libdlvhexplugin-robot_action-static.la

uninstall-static:
	$(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(plugindir)/libdlvhexplugin-robot_action-static.la
