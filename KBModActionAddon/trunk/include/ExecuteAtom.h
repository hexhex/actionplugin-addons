/* -*- C++ -*- */
/**
 * @file ExecuteAtom.hpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Wed Aug 19, 04:28:43 CET 2009
 *
 * @brief Header file for ExecuteAtom
 *
 */
#ifndef _EXECUTE_ATOM_H
#define _EXECUTE_ATOM_H

#include <dlvhex/ActionAddonAtom.h>
#include <dlvhex/Error.h>

namespace dlvhex {
  namespace kbmod {

// forward declarations
class KBModActionAddon;

/**
 * Class for the kbmod atom.
 *
**/


class ExecuteAtom : public ActionAddonAtom
{

protected:
  KBModActionAddon& kbmod_addon;

public:
  /**
   * Constructor of KBModatom. Defines the inputConstant of the addon atom.
   */
  ExecuteAtom(KBModActionAddon& kbmod);

  virtual
  ~ExecuteAtom();

  /**
   * Retrieves the resulting kbmod tuples in the answer object for the input query.
   */
  virtual void
  execute(const Tuple & parms) throw(PluginError);


private:




};

  } // namespace kbmod
} // namespace dlvhex

#endif /* EXECUTE_ATOM_H */
