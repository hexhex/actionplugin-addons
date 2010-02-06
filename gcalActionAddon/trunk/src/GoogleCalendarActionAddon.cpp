/* -*- C++ -*- */
/**
 * @file GoogleCalendarActionAddon.cpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Mon Feb 1, 01:55:21 CET 2010
 *
 * @brief Implementation file for GoogleCalendarActionAddon
 *
 */

/** @mainpage dlvhex-Google Calendar Addon Source Documentation
 *
 * \section Overview
 * This plugin implements functions which adds a given fact/rule to a knowledge base
 * The syntax is presented below:
 * \code
 * #createEvent[...]{OPT,PREC}[W:L].
 * \endcode
 *
 * Where ...
 * is the ...,
 * OPT is the action option, PREC is the action precedence,
 * W is the action weight, and L is the action level.
 *
 * A simple example:
 *
 * \code
 * #createEvent[...]{b,1}[2:1].
 * \endcode
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "GoogleCalendarActionAddon.h"
#include "CreateEventAtom.h"

#include "dlvhex/globals.h"

namespace dlvhex {
  namespace googlecalendar {






  GoogleCalendarActionAddon::GoogleCalendarActionAddon()
  { }


  void
  GoogleCalendarActionAddon::getAtoms(ActionAddonAtomFunctionMap& a)
  {

    boost::shared_ptr<ActionAddonAtom> kb_createEvent(new CreateEventAtom(*this));
    a["createEvent"] = kb_createEvent;
     
  }

  GoogleCalendarActionAddon theGoogleCalendarActionAddon;


  } // namespace gcal
} // namespace dlvhex


extern "C"
dlvhex::googlecalendar::GoogleCalendarActionAddon*
PLUGINIMPORTFUNCTION()
{


  dlvhex::googlecalendar::theGoogleCalendarActionAddon.setActionAddonName(PACKAGE_TARNAME);
  dlvhex::googlecalendar::theGoogleCalendarActionAddon.setVersion(GOOGLECALENDARADDON_MAJOR,
				       GOOGLECALENDARADDON_MINOR,
				       GOOGLECALENDARADDON_MICRO);

  return &dlvhex::googlecalendar::theGoogleCalendarActionAddon;
}
