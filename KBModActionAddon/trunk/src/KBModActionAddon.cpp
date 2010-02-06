/* -*- C++ -*- */
/**
 * @file KBModActionAddon.hpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Wed Aug 19, 04:28:43 CET 2009
 *
 * @brief Header file for KBModActionAddon
 *
 */

/** @mainpage dlvhex-kbmodplugin Source Documentation
 *
 * \section Overview
 * This plugin implements functions which adds a given fact/rule to a knowledge base
 * The syntax is presented below:
 * \code
 * #assert[FILENAME,FACT_OR_RULE]{OPT,PREC}[W:L].
 * \endcode
 *
 * Where FILENAME is the name of the file which contains the knowledge base, FACT_OR_RULE
 * is the fact or rule to be added as a string,
 * OPT is the action option, PREC is the action precedence,
 * W is the action weight, and L is the action level.
 *
 * A simple example:
 *
 * \code
 * #assert["/home/foo/knowledge.txt","bar."]{b,1}[2:1].
 * \endcode
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "KBModActionAddon.h"
#include "AssertAtom.h"
#include "RetractAtom.h"
#include "ExecuteAtom.h"
#include <iostream>

#include "dlvhex/globals.h"

namespace dlvhex {
  namespace kbmod {






  KBModActionAddon::KBModActionAddon()
  { }


  void
  KBModActionAddon::getAtoms(ActionAddonAtomFunctionMap& a)
  {

    boost::shared_ptr<ActionAddonAtom> kb_assert(new AssertAtom(*this));
    boost::shared_ptr<ActionAddonAtom> kb_retract(new RetractAtom(*this));
    boost::shared_ptr<ActionAddonAtom> kb_execute(new ExecuteAtom(*this));
    a["assert"] = kb_assert;
    a["retract"] = kb_retract;
    a["execute"] = kb_execute;

    
  }

  KBModActionAddon theKBModActionAddon;


  } // namespace kbmod
} // namespace dlvhex


extern "C"
dlvhex::kbmod::KBModActionAddon*
PLUGINIMPORTFUNCTION()
{


  dlvhex::kbmod::theKBModActionAddon.setActionAddonName(PACKAGE_TARNAME);
  dlvhex::kbmod::theKBModActionAddon.setVersion(KBMODPLUGIN_MAJOR,
				       KBMODPLUGIN_MINOR,
				       KBMODPLUGIN_MICRO);

  return &dlvhex::kbmod::theKBModActionAddon;
}
