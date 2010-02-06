/* -*- C++ -*- */
/**
 * @file GoogleCalendarActionAddon.h
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Mon Feb 1, 01:55:21 CET 2010
 *
 * @brief Header file for GoogleCalendarActionAddon
 *
 */
#ifndef _GOOGLECALENDAR_ADDON_H
#define _GOOGLECALENDAR_ADDON_H

#include <dlvhex/ActionAddonAtom.h>
#include <dlvhex/Error.h>


namespace dlvhex {
  namespace googlecalendar {

class GoogleCalendarActionAddon : public ActionAddonInterface
{

public:
  GoogleCalendarActionAddon();

private:

  void
  getAtoms(ActionAddonAtomFunctionMap& a);

};  // class GoogleCalendarActionAddon



  } // namespace googlecalendar
} // namespace dlvhex


#endif /* _GOOGLECALENDAR_ADDON_H */
