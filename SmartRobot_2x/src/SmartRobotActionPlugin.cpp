/**
 * @file SmartRobotActionPlugin.cpp
 * @author Stefano Germano
 *
 * @brief A simple Plugin of ActionPlugin that implements a Smart Robot
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */
#include "SmartRobotActionPlugin.h"

DLVHEX_NAMESPACE_BEGIN
SmartRobotActionPlugin::Environment::Environment() {
	name = "EnvironmentOfSmartRobotActionPlugin";

	currentRows = 10;
	currentColumns = 10;
	createMaze();

	firstExecution = true;

	currentPositionColumn = 0;
	currentPositionRow = 0;

	previousMovement = "none";

	numberOfUp = 0;
	numberOfDown = 0;
	numberOfLeft = 0;
	numberOfRight = 0;

}

SmartRobotActionPlugin::Environment::~Environment() {
	destroyMaze();
}

bool SmartRobotActionPlugin::Environment::isTheFirstExecution() const {
	return firstExecution;
}

void SmartRobotActionPlugin::Environment::finishedFirstExecution() {
	DBGLOG(PLUGIN, "Finished First Execution");
	firstExecution = false;
}

unsigned int SmartRobotActionPlugin::Environment::getCurrentPositionRow() const {
	return currentPositionRow;
}

unsigned int SmartRobotActionPlugin::Environment::getCurrentPositionColumn() const {
	return currentPositionColumn;
}

unsigned int SmartRobotActionPlugin::Environment::getCurrentRows() const {
	return currentRows;
}

unsigned int SmartRobotActionPlugin::Environment::getCurrentColumns() const {
	return currentColumns;
}

unsigned int SmartRobotActionPlugin::Environment::getNumberOfTimes(
		unsigned int row, unsigned int column) const {
	if (row >= currentRows || column >= currentColumns)
		throw PluginError("Wrong input argument type (in getNumberOfTimes)");
	return numberOfTimes[row][column];
}

void SmartRobotActionPlugin::Environment::refresh() const {

	int c = system("clear");

// 	std::cout << "   ";
// 	
// 	for(unsigned int j = 0; j < currentColumns; j++) {
// 		if(j < 10)
// 			std::cout << j;
// 		else
// 			if(j < 100)
// 				std::cout << j % 10;
// 			else
// 				if(j < 1000)
// 					std::cout << j % 100;
// 	}
// 	std::cout << std::endl;

	for (unsigned int i = 0; i < currentRows; i++) {
// 		if(i < 10)
// 			std::cout << "0" ;
// 		std::cout << i << " ";
		for (unsigned int j = 0; j < currentColumns; j++) {
			if (maze[i][j])
				std::cout << "+";
			else if (i == currentPositionRow && j == currentPositionColumn)
				if (foundTreasure())
					std::cout << "^";
				else
					std::cout << "0";
			else if (i == treasureRow && j == treasureColumn)
				std::cout << "*";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}

	if (foundTreasure())
		std::cout << "\n>>> I found the Treasure!!! <<<\n" << std::endl;
//		printMazeDetectedByTheRobot();
//	}
//	else if (theRobotExploredTheWholeMaze()) {
//		std::cout
//				<< "I explored the whole Maze but I haven't found the Treasure"
//				<< std::endl;
//		printMazeDetectedByTheRobot();
//	}

}

void SmartRobotActionPlugin::Environment::addWall(unsigned int row,
		unsigned int column) {
	if (row >= currentRows || column >= currentColumns)
		throw PluginError("Wrong input argument type (in addWall)");
	maze[row][column] = true;
	DBGLOG(PLUGIN, "Added " << row << " " << column);
}

void SmartRobotActionPlugin::Environment::setDimension(unsigned int rows,
		unsigned int columns) {
	if (rows < 3 || columns < 3)
		throw PluginError("Cannot set a dimension under 3 x 3");

	if (rows == currentRows || columns == currentColumns) {
		DBGLOG(PLUGIN, "The new dimension is the same as before");
		return;
	}
	DBGLOG(PLUGIN, "New dimension " << rows << " " << columns);
	destroyMaze();
	currentRows = rows;
	currentColumns = columns;
	createMaze();
}

void SmartRobotActionPlugin::Environment::createMaze() {
	maze = new bool *[currentRows];
	numberOfTimes = new unsigned int *[currentRows];
	mazeDetectedByTheRobot = new bool *[currentRows];
	for (unsigned int i = 0; i < currentRows; i++) {
		maze[i] = new bool[currentColumns];
		numberOfTimes[i] = new unsigned int[currentColumns];
		mazeDetectedByTheRobot[i] = new bool[currentColumns];
	}

	for (unsigned int i = 0; i < currentRows; i++)
		for (unsigned int j = 0; j < currentColumns; j++) {
			maze[i][j] = false;
			numberOfTimes[i][j] = 0;
			mazeDetectedByTheRobot[i][j] = false;
		}
}

void SmartRobotActionPlugin::Environment::destroyMaze() {
	for (unsigned int i = 0; i < currentRows; i++) {
		delete[] maze[i];
		delete[] numberOfTimes[i];
		delete[] mazeDetectedByTheRobot[i];
	}
	delete[] maze;
	delete[] numberOfTimes;
	delete[] mazeDetectedByTheRobot;
}

void SmartRobotActionPlugin::Environment::moveUp() {
	if (currentPositionRow == 0
			|| maze[currentPositionRow - 1][currentPositionColumn])
		throw PluginError("Cannot move up");

	currentPositionRow -= 1;
	previousMovement = "up";
	numberOfUp++;
	normalizeNumberOf();
	numberOfTimes[currentPositionRow][currentPositionColumn]++;
}

void SmartRobotActionPlugin::Environment::moveDown() {
	if (currentPositionRow == currentRows - 1
			|| maze[currentPositionRow + 1][currentPositionColumn])
		throw PluginError("Cannot move down");

	currentPositionRow += 1;
	previousMovement = "down";
	numberOfDown++;
	normalizeNumberOf();
	numberOfTimes[currentPositionRow][currentPositionColumn]++;
}

void SmartRobotActionPlugin::Environment::moveLeft() {
	if (currentPositionColumn == 0
			|| maze[currentPositionRow][currentPositionColumn - 1])
		throw PluginError("Cannot move left");

	currentPositionColumn -= 1;
	previousMovement = "left";
	numberOfLeft++;
	normalizeNumberOf();
	numberOfTimes[currentPositionRow][currentPositionColumn]++;
}

void SmartRobotActionPlugin::Environment::moveRight() {
	if (currentPositionColumn == currentColumns - 1
			|| maze[currentPositionRow][currentPositionColumn + 1])
		throw PluginError("Cannot move right");

	currentPositionColumn += 1;
	previousMovement = "right";
	numberOfRight++;
	normalizeNumberOf();
	numberOfTimes[currentPositionRow][currentPositionColumn]++;
}

void SmartRobotActionPlugin::Environment::normalizeNumberOf() {

	unsigned int min = numberOfUp;

	if (numberOfDown < min)
		min = numberOfDown;

	if (numberOfLeft < min)
		min = numberOfLeft;

	if (numberOfRight < min)
		min = numberOfRight;

	numberOfUp -= min;
	numberOfDown -= min;
	numberOfLeft -= min;
	numberOfRight -= min;

}

void SmartRobotActionPlugin::Environment::setCurrentPosition(unsigned int row,
		unsigned int column) {
	if (maze[row][column])
		throw PluginError("This position is occupied by a WALL");

	DBGLOG(PLUGIN, "New position " << row << " " << column);

	currentPositionRow = row;
	currentPositionColumn = column;

	numberOfTimes[row][column]++;

}

std::string SmartRobotActionPlugin::Environment::getPreviousMovement() const {
	return previousMovement;
}

unsigned int SmartRobotActionPlugin::Environment::getNumberOfUp() const {
	return numberOfUp;
}

unsigned int SmartRobotActionPlugin::Environment::getNumberOfDown() const {
	return numberOfDown;
}

unsigned int SmartRobotActionPlugin::Environment::getNumberOfLeft() const {
	return numberOfLeft;
}

unsigned int SmartRobotActionPlugin::Environment::getNumberOfRight() const {
	return numberOfRight;
}

bool SmartRobotActionPlugin::Environment::foundTreasure() const {
	return (currentPositionRow == treasureRow
			&& currentPositionColumn == treasureColumn);
}

void SmartRobotActionPlugin::Environment::putTreasure(unsigned int row,
		unsigned int column) {
	if (row >= currentRows || column >= currentColumns)
		throw PluginError("Wrong input argument type (in putTreasure)");
	treasureRow = row;
	treasureColumn = column;
}

void SmartRobotActionPlugin::Environment::addDetectedWall(unsigned int row,
		unsigned int column) {
	if (row >= currentRows || column >= currentColumns)
		throw PluginError("Wrong input argument type (in addDetectedWall)");
	mazeDetectedByTheRobot[row][column] = true;
	DBGLOG(PLUGIN, "Detected wall in " << row << " " << column);
}

bool SmartRobotActionPlugin::Environment::theRobotExploredTheWholeMaze() const {

	for (unsigned int i = 0; i < currentRows; i++)
		for (unsigned int j = 0; j < currentColumns; j++)
			if (!mazeDetectedByTheRobot[i][j] && numberOfTimes[i][j] == 0)
				return false;

	return true;

}

void SmartRobotActionPlugin::Environment::printMazeDetectedByTheRobot() const {

	std::cout << "Maze Detected by the Robot" << std::endl;

	for (unsigned int i = 0; i < currentRows; i++) {
		for (unsigned int j = 0; j < currentColumns; j++)
			if (mazeDetectedByTheRobot[i][j])
				std::cout << "+";
			else
				std::cout << " ";
		std::cout << std::endl;
	}

}

SmartRobotActionPlugin::SmartRobotActionAtomFirstExecution::SmartRobotActionAtomFirstExecution() :
		PluginActionAtom("firstExecution") {
	setOutputArity(0);
}

void SmartRobotActionPlugin::SmartRobotActionAtomFirstExecution::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 0)
		throw PluginError("Wrong input argument type");

	Tuple out;

	if (environment.isTheFirstExecution())
		answer.get().push_back(out);

}

SmartRobotActionPlugin::SmartRobotActionAtomGetPosition::SmartRobotActionAtomGetPosition() :
		PluginActionAtom("getPosition") {
	setOutputArity(2);
}

void SmartRobotActionPlugin::SmartRobotActionAtomGetPosition::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 0)
		throw PluginError("Wrong input argument type");

	std::stringstream concatstreamRow;
	concatstreamRow << environment.getCurrentPositionRow();

	std::stringstream concatstreamColumn;
	concatstreamColumn << environment.getCurrentPositionColumn();

	Tuple out;

	//
	// call Term::Term with second argument true to get a quoted string!
	//
	Term termRow(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamRow.str()));
	out.push_back(registry.storeTerm(termRow));
	Term termColumn(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamColumn.str()));
	out.push_back(registry.storeTerm(termColumn));
	answer.get().push_back(out);

}

SmartRobotActionPlugin::SmartRobotActionAtomPreviousMovement::SmartRobotActionAtomPreviousMovement() :
		PluginActionAtom("previousMovement") {
	setOutputArity(1);
}

void SmartRobotActionPlugin::SmartRobotActionAtomPreviousMovement::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 0)
		throw PluginError("Wrong input argument type");

	std::stringstream concatstream;
	concatstream << environment.getPreviousMovement();

	Tuple out;
	Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstream.str()));
	out.push_back(registry.storeTerm(term));
	answer.get().push_back(out);

}

SmartRobotActionPlugin::SmartRobotActionAtomWeights::SmartRobotActionAtomWeights() :
		PluginActionAtom("weights") {
	setOutputArity(4);
}

void SmartRobotActionPlugin::SmartRobotActionAtomWeights::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 0)
		throw PluginError("Wrong input argument type");

	std::stringstream concatstreamWup;
	concatstreamWup << environment.getNumberOfUp();

	std::stringstream concatstreamWdown;
	concatstreamWdown << environment.getNumberOfDown();

	std::stringstream concatstreamWleft;
	concatstreamWleft << environment.getNumberOfLeft();

	std::stringstream concatstreamWright;
	concatstreamWright << environment.getNumberOfRight();

	Tuple out;

	//
	// call Term::Term with second argument true to get a quoted string!
	//
	Term termUp(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamWup.str()));
	out.push_back(registry.storeTerm(termUp));
	Term termDown(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamWdown.str()));
	out.push_back(registry.storeTerm(termDown));
	Term termLeft(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamWleft.str()));
	out.push_back(registry.storeTerm(termLeft));
	Term termRight(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamWright.str()));
	out.push_back(registry.storeTerm(termRight));
	answer.get().push_back(out);

}

SmartRobotActionPlugin::SmartRobotActionAtomGetNumberOfTimes::SmartRobotActionAtomGetNumberOfTimes() :
		PluginActionAtom("getNumberOfTimes") {
	setOutputArity(4);
}

void SmartRobotActionPlugin::SmartRobotActionAtomGetNumberOfTimes::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 0)
		throw PluginError("Wrong input argument type");

	std::stringstream concatstreamUp;
	if (environment.getCurrentPositionRow() != 0)
		concatstreamUp
				<< environment.getNumberOfTimes(
						environment.getCurrentPositionRow() - 1,
						environment.getCurrentPositionColumn());
	else
		concatstreamUp << 0;

	std::stringstream concatstreamDown;
	if (environment.getCurrentPositionRow() < environment.getCurrentRows() - 1)
		concatstreamDown
				<< environment.getNumberOfTimes(
						environment.getCurrentPositionRow() + 1,
						environment.getCurrentPositionColumn());
	else
		concatstreamDown << 0;

	std::stringstream concatstreamLeft;
	if (environment.getCurrentPositionColumn() != 0)
		concatstreamLeft
				<< environment.getNumberOfTimes(
						environment.getCurrentPositionRow(),
						environment.getCurrentPositionColumn() - 1);
	else
		concatstreamLeft << 0;

	std::stringstream concatstreamRight;
	if (environment.getCurrentPositionColumn()
			< environment.getCurrentColumns() - 1)
		concatstreamRight
				<< environment.getNumberOfTimes(
						environment.getCurrentPositionRow(),
						environment.getCurrentPositionColumn() + 1);
	else
		concatstreamRight << 0;

	Tuple out;

	//
	// call Term::Term with second argument true to get a quoted string!
	//
	Term termUp(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamUp.str()));
	out.push_back(registry.storeTerm(termUp));
	Term termDown(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamDown.str()));
	out.push_back(registry.storeTerm(termDown));
	Term termLeft(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamLeft.str()));
	out.push_back(registry.storeTerm(termLeft));
	Term termRight(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(concatstreamRight.str()));
	out.push_back(registry.storeTerm(termRight));
	answer.get().push_back(out);

}

SmartRobotActionPlugin::SmartRobotActionAtomFoundTreasure::SmartRobotActionAtomFoundTreasure() :
		PluginActionAtom("foundTreasure") {
	setOutputArity(0);
}

void SmartRobotActionPlugin::SmartRobotActionAtomFoundTreasure::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 0)
		throw PluginError("Wrong input argument type");

	Tuple out;

	if (environment.foundTreasure())
		answer.get().push_back(out);

}

SmartRobotActionPlugin::SmartRobotActionAtomExploredTheWholeMaze::SmartRobotActionAtomExploredTheWholeMaze() :
		PluginActionAtom("exploredTheWholeMaze") {
	setOutputArity(0);
}

void SmartRobotActionPlugin::SmartRobotActionAtomExploredTheWholeMaze::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 0)
		throw PluginError("Wrong input argument type");

	Tuple out;

	if (environment.theRobotExploredTheWholeMaze())
		answer.get().push_back(out);

}

SmartRobotActionPlugin::SmartRobotAction::SmartRobotAction() :
		PluginAction("smartRobot") {
}

void SmartRobotActionPlugin::SmartRobotAction::execute(Environment& environment,
		RegistryPtr pregistry, const Tuple& parms,
		const InterpretationConstPtr interpretationPtr) {
	Registry& registry = *pregistry;

	if (registry.getTermStringByID(parms[0]) == "move") {
		if (registry.getTermStringByID(parms[1]) == "up")
			environment.moveUp();
		else if (registry.getTermStringByID(parms[1]) == "down")
			environment.moveDown();
		else if (registry.getTermStringByID(parms[1]) == "left")
			environment.moveLeft();
		else if (registry.getTermStringByID(parms[1]) == "right")
			environment.moveRight();
		else
			throw PluginError("Unknown move!");

		environment.refresh();

	} else if (registry.getTermStringByID(parms[0]) == "addWall") {
		environment.addWall(parms[1].address, parms[2].address);
		environment.refresh();
	} else if (registry.getTermStringByID(parms[0]) == "setDimension")
		environment.setDimension(parms[1].address, parms[2].address);
	else if (registry.getTermStringByID(parms[0]) == "setPosition")
		environment.setCurrentPosition(parms[1].address, parms[2].address);
	else if (registry.getTermStringByID(parms[0]) == "finishedFirstExecution")
		environment.finishedFirstExecution();
	else if (registry.getTermStringByID(parms[0]) == "putTreasure")
		environment.putTreasure(parms[1].address, parms[2].address);
	else if (registry.getTermStringByID(parms[0]) == "addDetectedWall")
		environment.addDetectedWall(parms[1].address, parms[2].address);
	else if (registry.getTermStringByID(parms[0])
			== "printMazeDetectedByTheRobot")
		environment.printMazeDetectedByTheRobot();

// 	environment.refresh();

}

std::vector<PluginAtomPtr> SmartRobotActionPlugin::createAtoms(
		ProgramCtx& ctx) const {
	std::vector < PluginAtomPtr > ret;
	ret.push_back(
			PluginAtomPtr(new SmartRobotActionAtomFirstExecution,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SmartRobotActionAtomGetPosition,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SmartRobotActionAtomPreviousMovement,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SmartRobotActionAtomWeights,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SmartRobotActionAtomGetNumberOfTimes,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SmartRobotActionAtomFoundTreasure,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SmartRobotActionAtomExploredTheWholeMaze,
					PluginPtrDeleter<PluginAtom>()));
	return ret;
}

std::vector<PluginActionBasePtr> SmartRobotActionPlugin::createActions(
		ProgramCtx& ctx) const {
	std::vector < PluginActionBasePtr > ret;
	ret.push_back(
			PluginActionBasePtr(new SmartRobotAction,
					PluginPtrDeleter<PluginActionBase>()));
	return ret;
}

//
// now instantiate the plugin
//
SmartRobotActionPlugin theSmartRobotActionPlugin;

DLVHEX_NAMESPACE_END

//
// let it be loaded by dlvhex!
//
IMPLEMENT_PLUGINABIVERSIONFUNCTION

// return plain C type s.t. all compilers and linkers will like this code
extern "C" void * PLUGINIMPORTFUNCTION() {
return reinterpret_cast<void*>(& DLVHEX_NAMESPACE theSmartRobotActionPlugin);
}
