AUTOMAKE_OPTIONS = gnu

plugin_LTLIBRARIES = libactionrobot.la

AM_CPPFLAGS= \
	-I$(top_srcdir)/include \
	$(DEBUG_FLAGS) \
	$(DLVHEX_CFLAGS)

libactionrobot_la_SOURCES = ROBOTPlugin.cpp ROBOTAtom.cpp

libactionrobot_la_LDFLAGS =-version-info="" -avoid-version
