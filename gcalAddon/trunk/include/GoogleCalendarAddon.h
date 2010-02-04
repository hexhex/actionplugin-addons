/* -*- C++ -*- */
/**
 * @file GoogleCalendarAddon.h
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Mon Feb 1, 01:55:21 CET 2010
 *
 * @brief Header file for GoogleCalendarAddon
 *
 */
#ifndef _GOOGLECALENDAR_ADDON_H
#define _GOOGLECALENDAR_ADDON_H

#include <dlvhex/AddonAtom.h>
#include <dlvhex/Error.h>


namespace dlvhex {
  namespace googlecalendar {

class GoogleCalendarAddon : public AddonInterface
{

public:
  GoogleCalendarAddon();

private:

  void
  getAtoms(AddonAtomFunctionMap& a);

};  // class GoogleCalendarAddon



  } // namespace googlecalendar
} // namespace dlvhex


#endif /* _GOOGLECALENDAR_ADDON_H */
