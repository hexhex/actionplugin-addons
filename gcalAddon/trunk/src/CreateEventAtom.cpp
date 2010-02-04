/* dlvhex-GoogleCalendarAddon -- Google Calendar Addon for dlvhex.
 * 2010 Selen Başol, Ozan Erdem
 *
 * This file is part of dlvhex-GoogleCalendarAddon.
 *
 * dlvhex-GoogleCalendarAddon is free software; you can redistribute it
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
 * @file   createEventAtom.cpp
 * @author Selen Başol
 * @author Ozan Erdem
 *
 * @brief Handling of createEvent atoms
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "GoogleCalendarAddon.h"
#include "CreateEventAtom.h"
#include <string>
#include <iostream>


namespace dlvhex
{
  namespace googlecalendar
  {


    CreateEventAtom::~CreateEventAtom()
    {
      
    }

    CreateEventAtom::CreateEventAtom(GoogleCalendarAddon& gcal) : gcal_addon(gcal)
    {
			
    }



    // Standard function takes the query as an input and evaluates the associated function 
    void
    CreateEventAtom::execute(const Tuple & parms) throw(PluginError)
    {
//java calendarApp team1 "http://www.google.com/calendar/feeds/02ngn7n8s87fi6oojbn06sre4g%40group.calendar.google.com/private/full" Meeting \'2010-04-04T17:00:00Z\' acthex@gmail.com secretpassword
	std::cout<<"command will be executed next\n";
	std::string command="java calendarApp ";
	
	for(int i=0; i<parms.size(); i++)
	{	
		if(i!=3)
			command += parms[i].getString().substr(1, parms[i].getString().size()-2);
		else
			command = command + "\\"+parms[i].getString().substr(1, parms[i].getString().size()-3) + "\\'";
		command +=" ";
	}
	std::cout<<"command will be executed next\n";
	std::cout<<"printing command c_strsiz :"<<command;
	std::cout<<"printing command :"<<command.c_str();

	system(command.c_str());
	  
    }

    



 


  } // googlecalendar

} // dlvhex
