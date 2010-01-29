/* -*- C++ -*- */
/**
 * @file ROBOTPlugin.cpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Sat Aug 1, 14:59:09 CET 2009
 *
 * @brief Corefile of the ROBOT plugin
 *
 */

/** @mainpage dlvhex-robotplugin Source Documentation
 *
 * \section Overview
 * This plugin implements functions which make a robot move, and toggle an alarm.
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

#include "ROBOTPlugin.h"
#include "ROBOTAtom.h"

#include <iostream>

#include "dlvhex/globals.h"

namespace dlvhex {
 






  ROBOTPlugin::ROBOTPlugin()
  { }


  void
  ROBOTPlugin::getAtoms(AddonAtomFunctionMap& a)
  {
    boost::shared_ptr<AddonAtom> robot(new ROBOTAtom(*this));
    a["robot"] = robot;
	//std::cout << "registered the robot atom in the addon.\n";
  }

ROBOTPlugin theROBOTPlugin;



} // namespace dlvhex


extern "C"
dlvhex::ROBOTPlugin*
PLUGINIMPORTFUNCTION()
{
  dlvhex::theROBOTPlugin.setAddonName(PACKAGE_TARNAME);
  dlvhex::theROBOTPlugin.setVersion(ROBOTPLUGIN_MAJOR,
				       ROBOTPLUGIN_MINOR,
				       ROBOTPLUGIN_MICRO);
  return &dlvhex::theROBOTPlugin;
}
