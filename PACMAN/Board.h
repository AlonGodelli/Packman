#pragma once
#include "Position.h"
//#include "Game.h"
#include "misc.h"
class Board
{
private:
	static const int height = 25;
	static const int width = 80;

	char _board[height][width];

public:
	Board(const char board[25][80]);
	void print(int color) const;
	const char& getBoardChar(Position& pos) const;
	void setBoardChar(Position& pos, const char c);
	const int checkWallType(int x, int y) const;

};