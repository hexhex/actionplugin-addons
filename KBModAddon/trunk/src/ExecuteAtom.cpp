/* dlvhex-KBModaddon -- KBMod addon for dlvhex.
 * 2009 Selen Başol, Ozan Erdem
 *
 * This file is part of dlvhex-KBModaddon.
 *
 * dlvhex-KBModaddon is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * dlvhex-KBModaddon is distributed in the hope that it will be
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
 * @file   ExecuteAtom.cpp
 * @author Selen Başol
 * @author Ozan Erdem
 *
 * @brief Handling of execute atoms
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "KBModAddon.h"
#include "ExecuteAtom.h"

#include <iostream>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <sstream>


namespace dlvhex
{
  namespace kbmod
  {


    ExecuteAtom::~ExecuteAtom()
    {
      
    }

	ExecuteAtom::ExecuteAtom(KBModAddon& kbmod) : kbmod_addon(kbmod)
	{
		//addInputConstant();	
		//addInputConstant();			
	}



    // Standard function takes the query as an input and evaluates the associated function 
    void
    ExecuteAtom::execute(const Tuple & parms) throw(PluginError)
    {
	assert(parms.size()>0);


	  std::string command;//=parms[0].getString();
	for (int i=0; i< parms.size(); i++)
	{
		if(!parms[i].isString())
		{
			std::ostringstream a_int;
			a_int<<parms[i];
			std::string int_str=a_int.str();
			command+=int_str;
		}	
		else
		{
			if(parms[i].getString()[0]!='\"' || parms[i].getString()[parms[i].getString().size()-1]!='\"')
			{
		  		throw PluginError("The parameter of the atom #execute should be a quoted string!");
		  	}
			command+=parms[i].getString().substr(1,parms[i].getString().size()-2);
		}
	}

	system(command.c_str());

    }

    



 


  } // robot

} // dlvhex
