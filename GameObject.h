#pragma once
#include "Position.h"
#include "misc.h"
#include "Board.h"


class Board;

class GameObject
{
protected:
	Position _pos;
	char _direction = 1;
public:
	void setPosition(const Position& pos);
	void Move(const Board& board, Position& currPos, Position& newPos, const char boardPosition, const bool isDesigned);
	Position& getPosition();
	void setDirection(const int direction);
	const int& getDirection() const;
	virtual void print(int color) = 0;
	virtual ~GameObject();
};

