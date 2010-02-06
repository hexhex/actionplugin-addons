/* -*- C++ -*- */
/**
 * @file ROBOTActionAddon.hpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Sat Aug 1, 14:59:09 CET 2009
 *
 * @brief Header file for ROBOTActionAddon
 *
 */
#ifndef _ROBOT_PLUGIN_H
#define _ROBOT_PLUGIN_H

#include <dlvhex/ActionAddonAtom.h>
#include <dlvhex/Error.h>


namespace dlvhex {


class ROBOTActionAddon : public ActionAddonInterface
{

public:
  ROBOTActionAddon();

private:

  void
  getAtoms(ActionAddonAtomFunctionMap& a);

};  // class ROBOTActionAddon




} // namespace dlvhex


#endif /* _ROBOT_PLUGIN_H */
