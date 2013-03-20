/**
 * @file Reversi.h
 * @author Stefano Germano
 *
 * @brief 
 */

#ifndef REVERSI_H_
#define REVERSI_H_

#include "acthex/ActionPluginInterface.h"

#include "PawnPlaced.h"

DLVHEX_NAMESPACE_BEGIN

class Reversi: public ActionPluginInterface {

public:

	Reversi() :
			ActionPluginInterface() {
		setNameVersion(PACKAGE_TARNAME, REVERSI_VERSION_MAJOR,
				REVERSI_VERSION_MINOR, REVERSI_VERSION_MICRO);
	}

	/**
	 * @brief Environment
	 */
	class Environment: public PluginEnvironment {
	public:
		Environment();
		virtual ~Environment();
		void getPawnPlaced(list<PawnPlaced>&, unsigned int) const;
//		char getMyColor(unsigned int) const;
		void makeAMove(unsigned int, unsigned int);
		void setGamenumber(unsigned int);
	private:
		unsigned int gamenumber;
	};

	/**
	 * @brief
	 */
	class PawnPlacedExternalAtom: public PluginActionAtom<Reversi> {
	public:
		PawnPlacedExternalAtom();
	private:
		virtual void retrieve(const Environment& environment,
				const Query& query, Answer& answer);
	};

	/**
	 * @brief
	 */
//	class MyColorExternalAtom: public PluginActionAtom<Reversi> {
//	public:
//		MyColorExternalAtom();
//	private:
//		virtual void retrieve(const Environment& environment,
//				const Query& query, Answer& answer);
//	};

	/**
	 * @brief
	 */
	class ReversiActionAtom: public PluginAction<Reversi> {
	public:
		ReversiActionAtom();
	private:
		virtual void execute(Environment&, RegistryPtr, const Tuple&,
				const InterpretationConstPtr);
	};

	virtual std::vector<PluginAtomPtr> createAtoms(ProgramCtx& ctx) const;

	virtual std::vector<PluginActionBasePtr> createActions(
			ProgramCtx& ctx) const;

protected:

	ActionPluginInterfacePtr create(ProgramCtx& ctx) {
		ctx.getPluginEnvironment<Reversi>();
		return boost::shared_ptr <Reversi> (new Reversi());
	}

};

DLVHEX_NAMESPACE_END

#endif /* REVERSI_H_ */
