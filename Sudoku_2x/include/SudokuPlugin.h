/**
 * @file SudokuPlugin.h
 * @author Stefano Germano
 *
 * @brief ...
 */

#ifndef SUDOKU_PLUGIN_H_
#define SUDOKU_PLUGIN_H_

#include "acthex/ActionPluginInterface.h"

#include<list>
using namespace std;

DLVHEX_NAMESPACE_BEGIN

class SudokuPlugin: public ActionPluginInterface {

public:

	class Environment: public PluginEnvironment {
	public:
		Environment();
		virtual ~Environment();
		void insertNumber(unsigned int, unsigned int, unsigned int);
		unsigned int getNumber(unsigned int, unsigned int) const;
		void print(std::ostream&) const;
		void writeToFile(std::string) const;
		static const unsigned int ROWS = 9;
		static const unsigned int COLUMNS = 9;
		static const unsigned int NUMBERS = 9;
		bool isTheFirstExecution() const;
		void finishedFirstExecution();
		bool isCompleted() const;
		const list<unsigned int> getNumbersNotCandidates(unsigned int,
				unsigned int) const;
		void insertNumberNotCandidate(unsigned int, unsigned int, unsigned int);
		void resetChanged();
		void printWithThePossibilities(std::ostream&) const;
	private:
		std::string name;
		unsigned int ** grid;
		bool firstExecution;
		bool *** gridNotCandidates;
		bool changed;
	};

	SudokuPlugin() :
			ActionPluginInterface() {
		setNameVersion(PACKAGE_TARNAME, SUDOKUPLUGIN_VERSION_MAJOR,
				SUDOKUPLUGIN_VERSION_MINOR, SUDOKUPLUGIN_VERSION_MICRO);
	}

	class SudokuAtomGetNumber: public PluginActionAtom<SudokuPlugin> {
	public:
		SudokuAtomGetNumber();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SudokuAtomFirstExecution: public PluginActionAtom<SudokuPlugin> {
	public:
		SudokuAtomFirstExecution();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SudokuAtomSudokuIsCompleted: public PluginActionAtom<SudokuPlugin> {
	public:
		SudokuAtomSudokuIsCompleted();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SudokuAtomGetNumbersNotCandidates: public PluginActionAtom<
			SudokuPlugin> {
	public:
		SudokuAtomGetNumbersNotCandidates();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	class SudokuAction: public PluginAction<SudokuPlugin> {
	public:
		SudokuAction();
	private:
		virtual void execute(Environment&, RegistryPtr, const Tuple&,
				const InterpretationConstPtr);
	};

	virtual std::vector<PluginAtomPtr> createAtoms(ProgramCtx& ctx) const;

	virtual std::vector<PluginActionBasePtr> createActions(
			ProgramCtx& ctx) const;

protected:

	ActionPluginInterfacePtr create(ProgramCtx& ctx) {
		DBGLOG(PLUGIN, "create in SudokuPlugin");
#warning a trick, maybe we should find a way remove it
		ctx.getPluginEnvironment<SudokuPlugin>();
		DBGLOG(PLUGIN, "getPluginEnvironment done");
		return boost::shared_ptr < SudokuPlugin > (new SudokuPlugin());
	}

};

DLVHEX_NAMESPACE_END

#endif /* SUDOKU_PLUGIN_H_ */
