/* -*- C++ -*- */
/**
 * @file KBModActionPlugin.h
 * @author Selen Başol
 * @author Ozan Erdem
 * @author Stefano Germano
 *
 * @brief Header file for KBModPlugin
 *
 */
#ifndef KBMOD_ACTION_PLUGIN_H
#define KBMOD_ACTION_PLUGIN_H

#include <dlvhex/Error.h>

#include "acthex/ActionPluginInterface.h"

DLVHEX_NAMESPACE_BEGIN

class KBModActionPlugin: public ActionPluginInterface {

public:
	
	class Environment: public PluginEnvironment {
	public:
		Environment();
		virtual ~Environment();
	private:
		std::string name;
	};
	
	KBModActionPlugin() :
			ActionPluginInterface() {
		setNameVersion(PACKAGE_TARNAME, KBMODPLUGIN_VERSION_MAJOR,
				KBMODPLUGIN_VERSION_MINOR, KBMODPLUGIN_VERSION_MICRO);
	}

	virtual std::vector<PluginActionBasePtr> createActions(
			ProgramCtx& ctx) const;

	class AssertAtom: public PluginAction<KBModActionPlugin> {

	public:
		/**
		 * Constructor of KBModatom. Defines the inputConstant of the plugin atom.
		 */
		AssertAtom();

	protected:
		/**
		 * Retrieves the resulting kbmod tuples in the answer object for the input query.
		 */
		void execute(Environment&, RegistryPtr, const Tuple&,
				const InterpretationConstPtr);

	};

	class ExecuteAtom: public PluginAction<KBModActionPlugin> {

	public:
		/**
		 * Constructor of KBModatom. Defines the inputConstant of the addon atom.
		 */
		ExecuteAtom();

	protected:
		/**
		 * Retrieves the resulting kbmod tuples in the answer object for the input query.
		 */
		void execute(Environment&, RegistryPtr, const Tuple&,
				const InterpretationConstPtr);

	};

	class RetractAtom: public PluginAction<KBModActionPlugin> {

	public:
		/**
		 * Constructor of KBModatom. Defines the inputConstant of the plugin atom.
		 */
		RetractAtom();

	protected:
		/**
		 * Retrieves the resulting kbmod tuples in the answer object for the input query.
		 */
		void execute(Environment&, RegistryPtr, const Tuple&,
				const InterpretationConstPtr);

	};
	
protected:
	
	ActionPluginInterfacePtr create(ProgramCtx& ctx) {
		DBGLOG(PLUGIN, "create in KBModActionPlugin");
		#warning a trick, maybe we should find a way remove it
		ctx.getPluginEnvironment<KBModActionPlugin>();
		DBGLOG(PLUGIN, "getPluginEnvironment done");
		return boost::shared_ptr < KBModActionPlugin
		> (new KBModActionPlugin());
	}

};

DLVHEX_NAMESPACE_END

#endif /* KBMOD_ACTION_PLUGIN_H */
