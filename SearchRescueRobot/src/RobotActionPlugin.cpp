/**
 * @file RobotActionPlugin.cpp
 * @author Zeynep G. Saribatur 2015
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
		failureReason="obstacle";
		return;
	}
	currentX += 1;
	//std::cout << "Robot is at " << currentX << ", " << currentY;
}

void RobotActionPlugin::Environment::moveRight() {
	//updateMap(currentX,currentY,1);
	if(temp_map[currentX][currentY+1]==2){
		std::cout << " Obstacle in the way! " ;
		failureReason="obstacle";
		return;
	}
	currentY += 1;
	//std::cout << "Robot is at " << currentX << ", " << currentY;
}
void RobotActionPlugin::Environment::moveUp() {
	//updateMap(currentX,currentY,1);
	if(temp_map[currentX-1][currentY]==2){
		std::cout << " Obstacle in the way! " ;
		failureReason="obstacle";
		return;
	}
	currentX -= 1;
	//std::cout << "Robot is at " << currentX << ", " << currentY;
}

void RobotActionPlugin::Environment::moveLeft() {
	//updateMap(currentX,currentY,1);
	if(temp_map[currentX][currentY-1]==2){
		std::cout << " Obstacle in the way! " ;
		failureReason="obstacle";
		return;
	}
	currentY -= 1;
	//std::cout << "Robot is at " << currentX << ", " << currentY;
}

void RobotActionPlugin::Environment::moveTo(int a,int b) {
	currentX=a;	
	currentY=b;
}

void RobotActionPlugin::Environment::updateMap(int a, int b, int c){
	temp_map[a][b]=c;
	if(a==goalX and b==goalY and c==1)
		changeGoal();
}

void RobotActionPlugin::Environment::changeGoal(){
	if(goalX==3 and goalY==3)
		goalX=0;
	else if(goalX==0 and goalY==3){
		goalY=0;
		goalX=3;
	}
	else if(goalX==3 and goalY==0){
		goalY=0;
		goalX=0;		
	}
	std::cout << " Goal is now: "<< goalX <<","<< goalY<<" " ;		
	
}

void RobotActionPlugin::Environment::updateMainMap(int a, int b, int c){
	map[a][b]=c;
	lostPerson--;
}

void RobotActionPlugin::Environment::resetFailureReason(){
	failureReason="none";
}

int RobotActionPlugin::Environment::sense(int a, int b) const{
	return map[a][b];
}

int RobotActionPlugin::Environment::senseKnowledge(int a, int b) const{
	return temp_map[a][b];
}

std::string RobotActionPlugin::Environment::getFailureReason() const{
	return failureReason;
}

void RobotActionPlugin::Environment::senseSurroundingCells(){
	int tempposx=currentX;
	int tempposy=currentY;
	int sensed;
	updateMap(currentX,currentY,1);

	while(tempposx<maxrow){
		tempposx++;
		if(senseKnowledge(tempposx,tempposy)!=-1){
			if(senseKnowledge(tempposx,tempposy)==2)
				break;
			continue;
		}
		std::cout << " Sensing-down " ;
		sensed=sense(tempposx,tempposy);
		if(sensed==1){		
			updateMap(tempposx,tempposy,2);
			//std::cout << " Obstacle - down " ;
			std::cout << " Obstacle at " << tempposx << ", " << tempposy << " ";
			break; //can't sense behind the obstacle
		}
		else if(sensed==2){		
			updateMap(tempposx,tempposy,3);
			//std::cout << " Person - down " ;
			std::cout << " Person at " << tempposx << ", " << tempposy << " ";
			failureReason="person";
			break; //can't sense behind the person
		}
		else //sensed==0
			updateMap(tempposx,tempposy,0);
	}

	tempposx=currentX;
	tempposy=currentY;

	while(tempposx>0){
		tempposx--;
		if(senseKnowledge(tempposx,tempposy)!=-1){
			if(senseKnowledge(tempposx,tempposy)==2)
				break;
			continue;
		}
		std::cout << " Sensing-up " ;
		sensed=sense(tempposx,tempposy);
		if(sensed==1){		
			updateMap(tempposx,tempposy,2);
			//std::cout << " Obstacle - up " ;
			std::cout << " Obstacle at " << tempposx << ", " << tempposy << " ";
			break; //can't sense behind the obstacle
		}
		else if(sensed==2){		
			updateMap(tempposx,tempposy,3);
			//std::cout << " Person - up " ;
			std::cout << " Person at " << tempposx << ", " << tempposy << " ";
			failureReason="person";
			break; //can't sense behind the person
		}
		else //sensed==0
			updateMap(tempposx,tempposy,0);
	}

	tempposx=currentX;
	tempposy=currentY;

	while(tempposy<maxcol){
		tempposy++;
		if(senseKnowledge(tempposx,tempposy)!=-1){
			if(senseKnowledge(tempposx,tempposy)==2)
				break;
			continue;
		}
		std::cout << " Sensing-right " ;
		sensed=sense(tempposx,tempposy);
		if(sensed==1){		
			updateMap(tempposx,tempposy,2);
			//std::cout << " Obstacle - right " ;
			std::cout << " Obstacle at " << tempposx << ", " << tempposy << " ";
			break; //can't sense behind the obstacle
		}
		else if(sensed==2){		
			updateMap(tempposx,tempposy,3);
			//std::cout << " Person - right " ;
			std::cout << " Person at " << tempposx << ", " << tempposy << " ";
			failureReason="person";
			break; //can't sense behind the person
		}
		else //sensed==0
			updateMap(tempposx,tempposy,0);
	}

	tempposx=currentX;
	tempposy=currentY;

	while(tempposy>0){
		tempposy--;
		if(senseKnowledge(tempposx,tempposy)!=-1){
			if(senseKnowledge(tempposx,tempposy)==2)
				break;
			continue;
		}
		std::cout << " Sensing-left " ;
		sensed=sense(tempposx,tempposy);
		if(sensed==1){		
			updateMap(tempposx,tempposy,2);
			//std::cout << " Obstacle - left " ;
			std::cout << " Obstacle at " << tempposx << ", " << tempposy << " ";
			break; //can't sense behind the obstacle
		}
		else if(sensed==2){		
			updateMap(tempposx,tempposy,3);
			//std::cout << " Person - left " ;
			std::cout << " Person at " << tempposx << ", " << tempposy << " ";
			failureReason="person";
			break; //can't sense behind the person
		}
		else //sensed==0
			updateMap(tempposx,tempposy,0);
	}

	tempposx=currentX;
	tempposy=currentY;

	//Checking diagonally
		
	while(tempposx<maxrow and tempposy<maxcol){
		tempposx++;
		tempposy++;
		if(senseKnowledge(tempposx,tempposy)!=-1){
			if(senseKnowledge(tempposx,tempposy)==2)
				break;
			continue;
		}
		std::cout << " Sensing-downright " ;
		sensed=sense(tempposx,tempposy);
		if(sensed==1){		
			updateMap(tempposx,tempposy,2);
			std::cout << " Obstacle at " << tempposx << ", " << tempposy << " ";
			break; //can't sense behind the obstacle
		}
		else if(sensed==2){		
			updateMap(tempposx,tempposy,3);
			std::cout << " Person at " << tempposx << ", " << tempposy << " ";
			failureReason="person";
			break; //can't sense behind the person
		}
		else //sensed==0
			updateMap(tempposx,tempposy,0);
	}

	tempposx=currentX;
	tempposy=currentY;

	while(tempposx>0 and tempposy<maxcol){
		tempposx--;
		tempposy++;
		if(senseKnowledge(tempposx,tempposy)!=-1){
			if(senseKnowledge(tempposx,tempposy)==2)
				break;
			continue;
		}
		std::cout << " Sensing-upright " ;
		sensed=sense(tempposx,tempposy);
		if(sensed==1){		
			updateMap(tempposx,tempposy,2);
			std::cout << " Obstacle at " << tempposx << ", " << tempposy << " ";
			break; //can't sense behind the obstacle
		}
		else if(sensed==2){		
			updateMap(tempposx,tempposy,3);
			std::cout << " Person at " << tempposx << ", " << tempposy << " ";
			failureReason="person";
			break; //can't sense behind the person
		}
		else //sensed==0
			updateMap(tempposx,tempposy,0);
	}

	tempposx=currentX;
	tempposy=currentY;
	
	while(tempposx>0 and tempposy>0){		
		tempposx--;
		tempposy--;
		if(senseKnowledge(tempposx,tempposy)!=-1){
			if(senseKnowledge(tempposx,tempposy)==2)
				break;
			continue;
		}
		std::cout << " Sensing-upleft " ;
		sensed=sense(tempposx,tempposy);
		if(sensed==1){		
			updateMap(tempposx,tempposy,2);
			std::cout << " Obstacle at " << tempposx << ", " << tempposy << " ";
			break; //can't sense behind the obstacle
		}
		else if(sensed==2){		
			updateMap(tempposx,tempposy,3);
			std::cout << " Person at " << tempposx << ", " << tempposy << " ";
			failureReason="person";
			break; //can't sense behind the person
		}
		else //sensed==0
			updateMap(tempposx,tempposy,0);
	}

	tempposx=currentX;
	tempposy=currentY;
	
	while(tempposx<maxrow and tempposy>0){
		tempposx++;
		tempposy--;
		if(senseKnowledge(tempposx,tempposy)!=-1){
			if(senseKnowledge(tempposx,tempposy)==2)
				break;
			continue;
		}
		std::cout << " Sensing-downleft " ;
		sensed=sense(tempposx,tempposy);
		if(sensed==1){		
			updateMap(tempposx,tempposy,2);
			std::cout << " Obstacle at " << tempposx << ", " << tempposy << " ";
			break; //can't sense behind the obstacle
		}
		else if(sensed==2){		
			updateMap(tempposx,tempposy,3);
			std::cout << " Person at " << tempposx << ", " << tempposy << " ";
			failureReason="person";
			break; //can't sense behind the person
		}
		else //sensed==0
			updateMap(tempposx,tempposy,0);
	}

}

bool RobotActionPlugin::Environment::robotVisited(int a, int b) const{
	if (temp_map[a][b]==1)
		return true;
	return false;
}

bool RobotActionPlugin::Environment::robotSensed(int a, int b) const{
	if (temp_map[a][b]==0 || temp_map[a][b]==1 || temp_map[a][b]==3)
		return true;
	return false;
}

bool RobotActionPlugin::Environment::robotFoundObstacle(int a, int b) const{
	if (temp_map[a][b]==2)
		return true;
	return false;
}

bool RobotActionPlugin::Environment::robotFoundPerson(int a, int b) const{
	if (temp_map[a][b]==3)
		return true;
	return false;
}

unsigned int RobotActionPlugin::Environment::getRobotPositionX() const {
	return currentX;
}

unsigned int RobotActionPlugin::Environment::getRobotPositionY() const {
	return currentY;
}

unsigned int RobotActionPlugin::Environment::getGoalX() const {
	return goalX;
}

unsigned int RobotActionPlugin::Environment::getGoalY() const {
	return goalY;
}


bool RobotActionPlugin::Environment::savedAll() const {
	std::cout << " - checking if saved all - " << std::endl;
	if (lostPerson==0)
		return true;
	return false;

}


RobotActionPlugin::ReachableExternalAtom::ReachableExternalAtom() :
		PluginActionAtom("reachable") {
	//addInputConstant();
	setOutputArity(2);
}
/*RobotActionPlugin::ReachableExternalAtom::ReachableExternalAtom() :
		PluginActionAtom("currentObstacles") {
	//addInputConstant();
	setOutputArity(2);
}*/

void RobotActionPlugin::ReachableExternalAtom::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {
	Registry &registry = *getRegistry();
	
	

	for(int i=0;i<environment.maxrow+1;i++){
		for(int j=0;j<environment.maxcol+1;j++){
			if(environment.robotSensed(i,j)){
				Tuple out;
				std::stringstream getX;
				std::stringstream getY;
				getX << i;
				getY << j;
				std::cout << " Sensed " << getX.str() << ", " << getY.str() << " " <<std::endl;
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
	
	int cx=environment.getRobotPositionX();
	int cy=environment.getRobotPositionY();
	int tempposx=cx;
	int tempposy=cy;
	int sensed;

	if(environment.robotVisited(tempposx,tempposy))
		return;

	std::cout << " Now sensing around at the new cell " <<std::endl;
	
	//current cell is also "reachable"
	Tuple out;
	std::stringstream getX;
	std::stringstream getY;
	getX << tempposx;
	getY << tempposy;
	Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(getX.str()));
	out.push_back(registry.storeTerm(termX));
	Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(getY.str()));
	out.push_back(registry.storeTerm(termY));
	answer.get().push_back(out);

	while(tempposx<environment.maxrow){
		tempposx++;
		sensed=environment.sense(tempposx,tempposy);
		if(sensed==1){		
			break; //can't sense behind the obstacle
		}
		else{
			Tuple out;
			std::stringstream getX;
			std::stringstream getY;
			getX << tempposx;
			getY << tempposy;
			Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getX.str()));
			out.push_back(registry.storeTerm(termX));
			Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getY.str()));
			out.push_back(registry.storeTerm(termY));
			answer.get().push_back(out);
			
			if(sensed==2)
				break; //can't sense behind the person		
		}
	}

	tempposx=cx;
	tempposy=cy;

	while(tempposx>0){
		tempposx--;
		sensed=environment.sense(tempposx,tempposy);
		if(sensed==1){	
			break; //can't sense behind the obstacle
		}
		else{	
			Tuple out;
			std::stringstream getX;
			std::stringstream getY;
			getX << tempposx;
			getY << tempposy;
			Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getX.str()));
			out.push_back(registry.storeTerm(termX));
			Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getY.str()));
			out.push_back(registry.storeTerm(termY));
			answer.get().push_back(out);
			
			if(sensed==2)
				break; //can't sense behind the person		
		}
	}

	tempposx=cx;
	tempposy=cy;

	while(tempposy<environment.maxcol){
		tempposy++;
		sensed=environment.sense(tempposx,tempposy);
		if(sensed==1){		
			
			break; //can't sense behind the obstacle
		}
		else{
			Tuple out;
			std::stringstream getX;
			std::stringstream getY;
			getX << tempposx;
			getY << tempposy;
			Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getX.str()));
			out.push_back(registry.storeTerm(termX));
			Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getY.str()));
			out.push_back(registry.storeTerm(termY));
			answer.get().push_back(out);
			
			if(sensed==2)
				break; //can't sense behind the person		
		}
	}

	tempposx=cx;
	tempposy=cy;

	while(tempposy>0){
		tempposy--;
		sensed=environment.sense(tempposx,tempposy);
		if(sensed==1){	
			break; //can't sense behind the obstacle
		}
		else{	
			Tuple out;
			std::stringstream getX;
			std::stringstream getY;
			getX << tempposx;
			getY << tempposy;
			Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getX.str()));
			out.push_back(registry.storeTerm(termX));
			Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getY.str()));
			out.push_back(registry.storeTerm(termY));
			answer.get().push_back(out);
			
			if(sensed==2)
				break; //can't sense behind the person		
		}
	}

	tempposx=cx;
	tempposy=cy;

	//Checking diagonally
		
	while(tempposx<environment.maxrow and tempposy<environment.maxcol){
		tempposx++;
		tempposy++;
		sensed=environment.sense(tempposx,tempposy);
		if(sensed==1){	
			break; //can't sense behind the obstacle
		}
		else{	
			Tuple out;
			std::stringstream getX;
			std::stringstream getY;
			getX << tempposx;
			getY << tempposy;
			Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getX.str()));
			out.push_back(registry.storeTerm(termX));
			Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getY.str()));
			out.push_back(registry.storeTerm(termY));
			answer.get().push_back(out);
			
			if(sensed==2)
				break; //can't sense behind the person		
		}
	}

	tempposx=cx;
	tempposy=cy;

	while(tempposx>0 and tempposy<environment.maxcol){
		tempposx--;
		tempposy++;
		sensed=environment.sense(tempposx,tempposy);
		if(sensed==1){	
			break; //can't sense behind the obstacle
		}
		else{	
			Tuple out;
			std::stringstream getX;
			std::stringstream getY;
			getX << tempposx;
			getY << tempposy;
			Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getX.str()));
			out.push_back(registry.storeTerm(termX));
			Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getY.str()));
			out.push_back(registry.storeTerm(termY));
			answer.get().push_back(out);
			
			if(sensed==2)
				break; //can't sense behind the person		
		}
	}

	tempposx=cx;
	tempposy=cy;
	
	while(tempposx>0 and tempposy>0){		
		tempposx--;
		tempposy--;
		sensed=environment.sense(tempposx,tempposy);
		if(sensed==1){	
			break; //can't sense behind the obstacle
		}
		else{
			Tuple out;
			std::stringstream getX;
			std::stringstream getY;
			getX << tempposx;
			getY << tempposy;
			Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getX.str()));
			out.push_back(registry.storeTerm(termX));
			Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getY.str()));
			out.push_back(registry.storeTerm(termY));
			answer.get().push_back(out);	
			
			if(sensed==2)
				break; //can't sense behind the person		
		}
	}

	tempposx=cx;
	tempposy=cy;
	
	while(tempposx<environment.maxrow and tempposy>0){
		tempposx++;
		tempposy--;
		sensed=environment.sense(tempposx,tempposy);
		if(sensed==1){		
			break; //can't sense behind the obstacle
		}
		else{
			Tuple out;
			std::stringstream getX;
			std::stringstream getY;
			getX << tempposx;
			getY << tempposy;
			Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getX.str()));
			out.push_back(registry.storeTerm(termX));
			Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(getY.str()));
			out.push_back(registry.storeTerm(termY));
			answer.get().push_back(out);
			if(sensed==2)
				break; //can't sense behind the person		
		}
	}
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

	for(int i=0;i<environment.maxrow+1;i++){
		for(int j=0;j<environment.maxcol+1;j++){
			if(environment.robotVisited(i,j)){
				Tuple out;
				std::stringstream getX;
				std::stringstream getY;
				getX << i;
				getY << j;
				std::cout << " Visited " << getX.str() << ", " << getY.str() << " " <<std::endl;
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
	
	//Tuple out;

	for(int i=0;i<environment.maxrow+1;i++){
		for(int j=0;j<environment.maxcol+1;j++){
			if(environment.robotFoundObstacle(i,j)){
				Tuple out;
				std::stringstream getX;
				std::stringstream getY;
				getX << i;
				getY << j;
				std::cout << " Know obstacle at " << getX.str() << ", " << getY.str() << " " <<std::endl;
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

RobotActionPlugin::PersonLocationExternalAtom::PersonLocationExternalAtom() :
		PluginActionAtom("personLocation") {
	setOutputArity(2);
}


void RobotActionPlugin::PersonLocationExternalAtom::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();
	
	//Tuple out;

	for(int i=0;i<environment.maxrow+1;i++){
		for(int j=0;j<environment.maxcol+1;j++){
			if(environment.robotFoundPerson(i,j)){
				Tuple out;
				std::stringstream getX;
				std::stringstream getY;
				getX << i;
				getY << j;
				std::cout << " Know person at " << getX.str() << ", " << getY.str() << " " <<std::endl;
				Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
						std::string(getX.str()));
				out.push_back(registry.storeTerm(termX));

				Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
						std::string(getY.str()));
				out.push_back(registry.storeTerm(termY));
				answer.get().push_back(out);
				//return;
			}
		}
	}
	
	
}

RobotActionPlugin::SavedExternalAtom::SavedExternalAtom() :
		PluginActionAtom("savedAll") {
	//addInputConstant();
	setOutputArity(0);
}

void RobotActionPlugin::SavedExternalAtom::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {
	
	Tuple out;

	if (environment.savedAll())
		answer.get().push_back(out);
	
}

RobotActionPlugin::GoalExternalAtom::GoalExternalAtom() :
		PluginActionAtom("getGoal") {
	//addInputConstant();
	setOutputArity(2);
}

void RobotActionPlugin::GoalExternalAtom::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {
	
	Registry &registry = *getRegistry();
	
	Tuple out;

	std::stringstream getX;
	std::stringstream getY;

	getX << environment.getGoalX();
	getY << environment.getGoalY();
	std::cout << "Goal is " << getX.str() << ", " << getY.str() <<" ";	
	
	
	Term termX(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(getX.str()));
	out.push_back(registry.storeTerm(termX));

	Term termY(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
			std::string(getY.str()));
	out.push_back(registry.storeTerm(termY));
	answer.get().push_back(out);
	
}


RobotActionPlugin::FailureExternalAtom::FailureExternalAtom() :
		PluginActionAtom("getFailureReason") {
	//addInputConstant();
	setOutputArity(1);
}

void RobotActionPlugin::FailureExternalAtom::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {
	
	Registry &registry = *getRegistry();
	Tuple out;

	std::string fail = environment.getFailureReason();

	std::cout << " FailureReason " << fail << " ";
	Term failure(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, 
			std::string(fail));
	out.push_back(registry.storeTerm(failure));
	
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
		std::cout << " resetFailureReason "<<std::endl ;
		environment.resetFailureReason();
	}
	else{
	
		if(environment.getFailureReason()!="none")
			return;

		if (registry.getTermStringByID(parms[0]) == "move") {

			if (registry.getTermStringByID(parms[1]) == "down") {
				std::cout << " 'Move down at time "<<parms[3].address<<std::endl ;
				environment.moveDown();
			} else if (registry.getTermStringByID(parms[1]) == "right") {
				std::cout << " 'Move right at time "<<parms[3].address<<std::endl ;
				environment.moveRight();
			}  else if (registry.getTermStringByID(parms[1]) == "up") {
				std::cout << " 'Move up at time "<<parms[3].address<<std::endl ;
				environment.moveUp();
			}  else if (registry.getTermStringByID(parms[1]) == "left") {
				std::cout << " 'Move left at time "<<parms[3].address<<std::endl ;
				environment.moveLeft();
			} else {
				std::cout << "unknown move!\n";
			}
		}
		else if(registry.getTermStringByID(parms[0]) == "goto"){
			std::cout << " 'Moving-to "<< parms[1].address <<","<< parms[2].address<<"' at time "<<parms[3].address<<std::endl;
			environment.moveTo(parms[1].address, parms[2].address);
		}
		else if(registry.getTermStringByID(parms[0]) == "sense") {
			std::cout << " 'Sensing-Around "<<environment.getRobotPositionX()<<","<<environment.getRobotPositionY()<<"' at time "<<parms[3].address<<std::endl ;
			environment.senseSurroundingCells();
		}	
		else if(registry.getTermStringByID(parms[0]) == "pick") {
			std::cout << " 'Pick person at time "<<parms[3].address<<std::endl ;
			environment.updateMainMap(environment.getRobotPositionX(),environment.getRobotPositionY(),0);
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
			PluginAtomPtr(new PersonLocationExternalAtom, PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new ReachableExternalAtom, PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new FailureExternalAtom, PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SavedExternalAtom, PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new VisitedExternalAtom, PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new GoalExternalAtom, PluginPtrDeleter<PluginAtom>()));
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
