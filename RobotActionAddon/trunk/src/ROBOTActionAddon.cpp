/* -*- C++ -*- */
/**
 * @file ROBOTActionAddon.cpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Sat Aug 1, 14:59:09 CET 2009
 *
 * @brief Corefile of the ROBOT action addon
 *
 */

/** @mainpage dlvhex-robotaddon Source Documentation
 *
 * \section Overview
 * This addon implements functions which make a robot move, and toggle an alarm.
 * The syntax is presented below:
 * \code
 * #robot[ACT,PARAM]{OPT,PREC}[W:L].
 * \endcode
 *
 * Where ACT is the name of the action, PARAM is the parameter that is associated
 * with the given action, OPT is the action option, PREC is the action precedence,
 * W is the action weight, and L is the action level.
 *
 * A simple example:
 *
 * \code
 * #robot[move,left]{b,1}[2:1].
 * \endcode
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "ROBOTActionAddon.h"
#include "ROBOTAtom.h"

#include <iostream>

#include "dlvhex/globals.h"

namespace dlvhex {
 






  ROBOTActionAddon::ROBOTActionAddon()
  { }


  void
  ROBOTActionAddon::getAtoms(ActionAddonAtomFunctionMap& a)
  {
    boost::shared_ptr<ActionAddonAtom> robot(new ROBOTAtom(*this));
    a["robot"] = robot;
	//std::cout << "registered the robot atom in the addon.\n";
  }

ROBOTActionAddon theROBOTActionAddon;



} // namespace dlvhex


extern "C"
dlvhex::ROBOTActionAddon*
PLUGINIMPORTFUNCTION()
{
  dlvhex::theROBOTActionAddon.setActionAddonName(PACKAGE_TARNAME);
  dlvhex::theROBOTActionAddon.setVersion(ROBOTPLUGIN_MAJOR,
				       ROBOTPLUGIN_MINOR,
				       ROBOTPLUGIN_MICRO);
  return &dlvhex::theROBOTActionAddon;
}
