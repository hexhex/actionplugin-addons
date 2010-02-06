/* -*- C++ -*- */
/**
 * @file KBModPlugin.hpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Wed Aug 19, 04:28:43 CET 2009
 *
 * @brief Header file for KBModPlugin
 *
 */
#ifndef _KBMOD_PLUGIN_H
#define _KBMOD_PLUGIN_H

#include <dlvhex/ActionAddonAtom.h>
#include <dlvhex/Error.h>


namespace dlvhex {
  namespace kbmod {

class KBModActionAddon : public ActionAddonInterface
{

public:
  KBModActionAddon();

private:

  void
  getAtoms(ActionAddonAtomFunctionMap& a);

};  // class KBModPlugin



  } // namespace kbmod
} // namespace dlvhex


#endif /* _KBMOD_PLUGIN_H */
