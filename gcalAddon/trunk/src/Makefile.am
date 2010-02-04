AUTOMAKE_OPTIONS = gnu

plugin_LTLIBRARIES = libactiongooglecalendar.la calendarApp.class

AM_CPPFLAGS= -I$(top_srcdir)/include \
             $(DEBUG_FLAGS) \
             $(DLVHEX_CFLAGS)

libactiongooglecalendar_la_SOURCES = GoogleCalendarAddon.cpp CreateEventAtom.cpp

libactiongooglecalendar_la_LDFLAGS =-version-info="" -avoid-version
