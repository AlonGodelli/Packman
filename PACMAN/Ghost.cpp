#pragma once
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
#include "GameObject.h"

class GameObject;
static const int ILLEGAL = 100;
static const int NOVICE = 0;
static const int GOOD = 1;

//returns current board position's character and gives ghost a new position
char getBoardPosAndNewPos(Ghost& ghost, Board board, Position pacmanPos, Position _pos, Position& newPos, int& moveCount, int difficulty) {
	static int randomMoves = 0;

	switch (ghost.getDirection()) {
	case 1: //up
		newPos.setPosition(_pos.getPositionX(), _pos.getPositionY() - 1);
		break;
	case 2: //left
		newPos.setPosition(_pos.getPositionX() - 1, _pos.getPositionY());
		break;
	case 3: //right
		newPos.setPosition(_pos.getPositionX() + 1, _pos.getPositionY());
		break;
	case 4: //down
		newPos.setPosition(_pos.getPositionX(), _pos.getPositionY() + 1);
		break;
	default:
		break;
	}
	const char boardPosition = board.getBoardChar(newPos);

	if (difficulty == NOVICE) {
		if (boardPosition == '#' || moveCount == 0) {
			ghost.setDirection(randomNum(1, 4));
			ghost.setMoveCount(0);
		}
		return boardPosition;

	}
	else if (difficulty == GOOD) {
		if (moveCount > 30) {
			if (boardPosition == '#' || randomMoves == 0)
				ghost.setDirection(randomNum(1, 4));

			randomMoves++;
			return boardPosition;
		}
		else {
			randomMoves = 0;
			ghost.smartGhost(pacmanPos, newPos, board);
		}
	}
	else // difficulty = best 
		ghost.smartGhost(pacmanPos, newPos, board);

}

Ghost::Ghost()
{
}

Ghost::Ghost(const Position pos)
{
	_pos = pos;
}

void Ghost::Move(Ghost& ghost, Board& board, const Position& pacmanPos, const bool isDesigned, const int difficulty)
{
	Position newPos;
	_moveCount++;
	if (_moveCount > 40) {
		_moveCount = 0;
	}
	if (_moveCount % 2 == 0) {
		const char boardPosition = getBoardPosAndNewPos(ghost, board, pacmanPos, _pos, newPos, _moveCount, difficulty);
		GameObject::Move(board, _pos, newPos, boardPosition, isDesigned);
	}

}

void Ghost::setMoveCount(const int moveCount)
{
	_moveCount = moveCount;
}

const int Ghost::getMoveCount() const
{
	return _moveCount;
}

void Ghost::print(const int color)
{
	changeColor(color);
	gotoxy(_pos.getPositionX(), _pos.getPositionY());
	char g = static_cast <char>(234);
	cout << g;
}

const char Ghost::smartGhost(Position& pacmanPos, Position& newPos, Board& board)
{
	int xPac = pacmanPos.getPositionX();
	int yPac = pacmanPos.getPositionY();
	float distanceUp = ILLEGAL, distanceLeft = ILLEGAL, distanceRight = ILLEGAL, distanceDown = ILLEGAL;
	newPos.setPosition(_pos.getPositionX(), _pos.getPositionY() - 1);
	const char boardPositionU = board.getBoardChar(newPos);
	if (boardPositionU != '#' && boardPositionU != '%' && _pos.getPositionY() != 0) {
		int xGhost = newPos.getPositionX();
		int yGhost = newPos.getPositionY();

		distanceUp = sqrt(pow((xGhost - xPac), 2) + pow((yGhost - yPac), 2));
	}

	newPos.setPosition(_pos.getPositionX() - 1, _pos.getPositionY());
	const char boardPositionL = board.getBoardChar(newPos);
	if (boardPositionL != '#' && boardPositionL != '%' && _pos.getPositionX() != 0) {
		int xGhost = newPos.getPositionX();
		int yGhost = newPos.getPositionY();

		distanceLeft = sqrt(pow((xGhost - xPac), 2) + pow((yGhost - yPac), 2));
	}

	newPos.setPosition(_pos.getPositionX() + 1, _pos.getPositionY());
	const char boardPositionR = board.getBoardChar(newPos);
	if (boardPositionR != '#' && boardPositionR != '%' && _pos.getPositionX() != 80 - 1) {
		int xGhost = newPos.getPositionX();
		int yGhost = newPos.getPositionY();

		distanceRight = sqrt(pow((xGhost - xPac), 2) + pow((yGhost - yPac), 2));
	}

	newPos.setPosition(_pos.getPositionX(), _pos.getPositionY() + 1);
	const char boardPositionD = board.getBoardChar(newPos);
	if (boardPositionD != '#' && boardPositionD != '%' && _pos.getPositionY() != 25 - 1) {
		int xGhost = newPos.getPositionX();
		int yGhost = newPos.getPositionY();

		distanceDown = sqrt(pow((xGhost - xPac), 2) + pow((yGhost - yPac), 2));
	}
	if (distanceUp <= distanceDown && distanceUp <= distanceRight && distanceUp <= distanceLeft) {
		newPos.setPosition(_pos.getPositionX(), _pos.getPositionY() - 1);
		return boardPositionU;
	}
	else if (distanceDown <= distanceRight && distanceDown <= distanceLeft) {
		newPos.setPosition(_pos.getPositionX(), _pos.getPositionY() + 1);
		return boardPositionD;
	}
	else if (distanceRight <= distanceLeft) {
		newPos.setPosition(_pos.getPositionX() + 1, _pos.getPositionY());
		return boardPositionR;
	}
	else {
		newPos.setPosition(_pos.getPositionX() - 1, _pos.getPositionY());
		return boardPositionL;

	}
}
