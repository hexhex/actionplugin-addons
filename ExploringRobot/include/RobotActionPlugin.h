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
		Environment():map{{0,0,1,0},{1,0,0,0},{0,0,1,0},{0,0,1,0}},temp_map{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}} {
			name = "EnvironmentOfRobotActionPlugin";

			//srand(time(0));
			//this->quantityOfFuel = rand() % 2;
			//temp_map[0][0]=1;
			currentX = 0;
			currentY = 0;
			failureReason="";
			//obsX = 0;
			//obsY = 3;
			std::cout << "Robot is at " << currentX << ", " << currentY << std::endl;
			//std::cout << "Obstacle is at " << obsX << ", " << obsY << std::endl;
			std::cout << "---------------------------------------" << std::endl;
		}
		//bool getQuantityOfFuel() const {
		//	return quantityOfFuel;
		//}
		virtual ~Environment() {
		}
		;
		void moveDown();
		void moveRight();		
		void moveUp();
		void moveLeft();
		void updateMap(int,int,int);
		void senseObstacle();
		bool robotVisited(int,int) const;
		bool robotFoundObstacle(int,int) const;
		bool obstacleExists(int,int) const;
		bool failure() const;
		bool reached() const;
		void resetFailureReason();
		
		unsigned int getRobotPositionX() const;
		unsigned int getRobotPositionY() const;
		//unsigned int getObsPositionX() const;
		//unsigned int getObsPositionY() const;
	private:
		std::string name;
		std::string failureReason;
		int map[4][4];
		int temp_map[4][4];
		//bool quantityOfFuel;
		
		unsigned int currentX;
		unsigned int currentY;
		//unsigned int obsX;
		//unsigned int obsY;
	};

	RobotActionPlugin() :
			ActionPluginInterface() {
		setNameVersion(PACKAGE_TARNAME, ROBOTACTIONPLUGIN_VERSION_MAJOR,
				ROBOTACTIONPLUGIN_VERSION_MINOR,
				ROBOTACTIONPLUGIN_VERSION_MICRO);
	}

	class RobotLocationExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		RobotLocationExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class ObstacleLocationExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		ObstacleLocationExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class VisitedExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		VisitedExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SenseExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		SenseExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class ReachedExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		ReachedExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class RobotAction: public PluginAction<RobotActionPlugin> {

	public:

		RobotAction();

	private:

		//std::vector<std::string> world;
		//std::vector<std::string> tempWorld;
		//bool currentAlarm;

		//void putRobotInWorld(int x, int y);

		//void moveDown(int x);

		//void moveUp(int x);
		//void moveUp();

		//void moveLeft(int x);

		//void moveRight(int x);
		//void moveRight();

		//void refresh();

		//void turnAlarmOn();

		//void turnAlarmOff();

		//void leftCorridor();

		//void rightCorridor();

		virtual void execute(Environment& environment, RegistryPtr registry,
				const Tuple& parms, InterpretationConstPtr interpretationPtr);

	};

	virtual std::vector<PluginAtomPtr> createAtoms(ProgramCtx& ctx) const;

	virtual std::vector<PluginActionBasePtr> createActions(
			ProgramCtx& ctx) const;

protected:

	ActionPluginInterfacePtr create(ProgramCtx& ctx) {
		DBGLOG(PLUGIN, "create in RobotActionPlugin");
#warning a trick, maybe we should find a way remove it
		ctx.getPluginEnvironment<RobotActionPlugin>();
		DBGLOG(PLUGIN, "getPluginEnvironment done");
		return boost::shared_ptr < RobotActionPlugin > (new RobotActionPlugin());
	}

};

DLVHEX_NAMESPACE_END

#endif /* ROBOT_ACTION_PLUGIN_H_ */
