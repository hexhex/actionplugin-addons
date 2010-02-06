/* -*- C++ -*- */
/**
 * @file createEventAtom.h
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Mon Feb 1, 01:55:21 CET 2010
 *
 * @brief Header file for createEvent
 *
 */
#ifndef _CREATEEVENT_ATOM_H
#define _CREATEEVENT_ATOM_H

#include <dlvhex/ActionAddonAtom.h>
#include <dlvhex/Error.h>



namespace dlvhex {
  namespace googlecalendar {

// forward declarations
class GoogleCalendarActionAddon;

/**
 * Class for the createEvent atom.
 *
**/


class CreateEventAtom : public ActionAddonAtom
{

protected:
  GoogleCalendarActionAddon& gcal_addon;

public:
  /**
   * Constructor of KBModatom. Defines the inputConstant of the plugin atom.
   */
  CreateEventAtom(GoogleCalendarActionAddon & gcal);

  virtual
  ~CreateEventAtom();

  /**
   * Executes the createEvent action.
   */
  virtual void
  execute(const Tuple & parms) throw(PluginError);


private:




};

  } // namespace googlecalendar
} // namespace dlvhex

#endif /* CREATEEVENT_ATOM_H */
