/**
 * @file RobotActionPlugin.cpp
 * @author Stefano Germano
 *
 * @brief ...
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */
#include "RobotActionPlugin.h"

DLVHEX_NAMESPACE_BEGIN

void RobotActionPlugin::Environment::moveDown() {
	//updateMap(currentX,currentY,1);
	if(temp_map[currentX+1][currentY]==2){
		std::cout << " Obstacle in the way! " ;
		failureReason="Obstacle";
		return;
	}
	currentX += 1;
	//std::cout << "Robot is at " << currentX << ", " << currentY;
}

void RobotActionPlugin::Environment::moveRight() {
	//updateMap(currentX,currentY,1);
	if(temp_map[currentX][currentY+1]==2){
		std::cout << " Obstacle in the way! " ;
		failureReason="Obstacle";
		return;
	}
	currentY += 1;
	//std::cout << "Robot is at " << currentX << ", " << currentY;
}
void RobotActionPlugin::Environment::moveUp() {
	//updateMap(currentX,currentY,1);
	if(temp_map[currentX-1][currentY]==2){
		std::cout << " Obstacle in the way! " ;
		failureReason="Obstacle";
		return;
	}
	currentX -= 1;
	//std::cout << "Robot is at " << currentX << ", " << currentY;
}

void RobotActionPlugin::Environment::moveLeft() {
	//updateMap(currentX,currentY,1);
	if(temp_map[currentX][currentY-1]==2){
		std::cout << " Obstacle in the way! " ;
		failureReason="Obstacle";
		return;
	}
	currentY -= 1;
	//std::cout << "Robot is at " << currentX << ", " << currentY;
}

void RobotActionPlugin::Environment::updateMap(int a, int b, int c){
	if(c==1) //if it's about robot location
		temp_map[a][b]=1; 
	else if(c==2) //if it's about obstacle location
		temp_map[a][b]=2;
}

void RobotActionPlugin::Environment::resetFailureReason(){
	failureReason="";
}

bool RobotActionPlugin::Environment::obstacleExists(int a, int b) const{
	if (map[a][b]==1)
		return true;
	return false;
}

bool RobotActionPlugin::Environment::failure() const{
	if (failureReason!="")
		return true;
	return false;
}

void RobotActionPlugin::Environment::senseObstacle(){
	int robposx=currentX;
	int robposy=currentY;
	updateMap(currentX,currentY,1);

	if (robposx<3 && obstacleExists(robposx+1,robposy)){
		
		updateMap(robposx+1,robposy,2);
		std::cout << " Obstacle - down " ;
		std::cout << " Obstacle at " << robposx+1 << ", " << robposy << " ";
	}
	if(robposx>0 && obstacleExists(robposx-1,robposy)){
		
		updateMap(robposx-1,robposy,2);
		std::cout << " Obstacle - up " ;
		std::cout << " Obstacle at " << robposx-1 << ", " << robposy << " ";
	}
	if(robposy>0 && obstacleExists(robposx,robposy-1)){
		
		updateMap(robposx,robposy-1,2);
		std::cout << " Obstacle - left " ;
		std::cout << " Obstacle at " << robposx << ", " << robposy-1 << " ";
	
	}
	if(robposy<3 && obstacleExists(robposx,robposy+1)){
		
		updateMap(robposx,robposy+1,2);
		std::cout << " Obstacle - right " ;
		std::cout << " Obstacle at " << robposx << ", " << robposy+1 << " ";
	}
}

bool RobotActionPlugin::Environment::robotVisited(int a, int b) const{
	if (temp_map[a][b]==1)
		return true;
	return false;
}

bool RobotActionPlugin::Environment::robotFoundObstacle(int a, int b) const{
	if (temp_map[a][b]==2)
		return true;
	return false;
}

unsigned int RobotActionPlugin::Environment::getRobotPositionX() const {
	return currentX;
}

unsigned int RobotActionPlugin::Environment::getRobotPositionY() const {
	return currentY;
}




bool RobotActionPlugin::Environment::reached() const {
	std::cout << " - checking if reached - " << std::endl;
	if (currentX==3 && currentY==3)
		return true;
	return false;

}


RobotActionPlugin::VisitedExternalAtom::VisitedExternalAtom() :
		PluginActionAtom("visited") {
	//addInputConstant();
	setOutputArity(2);
}

void RobotActionPlugin::VisitedExternalAtom::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {
	Registry &registry = *getRegistry();
	Tuple out;

	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(environment.robotVisited(i,j)){
				Tuple out;
				std::stringstream getX;
				std::stringstream getY;
				getX << i;
				getY << j;
				std::cout << " Visited " << getX.str() << ", " << getY.str() << " ";
				Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
						std::string(getX.str()));
				out.push_back(registry.storeTerm(termX));

				Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
						std::string(getY.str()));
				out.push_back(registry.storeTerm(termY));
				answer.get().push_back(out);
			}
		}
	}
	
}



RobotActionPlugin::RobotLocationExternalAtom::RobotLocationExternalAtom() :
		PluginActionAtom("robotLocation") {
	setOutputArity(2);
}


void RobotActionPlugin::RobotLocationExternalAtom::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();
	
	Tuple out;

	std::stringstream getX;
	std::stringstream getY;

	getX << environment.getRobotPositionX();
	getY << environment.getRobotPositionY();
	std::cout << "Robot is at " << getX.str() << ", " << getY.str();	
	
	
	Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(getX.str()));
	out.push_back(registry.storeTerm(termX));

	Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(getY.str()));
	out.push_back(registry.storeTerm(termY));
	answer.get().push_back(out);
	
}

RobotActionPlugin::ObstacleLocationExternalAtom::ObstacleLocationExternalAtom() :
		PluginActionAtom("obstacleLocation") {
	setOutputArity(2);
}


void RobotActionPlugin::ObstacleLocationExternalAtom::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();
	
	Tuple out;

	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(environment.robotFoundObstacle(i,j)){
				Tuple out;
				std::stringstream getX;
				std::stringstream getY;
				getX << i;
				getY << j;
				std::cout << " Know obstacle at " << getX.str() << ", " << getY.str() << " ";
				Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
						std::string(getX.str()));
				out.push_back(registry.storeTerm(termX));

				Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
						std::string(getY.str()));
				out.push_back(registry.storeTerm(termY));
				answer.get().push_back(out);
			}
		}
	}
	
	
}

RobotActionPlugin::ReachedExternalAtom::ReachedExternalAtom() :
		PluginActionAtom("reached") {
	//addInputConstant();
	setOutputArity(0);
}

void RobotActionPlugin::ReachedExternalAtom::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Tuple out;

	if (environment.reached())
		answer.get().push_back(out);
	
}

RobotActionPlugin::RobotAction::RobotAction() :
		PluginAction("robot") {
	
}

void RobotActionPlugin::RobotAction::execute(Environment& environment,
		RegistryPtr pregistry, const Tuple& parms,
		InterpretationConstPtr interpretationPtr) {
	Registry& registry = *pregistry;

	int c = system("clear");	
	
	if(registry.getTermStringByID(parms[0]) == "resetFailureReason") {
		std::cout << " resetFailureReason " ;
		environment.resetFailureReason();
	}
	else{
	
		if(environment.failure())
			return;

		if (registry.getTermStringByID(parms[0]) == "move") {

			if (registry.getTermStringByID(parms[1]) == "down") {
				std::cout << " Move down " ;
				environment.moveDown();
			} else if (registry.getTermStringByID(parms[1]) == "right") {
				std::cout << " Move right ";
				environment.moveRight();
			}  else if (registry.getTermStringByID(parms[1]) == "up") {
				std::cout << " Move up ";
				environment.moveUp();
			}  else if (registry.getTermStringByID(parms[1]) == "left") {
				std::cout << " Move left ";
				environment.moveLeft();
			} else {
				std::cout << "unknown move!\n";
			}
		}
		else if(registry.getTermStringByID(parms[0]) == "sense") {
			std::cout << " Sensing Around " ;
			environment.senseObstacle();
		}	
	}

}

std::vector<PluginAtomPtr> RobotActionPlugin::createAtoms(
		ProgramCtx& ctx) const {
	std::vector < PluginAtomPtr > ret;
	ret.push_back(
			PluginAtomPtr(new RobotLocationExternalAtom, PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new ObstacleLocationExternalAtom, PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new VisitedExternalAtom, PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new ReachedExternalAtom, PluginPtrDeleter<PluginAtom>()));
	return ret;
}

std::vector<PluginActionBasePtr> RobotActionPlugin::createActions(
		ProgramCtx& ctx) const {
	std::vector < PluginActionBasePtr > ret;
	ret.push_back(
			PluginActionBasePtr(new RobotAction,
					PluginPtrDeleter<PluginActionBase>()));
	return ret;
}

//
// now instantiate the plugin
//
RobotActionPlugin theRobotActionPlugin;

DLVHEX_NAMESPACE_END

//
// let it be loaded by dlvhex!
//
IMPLEMENT_PLUGINABIVERSIONFUNCTION

// return plain C type s.t. all compilers and linkers will like this code
extern "C" void * PLUGINIMPORTFUNCTION() {
return reinterpret_cast<void*>(& DLVHEX_NAMESPACE theRobotActionPlugin);
}
