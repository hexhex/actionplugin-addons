/**
 * @file Reversi.cpp
 * @author Stefano Germano
 *
 * @brief 
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "Reversi.h"

#include <cstdlib>

#include <cstdio>

DLVHEX_NAMESPACE_BEGIN

Reversi::Environment::Environment() {
	// Initialize here your Environment
}

Reversi::Environment::~Environment() {
	// Frees the memory allocated dynamically
}

void Reversi::Environment::getPawnPlaced(
		list<PawnPlaced>& listPawnPlaced, unsigned int gamenumber) const {



}

char Reversi::Environment::getMyColor(unsigned int gamenumber) const {

	FILE *in;
	char buff[2];

	if(!(in = popen("./pl/htmlReversiMyColorDecripter.pl" + gamenumber, "r")))
		return 'e';

	char color;

	while(fgets(buff, sizeof(buff), in)!=NULL)
//		color << buff[0];
		std::cout << buff << std::endl;

	pclose(in);

//	int color = system("./pl/htmlReversiMyColorDecripter.pl");

	std::cout << "#" << color << "#" << std::endl;

}

void Reversi::Environment::makeAMove(unsigned int row, unsigned int column) {

}

Reversi::PawnPlacedExternalAtom::PawnPlacedExternalAtom() :
		PluginActionAtom("pawnPlaced") {
	addInputConstant();
	setOutputArity(3);
}

void Reversi::PawnPlacedExternalAtom::retrieve(const Environment& environment,
		const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	if (query.input.size() != 1)
		throw PluginError("Wrong input argument type (arity in retrieve)");

	ID idGameNumber = query.input[0];

	if (!idGameNumber.isIntegerTerm())
		throw PluginError("Wrong input argument type (isn't IntegerTerm in retrieve)");

	int gameNumber = idGameNumber.address;

	if(gameNumber < 0)
		throw PluginError("Wrong input argument type (the input term isn't a positive integer)");

	list<PawnPlaced> listPawnPlaced;
	environment.getPawnPlaced(listPawnPlaced, gameNumber);

	for (list<PawnPlaced>::iterator it = listPawnPlaced.begin();
			it != listPawnPlaced.end(); it++) {

		std::stringstream row;
		row << it->getRow();

		std::stringstream column;
		column << it->getColumn();

		std::string color = "" + it->getColor();

		Tuple out;

		Term termRow(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
				std::string(row.str()));
		out.push_back(registry.storeTerm(termRow));

		Term termColumn(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
				std::string(column.str()));
		out.push_back(registry.storeTerm(termColumn));

		Term termColor(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, color);
		out.push_back(registry.storeTerm(termColor));

		answer.get().push_back(out);

	}

}

Reversi::MyColorExternalAtom::MyColorExternalAtom() :
		PluginActionAtom("myColor") {
	addInputConstant();
	setOutputArity(1);
}

void Reversi::MyColorExternalAtom::retrieve(const Environment& environment,
		const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	if (query.input.size() != 1)
		throw PluginError("Wrong input argument type (arity in retrieve)");

	ID idGameNumber = query.input[0];

	if (!idGameNumber.isIntegerTerm())
		throw PluginError("Wrong input argument type (isn't IntegerTerm in retrieve)");

	int gameNumber = idGameNumber.address;

	if(gameNumber < 0)
		throw PluginError("Wrong input argument type (the input term isn't a positive integer)");

	std::string color = "" + environment.getMyColor(gameNumber);

	Tuple out;

	Term termColor(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, color);
	out.push_back(registry.storeTerm(termColor));

	answer.get().push_back(out);

}

Reversi::ReversiActionAtom::ReversiActionAtom() :
		PluginAction("reversi") {
}

void Reversi::ReversiActionAtom::execute(Environment& environment,
		RegistryPtr pregistry, const Tuple& parms,
		const InterpretationConstPtr interpretationPtr) {
	Registry& registry = *pregistry;

	if (registry.getTermStringByID(parms[0]) == "makeAMove")
		environment.makeAMove(parms[1].address, parms[2].address);

}

std::vector<PluginAtomPtr> Reversi::createAtoms(ProgramCtx& ctx) const {

	std::vector < PluginAtomPtr > ret;
	ret.push_back(
			PluginAtomPtr(new PawnPlacedExternalAtom,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new MyColorExternalAtom,
					PluginPtrDeleter<PluginAtom>()));
	return ret;

}

std::vector<PluginActionBasePtr> Reversi::createActions(ProgramCtx& ctx) const {

	std::vector < PluginActionBasePtr > ret;
	ret.push_back(
			PluginActionBasePtr(new ReversiActionAtom,
					PluginPtrDeleter<PluginActionBase>()));
	return ret;

}

//
// now instantiate the plugin
//
Reversi theReversi;

DLVHEX_NAMESPACE_END

//
// let it be loaded by dlvhex!
//
IMPLEMENT_PLUGINABIVERSIONFUNCTION

// return plain C type s.t. all compilers and linkers will like this code
extern "C" void * PLUGINIMPORTFUNCTION() {
return reinterpret_cast<void*>(& DLVHEX_NAMESPACE theReversi);
}
