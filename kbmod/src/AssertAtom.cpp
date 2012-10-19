/* dlvhex-KBModActionAddon -- KBMod addon for dlvhex.
 * 2009 Selen Başol, Ozan Erdem
 *
 * This file is part of dlvhex-robotplugin.
 *
 * dlvhex-robotplugin is free software; you can redistribute it
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
 * @file   AssertAtom.cpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @author Stefano Germano
 *
 * @brief Handling of assert atoms
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H
#include "KBModActionPlugin.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

DLVHEX_NAMESPACE_BEGIN

KBModActionPlugin::AssertAtom::AssertAtom() :
		PluginAction("assert") {
}

// Standard function takes the query as an input and evaluates the associated function
void KBModActionPlugin::AssertAtom::execute(Environment& environment,
		RegistryPtr pregistry, const Tuple& parms,
		const InterpretationConstPtr interpretationPtr) {

	Registry& registry = *pregistry;

	std::string fileNameStr = registry.getTermStringByID(parms[0]);
	std::string assert_str = "";
	if (fileNameStr[0] != '\"' || fileNameStr[fileNameStr.size() - 1] != '\"') {

		throw PluginError(
				"The first parameter of the atom #assert should be a quoted string!");
	}
	fileNameStr = fileNameStr.substr(1, fileNameStr.size() - 2);

	for (int i = 1; i < parms.size(); i++) {

		if (parms[i].isIntegerTerm()) {
			std::ostringstream a_int;
			a_int << parms[i].address;
			std::string int_str = a_int.str();
			assert_str += int_str;
		} else if (parms[i].isConstantTerm()) {
			std::string simbolStr = registry.getTermStringByID(parms[i]);
			assert_str += simbolStr;
		} else {
			std::string ruleStr = registry.getTermStringByID(parms[i]);
			if (ruleStr[0] != '\"' || ruleStr[ruleStr.size() - 1] != '\"') {
				throw PluginError(
						"The parameters of the atom #assert should be a quoted string or an integer!");
			}
			ruleStr = ruleStr.substr(1, ruleStr.size() - 2);
			assert_str += ruleStr;
		}

	}
	//std::cout<<"RULE : "<< assert_str<<std::endl;

	std::ofstream output;
	output.open(fileNameStr.c_str(), std::ios::app);
	if (!output.is_open()) {
		throw PluginError("Could not open the knowledge base");
	}
	output << assert_str << std::endl;
	output.close();

}

DLVHEX_NAMESPACE_END
