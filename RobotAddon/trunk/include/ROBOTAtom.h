/* -*- C++ -*- */
/**
 * @file ROBOTAtom.hpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @date Sat Aug 1, 14:59:09 CET 2009
 *
 * @brief Header file for ROBOTAtom
 *
 */
#ifndef _ROBOT_ATOM_H
#define _ROBOT_ATOM_H

#include <dlvhex/AddonAtom.h>
#include <dlvhex/Error.h>

#include <vector>

namespace dlvhex {


// forward declarations
class ROBOTPlugin;

/**
 * Class for the robot atom.
 *
**/


class ROBOTAtom : public AddonAtom
{

protected:
  ROBOTPlugin& robot_plugin;

public:
  /**
   * Constructor of ROBOTatom. Defines the inputConstant of the plugin atom.
   */
  ROBOTAtom(ROBOTPlugin& robot);

  virtual
  ~ROBOTAtom();

  /**
   * Retrieves the resulting robot tuples in the answer object for the input query.
   */
  virtual void
//  execute(const AddonAtom::Query& query) throw(PluginError);
  execute(const Tuple & parms) throw(PluginError);


private:

  void
  putRobotInWorld(int x, int y);
	
  void
  moveDown(int x);

  void
  moveUp(int x);

  void
  moveRight(int x);

  void
  moveLeft(int x);
 
  void
  refresh();

  void
  turnAlarmOn();

  void
  turnAlarmOff();

  void 
  leftCorridor();
 
  void
  rightCorridor();

  std::vector<std::string> world;
  std::vector<std::string> tempWorld; 
  int currentX;
  int currentY;
  bool currentAlarm;


};


} // namespace dlvhex

#endif /* ROBOT_ATOM_H */
