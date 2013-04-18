/**
 * @file SudokuPlugin.cpp
 * @author Stefano Germano
 *
 * @brief ...
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */
#include "SudokuPlugin.h"

#include <fstream>

//#include <cmath>
//using namespace std;

DLVHEX_NAMESPACE_BEGIN

SudokuPlugin::Environment::Environment() {

	name = "EnvironmentOfSudokuPlugin";

	firstExecution = true;

	numbers = 9;
	subNumbers = 3;

	createGrids();

	changed = true;

}

SudokuPlugin::Environment::~Environment() {
	destroyGrids();
}

void SudokuPlugin::Environment::createGrids() {

	grid = new unsigned int *[numbers];
	gridNotCandidates = new bool **[numbers];

	for (unsigned int i = 0; i < numbers; i++) {
		grid[i] = new unsigned int[numbers];

		gridNotCandidates[i] = new bool *[numbers];
	}

	for (unsigned int i = 0; i < numbers; i++)
		for (unsigned int j = 0; j < numbers; j++) {
			grid[i][j] = 0;

			gridNotCandidates[i][j] = new bool[numbers];

			for (unsigned int k = 0; k < numbers; k++)
				gridNotCandidates[i][j][k] = false;
		}

}

void SudokuPlugin::Environment::destroyGrids() {

	for (unsigned int i = 0; i < numbers; i++)
		delete[] grid[i];

	delete[] grid;

	for (unsigned int i = 0; i < numbers; i++)
		for (unsigned int j = 0; j < numbers; j++)
			delete[] gridNotCandidates[i][j];

	for (unsigned int i = 0; i < numbers; i++)
		delete[] gridNotCandidates[i];

	delete[] gridNotCandidates;

}

void SudokuPlugin::Environment::setDimension(unsigned int n) {

	if (n < 4)
		throw PluginError("Cannot set a dimension under 4");

	double subN = std::sqrt(n);

	if (subN - std::floor(subN) != 0)
		throw PluginError("Cannot set a dimension that isn't the square of an integer");

	if (n == numbers) {
		DBGLOG(PLUGIN, "The new dimension is the same as before");
		return;
	}

	DBGLOG(PLUGIN, "New dimension " << n);

	destroyGrids();

	numbers = n;
	subNumbers = std::floor(subN);

	createGrids();

}

void SudokuPlugin::Environment::insertNumber(unsigned int row,
		unsigned int column, unsigned int number) {

	if (row >= numbers || column >= numbers)
		throw PluginError(
				"Wrong input argument type (row or column in insertNumber)");

	if (number == 0 || number > numbers)
		throw PluginError("Wrong input argument type (number in insertNumber)");

	grid[row][column] = number;
	DBGLOG(PLUGIN, "Inserted " << number << " in [" << row << ";" << column << "]");

	changed = true;

}

unsigned int SudokuPlugin::Environment::getNumber(unsigned int row,
		unsigned int column) const {

	if (row >= numbers || column >= numbers)
		throw PluginError("Wrong input argument type (in getNumber)");

	return grid[row][column];

}

void SudokuPlugin::Environment::print(std::ostream& output) const {

	output << "  ";
	for (unsigned int j = 0; j < numbers; j++) {
		output << "--- ";
		if ((j + 1) % subNumbers == 0)
			output << " ";
	}
	output << std::endl;

	output << "  ";
	for (unsigned int j = 0; j < numbers; j++) {
		output << "--- ";
		if ((j + 1) % subNumbers == 0)
			output << " ";
	}
	output << std::endl;

	for (unsigned int i = 0; i < numbers; i++) {
		output << "||";

		for (unsigned int j = 0; j < numbers; j++) {
			output << " ";

			if (grid[i][j] == 0)
				output << " ";
			else
				output << grid[i][j];

			if(grid[i][j] < 10)
				output << " ";

			output << "|";

			if ((j + 1) % subNumbers == 0)
				output << "|";
		}

		output << std::endl;

		output << "  ";
		for (unsigned int j = 0; j < numbers; j++) {
			output << "--- ";
			if ((j + 1) % subNumbers == 0)
				output << " ";
		}
		output << std::endl;

		if ((i + 1) % subNumbers == 0) {

			output << "  ";
			for (unsigned int j = 0; j < numbers; j++) {
				output << "--- ";
				if ((j + 1) % subNumbers == 0)
					output << " ";
			}
			output << std::endl;
		}

	}

}

void SudokuPlugin::Environment::writeToFile(std::string fileName) const {

	std::ofstream output;
	output.open(fileName.c_str(), std::ios::app);

	if (!output.is_open())
		throw PluginError("Could not open the file");

	print(output);

	output << "\n\n\n";

	output.close();

}

bool SudokuPlugin::Environment::isTheFirstExecution() const {
	return firstExecution;
}

void SudokuPlugin::Environment::finishedFirstExecution() {
	DBGLOG(PLUGIN, "Finished First Execution");
	firstExecution = false;
}

bool SudokuPlugin::Environment::isCompleted() const {

	if (!changed) {
		std::cout << "There has been no addition in the last iteration"
				<< std::endl;
		return true;
	}

	for (unsigned int i = 0; i < numbers; i++)
		for (unsigned int j = 0; j < numbers; j++)
			if (grid[i][j] == 0)
				return false;

	std::cout << "The sudoku has been completed ";
	if(isCorrect())
		std::cout << "and it's correct!" << std::endl;
	else
		std::cout << "and it isn't correct!" << std::endl;

	return true;

}

bool SudokuPlugin::Environment::isCorrect() const {

	bool numbers_controlled[numbers];

	// numbers
	for (unsigned int i = 0; i < numbers; i++) {

		for (unsigned int j = 0; j < numbers; j++)
			numbers_controlled[j] = false;

		for (unsigned int j = 0; j < numbers; j++)
			if(numbers_controlled[grid[i][j] - 1])
				return false;
			else
				numbers_controlled[grid[i][j] - 1] = true;

	}

	// numbers
	for (unsigned int i = 0; i < numbers; i++) {

		for (unsigned int j = 0; j < numbers; j++)
			numbers_controlled[j] = false;

		for (unsigned int j = 0; j < numbers; j++)
			if(numbers_controlled[grid[j][i] - 1])
				return false;
			else
				numbers_controlled[grid[j][i] - 1] = true;

	}

	//sub-grids subNumbers x subNumbers
	for (unsigned int i = 0; i < numbers; i+=subNumbers) {

		for (unsigned int j = 0; j < numbers; j++)
			numbers_controlled[j] = false;

		for (unsigned int j = 0; j < numbers / subNumbers; j++)
			if(numbers_controlled[grid[i][j] - 1])
				return false;
			else
				numbers_controlled[grid[i][j] - 1] = true;

		for (unsigned int j = 0; j < numbers; j++)
			numbers_controlled[j] = false;

		for (unsigned int j = numbers / subNumbers; j < numbers * 2 / subNumbers; j++)
			if(numbers_controlled[grid[i][j] - 1])
				return false;
			else
				numbers_controlled[grid[i][j] - 1] = true;

		for (unsigned int j = 0; j < numbers; j++)
			numbers_controlled[j] = false;

		for (unsigned int j = numbers * 2 / subNumbers; j < numbers; j++)
			if(numbers_controlled[grid[i][j] - 1])
				return false;
			else
				numbers_controlled[grid[i][j] - 1] = true;

	}

	return true;

}

const list<unsigned int> SudokuPlugin::Environment::getNumbersNotCandidates(
		unsigned int row, unsigned int column) const {

	if (row >= numbers || column >= numbers)
		throw PluginError("Wrong input argument type (in getNumber)");

	list<unsigned int> numbersNotCandidates;

	for (unsigned int k = 0; k < numbers; k++)
		if (gridNotCandidates[row][column][k])
			numbersNotCandidates.push_back(k + 1);

	return numbersNotCandidates;

}

void SudokuPlugin::Environment::insertNumberNotCandidate(unsigned int row,
		unsigned int column, unsigned int number) {

	if (row >= numbers || column >= numbers)
		throw PluginError(
				"Wrong input argument type (row or column in insertNumberNotCandidate)");

	if (number == 0 || number > numbers)
		throw PluginError(
				"Wrong input argument type (number in insertNumberNotCandidate)");

	gridNotCandidates[row][column][number - 1] = true;
	DBGLOG(PLUGIN, "Inserted not candidate " << number << " in [" << row << ";"
			<< column << "]");

	unsigned int number_candidate = 0;
	unsigned int k = 0;
	for (; k < numbers; k++)
		if (!gridNotCandidates[row][column][k])
			if (number_candidate != 0)
				break;
			else
				number_candidate = k + 1;

	if (k == numbers)
		if (number_candidate == 0)
			throw PluginError("There isn't remained any candidate number");
		else {
			DBGLOG(PLUGIN, "There is only one candidate: " << number
					<< ", so was inserted in [" << row << ";" << column << "]");
			grid[row][column] = number_candidate;
		}

	changed = true;

}

void SudokuPlugin::Environment::resetChanged() {
	changed = false;
}

void SudokuPlugin::Environment::printWithThePossibilities(
		std::ostream& output) const {

	// Can be printed also for Sudoku numbersxnumbers
	if(numbers != 9)
		return;

	output << "  ";
	for (unsigned int j = 0; j < numbers; j++) {
		output << "--------- ";
		if ((j + 1) % subNumbers == 0)
			output << " ";
	}
	output << std::endl;

	output << "  ";
	for (unsigned int j = 0; j < numbers; j++) {
		output << "--------- ";
		if ((j + 1) % subNumbers == 0)
			output << " ";
	}
	output << std::endl;

	for (unsigned int i = 0; i < numbers; i++) {

		for (unsigned int k = 0; k < numbers; k += subNumbers) {

			output << "||";

			for (unsigned int j = 0; j < numbers; j++) {

				output << " ";

				if (grid[i][j] == 0) {
					if (gridNotCandidates[i][j][k])
						output << " ";
					else
						output << k + 1;
					output << "  ";
					if (gridNotCandidates[i][j][k + 1])
						output << " ";
					else
						output << k + 2;
					output << "  ";
					if (gridNotCandidates[i][j][k + 2])
						output << " ";
					else
						output << k + subNumbers;
					output << " ";
				} else {
					if (k == subNumbers)
						output << "   " << grid[i][j] << "    ";
					else
						output << "        ";
				}

				output << "|";

				if ((j + 1) % subNumbers == 0)
					output << "|";
			}

			output << std::endl;

		}

		output << "  ";
		for (unsigned int j = 0; j < numbers; j++) {
			output << "--------- ";
			if ((j + 1) % subNumbers == 0)
				output << " ";
		}
		output << std::endl;

		if ((i + 1) % subNumbers == 0) {

			output << "  ";
			for (unsigned int j = 0; j < numbers; j++) {
				output << "--------- ";
				if ((j + 1) % subNumbers == 0)
					output << " ";
			}
			output << std::endl;
		}

	}

}

SudokuPlugin::SudokuAtomGetNumber::SudokuAtomGetNumber() :
		PluginActionAtom("getNumber") {
	addInputConstant();
	addInputConstant();
	setOutputArity(1);
}

void SudokuPlugin::SudokuAtomGetNumber::retrieve(const Environment& environment,
		const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 2)
		throw PluginError("Wrong input argument type (arity in retrieve)");

	ID id1 = query.input[0];
	ID id2 = query.input[1];

	if (!id1.isIntegerTerm() || !id2.isIntegerTerm())
		throw PluginError(
				"Wrong input argument type (aren't IntegerTerm in retrieve)");

	std::stringstream concatstream;

	try {

		concatstream << environment.getNumber(id1.address, id2.address);
		
		Tuple out;
		Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					 std::string(concatstream.str()));
		out.push_back(registry.storeTerm(term));
		answer.get().push_back(out);
		
	} catch(PluginError e) {
		; // do nothing
	}
	


}

SudokuPlugin::SudokuAtomFirstExecution::SudokuAtomFirstExecution() :
		PluginActionAtom("firstExecutionOfSudoku") {
	setOutputArity(0);
}

void SudokuPlugin::SudokuAtomFirstExecution::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 0)
		throw PluginError("Wrong input argument type");

	Tuple out;

	if (environment.isTheFirstExecution())
		answer.get().push_back(out);

}

SudokuPlugin::SudokuAtomSudokuIsCompleted::SudokuAtomSudokuIsCompleted() :
		PluginActionAtom("sudokuIsCompleted") {
	setOutputArity(0);
}

void SudokuPlugin::SudokuAtomSudokuIsCompleted::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 0)
		throw PluginError("Wrong input argument type");

	Tuple out;

	if (environment.isCompleted())
		answer.get().push_back(out);

}

SudokuPlugin::SudokuAtomGetNumbersNotCandidates::SudokuAtomGetNumbersNotCandidates() :
		PluginActionAtom("getNumbersNotCandidates") {
	addInputConstant();
	addInputConstant();
	setOutputArity(1);
}

void SudokuPlugin::SudokuAtomGetNumbersNotCandidates::retrieve(
		const Environment& environment, const Query& query, Answer& answer) {

	Registry &registry = *getRegistry();

	int arity = query.input.size();

	if (arity != 2)
		throw PluginError("Wrong input argument type (arity in retrieve)");

	ID id1 = query.input[0];
	ID id2 = query.input[1];

	if (!id1.isIntegerTerm() || !id2.isIntegerTerm())
		throw PluginError(
				"Wrong input argument type (aren't IntegerTerm in retrieve)");

	try {
		
		const list<unsigned int> numbers = environment.getNumbersNotCandidates(
				id1.address, id2.address);

		if (numbers.empty())
			return;

		for (list<unsigned int>::const_iterator it = numbers.begin();
				it != numbers.end(); it++) {

			Tuple out;

			std::stringstream concatstream;
			concatstream << *it;

			Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT,
					std::string(concatstream.str()));
			out.push_back(registry.storeTerm(term));

			answer.get().push_back(out);

		}
	
	} catch(PluginError e) {
		; // do nothing
	}

}

SudokuPlugin::SudokuAction::SudokuAction() :
		PluginAction("sudoku") {
}

void SudokuPlugin::SudokuAction::execute(Environment& environment,
		RegistryPtr pregistry, const Tuple& parms,
		const InterpretationConstPtr interpretationPtr) {
	Registry& registry = *pregistry;

	if (registry.getTermStringByID(parms[0]) == "insertNumber")
		environment.insertNumber(parms[1].address, parms[2].address,
				parms[3].address);
	else if (registry.getTermStringByID(parms[0]) == "print") {
		int c = system("clear");
		environment.print(std::cout);
	} else if (registry.getTermStringByID(parms[0]) == "writeToFile") {
		std::string fileName = registry.getTermStringByID(parms[1]);
		if (fileName[0] != '\"' || fileName[fileName.size() - 1] != '\"')
			throw PluginError(
					"The first parameter of the atom #writeToFile should be a quoted string!");
		fileName = fileName.substr(1, fileName.size() - 2);
		environment.writeToFile(fileName);
	} else if (registry.getTermStringByID(parms[0]) == "finishedFirstExecution")
		environment.finishedFirstExecution();
	else if (registry.getTermStringByID(parms[0]) == "insertNumberNotCandidate")
		environment.insertNumberNotCandidate(parms[1].address, parms[2].address,
				parms[3].address);
	else if (registry.getTermStringByID(parms[0]) == "resetChanged")
		environment.resetChanged();
	else if (registry.getTermStringByID(parms[0])
			== "printWithThePossibilities") {
		int c = system("clear");
		environment.printWithThePossibilities(std::cout);
	} else if (registry.getTermStringByID(parms[0]) == "setDimension")
		environment.setDimension(parms[1].address);

}

std::vector<PluginAtomPtr> SudokuPlugin::createAtoms(ProgramCtx& ctx) const {
	std::vector < PluginAtomPtr > ret;
	ret.push_back(
			PluginAtomPtr(new SudokuAtomGetNumber,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SudokuAtomFirstExecution,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SudokuAtomSudokuIsCompleted,
					PluginPtrDeleter<PluginAtom>()));
	ret.push_back(
			PluginAtomPtr(new SudokuAtomGetNumbersNotCandidates,
					PluginPtrDeleter<PluginAtom>()));
	return ret;
}

std::vector<PluginActionBasePtr> SudokuPlugin::createActions(
		ProgramCtx& ctx) const {
	std::vector < PluginActionBasePtr > ret;
	ret.push_back(
			PluginActionBasePtr(new SudokuAction,
					PluginPtrDeleter<PluginActionBase>()));
	return ret;
}

//
// now instantiate the plugin
//
SudokuPlugin theSudokuPlugin;

DLVHEX_NAMESPACE_END

//
// let it be loaded by dlvhex!
//
IMPLEMENT_PLUGINABIVERSIONFUNCTION

// return plain C type s.t. all compilers and linkers will like this code
extern "C" void * PLUGINIMPORTFUNCTION() {
return reinterpret_cast<void*>(& DLVHEX_NAMESPACE theSudokuPlugin);
}
