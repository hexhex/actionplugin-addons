/**
 * @file PawnPlaced.h
 * @author Stefano Germano
 *
 * @brief 
 */

#ifndef PAWN_PLACED_H_
#define PAWN_PLACED_H_

class PawnPlaced {

public:
	PawnPlaced(unsigned short, unsigned short, char);
	unsigned short getRow() const;
	unsigned short getColumn() const;
	char getColor() const;

private:
	unsigned short row;
	unsigned short column;
	char color;

};

#endif /* PAWN_PLACED_H_ */
