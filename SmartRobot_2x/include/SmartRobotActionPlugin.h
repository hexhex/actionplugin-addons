/**
 * @file SmartRobotActionPlugin.h
 * @author Stefano Germano
 *
 * @brief A simple Plugin of ActionPlugin that implements a Smart Robot
 */

#ifndef SMART_ROBOT_ACTION_PLUGIN_H_
#define SMART_ROBOT_ACTION_PLUGIN_H_

#include "acthex/ActionPluginInterface.h"

DLVHEX_NAMESPACE_BEGIN

class SmartRobotActionPlugin: public ActionPluginInterface {

public:

	class Environment: public PluginEnvironment {
	public:
		Environment();
		virtual ~Environment();
		void addWall(unsigned int, unsigned int);
		void setDimension(unsigned int, unsigned int);
		void setCurrentPosition(unsigned int, unsigned int);
		unsigned int getCurrentPositionRow() const;
		unsigned int getCurrentPositionColumn() const;
		unsigned int getCurrentRows() const;
		unsigned int getCurrentColumns() const;
		void setPosition(unsigned int, unsigned int);
		bool isTheFirstExecution() const;
		void refresh() const;
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void finishedFirstExecution();
		std::string getPreviousMovement() const;
		unsigned int getNumberOfUp() const;
		unsigned int getNumberOfDown() const;
		unsigned int getNumberOfLeft() const;
		unsigned int getNumberOfRight() const;
		unsigned int getNumberOfTimes(unsigned int, unsigned int) const;
		bool foundTreasure() const;
		void putTreasure(unsigned int, unsigned int);
		void addDetectedWall(unsigned int, unsigned int);
		bool theRobotExploredTheWholeMaze() const;
		void printMazeDetectedByTheRobot() const;
	private:
		std::string name;
		bool ** maze; //true if there is a wall, false otherwise
		unsigned int currentPositionRow;
		unsigned int currentPositionColumn;
		unsigned int currentRows;
		unsigned int currentColumns;
		bool firstExecution;
		std::string previousMovement;
		unsigned int numberOfUp;
		unsigned int numberOfDown;
		unsigned int numberOfLeft;
		unsigned int numberOfRight;
		void normalizeNumberOf();
		unsigned int ** numberOfTimes; //the number of times that the robot has been in each cell
		unsigned int treasureRow;
		unsigned int treasureColumn;
		bool ** mazeDetectedByTheRobot; //the maze detected by the robot
		void createMaze();
		void destroyMaze();
	};

	SmartRobotActionPlugin() :
			ActionPluginInterface() {
		setNameVersion(PACKAGE_TARNAME, SMARTROBOTACTIONPLUGIN_VERSION_MAJOR,
				SMARTROBOTACTIONPLUGIN_VERSION_MINOR,
				SMARTROBOTACTIONPLUGIN_VERSION_MICRO);
	}

	class SmartRobotActionAtomFirstExecution: public PluginActionAtom<
			SmartRobotActionPlugin> {
	public:
		SmartRobotActionAtomFirstExecution();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SmartRobotActionAtomGetPosition: public PluginActionAtom<
			SmartRobotActionPlugin> {
	public:
		SmartRobotActionAtomGetPosition();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SmartRobotActionAtomPreviousMovement: public PluginActionAtom<
			SmartRobotActionPlugin> {
	public:
		SmartRobotActionAtomPreviousMovement();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SmartRobotActionAtomWeights: public PluginActionAtom<
			SmartRobotActionPlugin> {
	public:
		SmartRobotActionAtomWeights();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SmartRobotActionAtomGetNumberOfTimes: public PluginActionAtom<
			SmartRobotActionPlugin> {
	public:
		SmartRobotActionAtomGetNumberOfTimes();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SmartRobotActionAtomFoundTreasure: public PluginActionAtom<
			SmartRobotActionPlugin> {
	public:
		SmartRobotActionAtomFoundTreasure();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SmartRobotActionAtomExploredTheWholeMaze: public PluginActionAtom<
			SmartRobotActionPlugin> {
	public:
		SmartRobotActionAtomExploredTheWholeMaze();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SmartRobotAction: public PluginAction<SmartRobotActionPlugin> {

	public:

		SmartRobotAction();

	private:
		virtual void execute(Environment&, RegistryPtr, const Tuple&,
				const InterpretationConstPtr);

	};

	virtual std::vector<PluginAtomPtr> createAtoms(ProgramCtx& ctx) const;

	virtual std::vector<PluginActionBasePtr> createActions(
			ProgramCtx& ctx) const;

protected:

	ActionPluginInterfacePtr create(ProgramCtx& ctx) {
		DBGLOG(PLUGIN, "create in SmartRobotActionPlugin");
#warning a trick, maybe we should find a way remove it
		ctx.getPluginEnvironment<SmartRobotActionPlugin>();
		DBGLOG(PLUGIN, "getPluginEnvironment done");
		return boost::shared_ptr < SmartRobotActionPlugin
				> (new SmartRobotActionPlugin());
	}

};

DLVHEX_NAMESPACE_END

#endif /* SMART_ROBOT_ACTION_PLUGIN_H_ */
