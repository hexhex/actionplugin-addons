/* -*- C++ -*- */
/**
 * @file AssertAtom.hpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Wed Aug 19, 04:28:43 CET 2009
 *
 * @brief Header file for AssertAtom
 *
 */
#ifndef _ASSERT_ATOM_H
#define _ASSERT_ATOM_H

#include <dlvhex/ActionAddonAtom.h>
#include <dlvhex/Error.h>

#include <vector>

namespace dlvhex {
  namespace kbmod {

// forward declarations
class KBModActionAddon;

/**
 * Class for the kbmod atom.
 *
**/


class AssertAtom : public ActionAddonAtom
{

protected:
  KBModActionAddon& kbmod_addon;

public:
  /**
   * Constructor of KBModatom. Defines the inputConstant of the plugin atom.
   */
  AssertAtom(KBModActionAddon& kbmod);

  virtual
  ~AssertAtom();

  /**
   * Retrieves the resulting kbmod tuples in the answer object for the input query.
   */
  virtual void
  execute(const Tuple & parms) throw(PluginError);


private:




};

  } // namespace kbmod
} // namespace dlvhex

#endif /* ASSERT_ATOM_H */
