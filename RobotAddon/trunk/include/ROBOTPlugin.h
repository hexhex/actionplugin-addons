/* -*- C++ -*- */
/**
 * @file ROBOTPlugin.hpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Sat Aug 1, 14:59:09 CET 2009
 *
 * @brief Header file for ROBOTPlugin
 *
 */
#ifndef _ROBOT_PLUGIN_H
#define _ROBOT_PLUGIN_H

#include <dlvhex/AddonAtom.h>
#include <dlvhex/Error.h>


namespace dlvhex {


class ROBOTPlugin : public AddonInterface
{

public:
  ROBOTPlugin();

private:

  void
  getAtoms(AddonAtomFunctionMap& a);

};  // class ROBOTPlugin




} // namespace dlvhex


#endif /* _ROBOT_PLUGIN_H */
