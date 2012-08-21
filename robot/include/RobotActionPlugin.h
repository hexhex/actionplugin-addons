/**
 * @file RobotActionPlugin.h
 * @author Stefano Germano
 *
 * @brief ...
 */

#ifndef ROBOT_ACTION_PLUGIN_H_
#define ROBOT_ACTION_PLUGIN_H_

#include "acthex/ActionPluginInterface.h"

#include <stdlib.h>
#include <time.h>

DLVHEX_NAMESPACE_BEGIN

class RobotActionPlugin: public ActionPluginInterface {

public:

	class Environment: public PluginEnvironment {
	public:
		Environment() {
			name = "EnvironmentOfRobotActionPlugin";

			srand(time(0));
			this->quantityOfFuel = rand() % 2;
		}
		bool getQuantityOfFuel() const {
			return quantityOfFuel;
		}
		virtual ~Environment() {
		}
		;
	private:
		std::string name;
		bool quantityOfFuel;
	};

	RobotActionPlugin() :
			ActionPluginInterface() {
		setNameVersion(PACKAGE_TARNAME, ROBOTACTIONPLUGIN_VERSION_MAJOR,
				ROBOTACTIONPLUGIN_VERSION_MINOR,
				ROBOTACTIONPLUGIN_VERSION_MICRO);
	}

	class RobotActionAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		RobotActionAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class RobotAction: public PluginAction<RobotActionPlugin> {

	public:

		RobotAction();

	private:

		std::vector<std::string> world;
		std::vector<std::string> tempWorld;
		int currentX;
		int currentY;
		bool currentAlarm;

		void putRobotInWorld(int x, int y);

		void moveDown(int x);

		void moveUp(int x);

		void moveLeft(int x);

		void moveRight(int x);

		void refresh();

		void turnAlarmOn();

		void turnAlarmOff();

		void leftCorridor();

		void rightCorridor();

		virtual void execute(Environment& environment, RegistryPtr registry,
				const Tuple& parms, InterpretationConstPtr interpretationPtr);

	};

	virtual std::vector<PluginAtomPtr> createAtoms(ProgramCtx& ctx) const;

	virtual std::vector<PluginActionBasePtr> createActions(
			ProgramCtx& ctx) const;

protected:

	ActionPluginInterfacePtr create(ProgramCtx& ctx) {
		std::cerr << "create in RobotActionPlugin" << std::endl;
#warning a trick, maybe we should find a way remove it
		ctx.getPluginEnvironment<RobotActionPlugin>();
		std::cerr << "getPluginEnvironment done" << std::endl;
		return boost::shared_ptr < RobotActionPlugin > (new RobotActionPlugin());
	}

};

DLVHEX_NAMESPACE_END

#endif /* ROBOT_ACTION_PLUGIN_H_ */
