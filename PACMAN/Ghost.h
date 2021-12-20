#pragma once
#include "Position.h"
#include "Game.h"
#include "GameObject.h"
class Board;



class Ghost : public GameObject
{
private:
	int _moveCount = 0;
public:
	Ghost();
	Ghost(const Position pos);
	void Move(Ghost& ghost, Board& board, const Position& pacmanPos, const bool isDesigned, const int difficulty);
	void setMoveCount(const int moveCount);
	const int getMoveCount() const;
	void print(const int color);
	const char smartGhost(Position& pacmanPos, Position& newPos, Board& board);
};



