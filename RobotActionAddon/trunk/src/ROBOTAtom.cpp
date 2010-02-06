/* dlvhex-robot atom -- ROBOT action addon for dlvhex.
 * 2009 Selen Başol, Ozan Erdem
 *
 * This file is part of dlvhex-robot action addon.
 *
 * dlvhex-robotaddon is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * dlvhex-robotplugin is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with dlvhex; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

/**
 * @file   ROBOTAtom.cpp
 * @author Selen Başol
 * @author Ozan Erdem
 *
 * @brief Handling of ROBOT atoms
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "ROBOTActionAddon.h"
#include "ROBOTAtom.h"

#include <iostream>
//#include <unistd.h>

namespace dlvhex
{


/*
    ROBOTAtom::ROBOTAtom(ROBOTActionAddon& robot)
      : robot_plugin(robot)
    {
      raptor_init();

      //Use a constant for the URI.
      addInputConstant();

      //arity set to 3, for the robot triples
      setOutputArity(3);
    }
*/

    ROBOTAtom::~ROBOTAtom()
    {
      
    }

	ROBOTAtom::ROBOTAtom(ROBOTActionAddon& robot) : robot_plugin(robot)
	{
		//addInputConstant();		
		currentAlarm=0;		
		world.push_back("                                                                      "); 
		world.push_back("                                ALARM: OFF                            ");
		world.push_back("                            +                +                        ");
		world.push_back("                            +                +                        ");
		world.push_back("                            +                +                        ");
		world.push_back("                            +                +                        ");
		world.push_back("                            +                +                        ");
		world.push_back("                            +                +                        ");
		world.push_back("    +++++++++++++++++++++++++                +++++++++++++++++++++++++");
		world.push_back("    +                                                                +");
		world.push_back("    +                                                                +");
		world.push_back("    +                                                                +");
		world.push_back("    +                                                                +");
		world.push_back("    +                                                                +");
		world.push_back("    +              ++++++++++++++++++++++++++++++++++++++            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    +              +                                    +            +");
		world.push_back("    ++++++++++++++++                                    ++++++++++++++");		
		currentX=11;
		currentY=37;
		putRobotInWorld(currentX,currentY);
		
	}

	void ROBOTAtom::putRobotInWorld(int x, int y)
	{
			tempWorld=world;
			tempWorld[x][y]='O';
	}
	
	void ROBOTAtom::moveDown(int x)
	{
		for(int i=0;i<x;i++)
		{
			putRobotInWorld(++currentX,currentY);
			refresh();
		}
	}

	void ROBOTAtom::moveUp(int x)
	{
		for(int i=0;i<x;i++)
		{
			putRobotInWorld(--currentX,currentY);
			refresh();
		}
	}

	void ROBOTAtom::moveLeft(int x)
	{
		for(int i=0;i<x;i++)
		{
			putRobotInWorld(currentX,--currentY);
			refresh();
		}
	}

	void ROBOTAtom::moveRight(int x)
	{
		for(int i=0;i<x;i++)
		{
			putRobotInWorld(currentX,++currentY);
			refresh();			
		}
	}
	
	void ROBOTAtom::refresh()
	{
			system("clear");			
			tempWorld=world;
			tempWorld[currentX][currentY]='O';	

			for(int j=0;j<35;j++)
			{
				std::cout << tempWorld[j] << std::endl;
			}
			
			usleep(1000*500);				
			
	}

	void ROBOTAtom::turnAlarmOn()
	{
		moveUp(9);
		if(!currentAlarm)		
		{
			moveRight(1);
			moveRight(1);
			world[1]="                                ALARM: ONF                            ";
			moveRight(1);
			world[1]="                                ALARM: ON                             ";
			moveRight(1);
			refresh();
			moveLeft(4);
		}
		moveDown(9);
	}

	void ROBOTAtom::turnAlarmOff()
	{
		moveUp(9);
		if(currentAlarm)
		{
			moveRight(1);
			moveRight(1);
			world[1]="                                ALARM: OF                            ";
			moveRight(1);
			world[1]="                                ALARM: OFF                            ";
			moveRight(1);
			refresh();
			moveLeft(4);
		}
		moveDown(9);
	}

	void ROBOTAtom::leftCorridor()
	{
		moveLeft(25);
		moveDown(22);
		sleep(1);
		moveUp(22);
		moveRight(25);		
	}

	void ROBOTAtom::rightCorridor()
	{
		moveRight(25);
		moveDown(22);
		sleep(1);
		moveUp(22);
		moveLeft(25);
	}

    // Standard function takes the query as an input and evaluates the associated function 
    void
//    ROBOTAtom::execute(const AddonAtom::Query& query) throw(PluginError)
	ROBOTAtom::execute(const Tuple & parms) throw(PluginError)
    {
		

	  system("clear");

	//  Tuple parms = query.getInputTuple();
	//std::cout<<"parms size: "<<parms.size()<<std::endl;
	  if(parms[0].getString()=="move")
	  {
			  if(parms[1].getString()=="left")
			  {
					leftCorridor();
			  }
			  else if(parms[1].getString()=="right")
			  {
					rightCorridor();
			  }
			  else if(parms[1].getString()=="all")
			  {
					leftCorridor();
					rightCorridor();
			  }
			  else
			  {
					std::cout << "unknown move!\n";
			  }
	  }
	  else if(parms[0].getString()=="turnAlarm")
	  {
			if(parms[1].getString()=="on")
		    {
				turnAlarmOn();
				currentAlarm=1;
			}
			else if(parms[1].getString()=="off")
			{
				turnAlarmOff();
				currentAlarm=0;
			}
			else
			{
				std::cout << "invalid option!\n";
			}
	  }

     refresh();
 

	}


} // dlvhex
