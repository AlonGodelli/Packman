#pragma once
#include "Position.h"

Position::Position()
{
	_x = 35;
	_y = 13;
}

Position::Position(const int x, const int y)
{
	_x = x;
	_y = y;
}

void Position::setPosition(const int x, const int y)
{
	_x = x;
	_y = y;
}

const int Position::getPositionY() const
{
	return _y;
}

const int Position::getPositionX() const
{
	return _x;
}
