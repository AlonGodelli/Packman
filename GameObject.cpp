#pragma once
#include "GameObject.h"
#include "misc.h"
#include "Board.h"



void GameObject::setPosition(const Position& pos)
{
	_pos = pos;
}

void GameObject::Move(const Board& board, Position& currPos, Position& newPos, const char boardPosition, const bool isDesigned)
{
	switch (boardPosition)
	{
	case (char)250: //breadcrumbs
		gotoxy(currPos.getPositionX(), currPos.getPositionY());
		changeColor(15 - 14 * isDesigned);
		cout << board.getBoardChar(currPos);
		currPos = newPos;
		break;
	case ' ':
		gotoxy(currPos.getPositionX(), currPos.getPositionY());
		changeColor(15 - 14 * isDesigned);
		cout << board.getBoardChar(currPos);
		currPos = newPos;
		break;

	default:
		break;
	}
}

Position& GameObject::getPosition()
{
	return _pos;
}

void GameObject::setDirection(const int direction)
{
	_direction = direction;
}

const int& GameObject::getDirection() const
{
	return _direction;
}

GameObject::~GameObject()
{
}
