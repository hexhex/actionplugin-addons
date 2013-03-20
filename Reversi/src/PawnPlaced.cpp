/**
 * @file PawnPlaced.cpp
 * @author Stefano Germano
 *
 * @brief 
 */

#include "PawnPlaced.h"

PawnPlaced::PawnPlaced(unsigned short row, unsigned short column, char color) : row(row), column(column), color(color) {}

unsigned short PawnPlaced::getRow() const {
	return row;
}

unsigned short PawnPlaced::getColumn() const {
	return column;
}

char PawnPlaced::getColor() const {
	return color;
}
