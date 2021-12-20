#pragma once
#include "Fruit.h"
#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include "Ghost.h"
#include "Game.h"
#include "Board.h"
#include "misc.h"


using namespace std;

Board::Board(const char board[25][80])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			_board[i][j] = board[i][j];
		}
	}
}

void Board::print(int color) const
{
	changeColor(color);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (_board[i][j] == '#' && color != 15)
			{
				const char wallType = checkWallType(i, j);
				cout << wallType;
			}
			else if (_board[i][j] == '%')
				cout << ' ';
			else
				cout << _board[i][j];
		}
		cout << endl;
	}
}

const char& Board::getBoardChar(Position& pos) const
{
	int y = pos.getPositionY();
	int x = pos.getPositionX();
	return _board[y][x];
}

void Board::setBoardChar(Position& pos, const char c)
{
	int x = pos.getPositionX();
	int y = pos.getPositionY();
	_board[y][x] = c;
}

/*checks neighboring characters for nice print*/
const int Board::checkWallType(int x, int y) const
{
	bool top = false, left = false, right = false, bottom = false;


	if (_board[x - 1][y] == '#' && x != 0)
		top = true;
	if (_board[x][y - 1] == '#' && y != 0)
		left = true;
	if (_board[x][y + 1] == '#' && y != width - 1)
		right = true;
	if (_board[x + 1][y] == '#' && x != height)
		bottom = true;


	if (top == true && left == true && right == true && bottom == true)
		return 206; //X
	else if (top == true && bottom == true && left == true)
		return 185; //left T
	else if (top == true && bottom == true && right == true)
		return 204; //right T
	else if (left == true && right == true && top == true)
		return 202; //reverse T
	else if (left == true && right == true && bottom == true)
		return 203; // T
	else if (left == true && right == true)
		return 205; //horizontal
	else if (top == true && right == true)
		return 200; //left bottom corner
	else if (top == true && left == true)
		return 188; //right bottom corner
	else if (bottom == true && right == true)
		return 201; //top left corner
	else if (bottom == true && left == true)
		return 187; //top right corner
	else if (top == true || bottom == true)
		return 186; //vertical
	else
		return 205;

}






