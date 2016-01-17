/* -*- C++ -*- */
/**
 * @file KBModActionPlugin.cpp
 * @author Selen Başol
 * @author Ozan Erdem
 * @author Stefano Germano
 *
 * @brief Header file for KBModActionAddon
 *
 */

/** @mainpage dlvhex-kbmodplugin Source Documentation
 *
 * \section Overview
 * This plugin implements functions which adds a given fact/rule to a knowledge base
 * The syntax is presented below:
 * \code
 * #assert[FILENAME,FACT_OR_RULE]{OPT,PREC}[W:L].
 * \endcode
 *
 * Where FILENAME is the name of the file which contains the knowledge base, FACT_OR_RULE
 * is the fact or rule to be added as a string,
 * OPT is the action option, PREC is the action precedence,
 * W is the action weight, and L is the action level.
 *
 * A simple example:
 *
 * \code
 * #assert["/home/foo/knowledge.txt","bar."]{b,1}[2:1].
 * \endcode
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H
#include "KBModActionPlugin.h"
#include <iostream>

DLVHEX_NAMESPACE_BEGIN

KBModActionPlugin::Environment::Environment() {
	name = "EnvironmentOfKBModActionPlugin";
}

KBModActionPlugin::Environment::~Environment() {
}

std::vector<PluginActionBasePtr> KBModActionPlugin::createActions(
		ProgramCtx& ctx) const {
	std::vector < PluginActionBasePtr > ret;
	ret.push_back(
			PluginActionBasePtr(new AssertAtom(),
					PluginPtrDeleter<PluginActionBase>()));
	ret.push_back(
			PluginActionBasePtr(new RetractAtom(),
					PluginPtrDeleter<PluginActionBase>()));
	ret.push_back(
			PluginActionBasePtr(new ExecuteAtom(),
					PluginPtrDeleter<PluginActionBase>()));
	return ret;

}

//
// now instantiate the plugin
//
KBModActionPlugin theKBModActionPlugin;

DLVHEX_NAMESPACE_END

//
// let it be loaded by dlvhex!
//
IMPLEMENT_PLUGINABIVERSIONFUNCTION

// return plain C type s.t. all compilers and linkers will like this code
extern "C" void * PLUGINIMPORTFUNCTION() {
return reinterpret_cast<void*>(& DLVHEX_NAMESPACE theKBModActionPlugin);
}

