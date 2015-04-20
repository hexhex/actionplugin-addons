/**
 * @file RobotActionPlugin.h
 * @author Zeynep G. Saribatur 2015
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
		Environment():map{{0,0,1,0},{1,0,0,0},{2,0,1,0},{0,0,1,0}},temp_map{{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}} {
		//Environment():map{{0,0},{1,0},{2,0}},temp_map{{-1,-1},{-1,-1},{-1,-1}} {
			name = "EnvironmentOfRobotActionPlugin";

			currentX = 0;
			currentY = 0;
			lostPerson = 1;
			goalX=3;
			goalY=3;
			//goalX=1;
			//goalY=1;
			maxrow=3;
			maxcol=3;
			failureReason="none";
			std::cout << "Robot is at " << currentX << ", " << currentY << std::endl;
			std::cout << "---------------------------------------" << std::endl;
		}
		virtual ~Environment() {
		}
		;
		void moveDown();
		void moveRight();		
		void moveUp();
		void moveLeft();
		void changeGoal();
		void moveTo(int,int);
		void updateMap(int,int,int);
		void updateMainMap(int,int,int);
		void senseSurroundingCells();
		int sense(int,int) const;
		int senseKnowledge(int,int) const;
		bool robotVisited(int,int) const;
		bool robotSensed(int,int) const;
		bool robotFoundObstacle(int,int) const;
		bool robotFoundPerson(int,int) const;
		bool savedAll() const;
		std::string getFailureReason() const; 
		void resetFailureReason();
		
		unsigned int getRobotPositionX() const;
		unsigned int getRobotPositionY() const;		
		unsigned int getGoalX() const;
		unsigned int getGoalY() const;
		//unsigned int getObsPositionX() const;
		//unsigned int getObsPositionY() const;

		
		int maxrow;
		int maxcol;
	private:
		std::string name;
		std::string failureReason;
		int map[4][4];
		int temp_map[4][4];
		//int map[3][2];
		//int temp_map[3][2];
		//bool quantityOfFuel;
		
		unsigned int currentX;
		unsigned int currentY;
		unsigned int goalX;
		unsigned int goalY;
		unsigned int lostPerson;
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


	class PersonLocationExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		PersonLocationExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class ReachableExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		ReachableExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class VisitedExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		VisitedExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SavedExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		SavedExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class FailureExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		FailureExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class GoalExternalAtom: public PluginActionAtom<RobotActionPlugin> {
	public:
		GoalExternalAtom();
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class RobotAction: public PluginAction<RobotActionPlugin> {

	public:

		RobotAction();

	private:

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
