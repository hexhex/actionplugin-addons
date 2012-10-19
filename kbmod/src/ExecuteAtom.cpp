/* dlvhex-KBModActionAddon -- KBMod addon for dlvhex.
 * 2009 Selen Başol, Ozan Erdem
 *
 * This file is part of dlvhex-KBModActionAddon.
 *
 * dlvhex-KBModActionAddon is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * dlvhex-KBModActionAddon is distributed in the hope that it will be
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
 * @author Stefano Germano
 *
 * @brief Handling of execute atoms
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H
#include "KBModActionPlugin.h"

#include <iostream>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <sstream>

DLVHEX_NAMESPACE_BEGIN

KBModActionPlugin::ExecuteAtom::ExecuteAtom() :
		PluginAction("execute") {
}

// Standard function takes the query as an input and evaluates the associated function
void KBModActionPlugin::ExecuteAtom::execute(Environment& environment,
		RegistryPtr pregistry, const Tuple& parms,
		const InterpretationConstPtr interpretationPtr) {

	Registry& registry = *pregistry;

	assert(parms.size() > 0);

	std::string command;
	for (int i = 0; i < parms.size(); i++) {
		if (parms[i].isIntegerTerm()) {
			std::ostringstream a_int;
			a_int << parms[i].address;
			std::string int_str = a_int.str();
			command += int_str;
		} else if (parms[i].isConstantTerm() || parms[i].isVariableTerm()) {
			std::string termStr = registry.getTermStringByID(parms[i]);
			command += termStr;
		} else {
			std::string termStr = registry.getTermStringByID(parms[i]);
			if (termStr[0] != '\"' || termStr[termStr.size() - 1] != '\"') {
				throw PluginError(
						"The parameter of the atom #execute should be a quoted string!");
			}
			command += termStr.substr(1, termStr.size() - 2);
		}
	}

	system(command.c_str());

}

DLVHEX_NAMESPACE_END
