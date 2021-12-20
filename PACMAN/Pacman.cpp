#pragma once
#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Pacman.h"
#include "Board.h"
#include "Game.h"
#include "misc.h"
#include "GameObject.h"

//returns current board position's character and gives pacman a new position
char getBoardPosAndNewPos(char direction, Board board, Position currPos, Position& newPos) {
	char boardPosition, currChar;
	int maxHeight = 25, maxWidth = 80, minHeight = 0, minWidth = 0;

	switch (direction) {
	case 'w': //up
		newPos.setPosition(currPos.getPositionX(), currPos.getPositionY() - 1);
		currChar = board.getBoardChar(newPos);
		if (currChar == '%' || currPos.getPositionY() == 0) {
			do { //make sure the pacman stay in limit
				newPos.setPosition(currPos.getPositionX(), --maxHeight);
				currChar = board.getBoardChar(newPos);
			} while (currChar == '%');
		}
		break;

	case 'a': //left
		newPos.setPosition(currPos.getPositionX() - 1, currPos.getPositionY());
		currChar = board.getBoardChar(newPos);
		if (currChar == '%' || currPos.getPositionX() == 0) {
			do { //make sure the pacman stay in limit
				newPos.setPosition(--maxWidth, currPos.getPositionY());
				currChar = board.getBoardChar(newPos);
			} while (currChar == '%');
		}
		break;
	case 'd': //right
		newPos.setPosition(currPos.getPositionX() + 1, currPos.getPositionY());
		currChar = board.getBoardChar(newPos);
		if (currChar == '%' || currPos.getPositionX() == maxWidth - 1) {
			do { //make sure the pacman stay in limit
				newPos.setPosition(minWidth++, currPos.getPositionY());
				currChar = board.getBoardChar(newPos);
			} while (currChar == '%');
		}
		break;
	case 'x': //down
		newPos.setPosition(currPos.getPositionX(), currPos.getPositionY() + 1);
		currChar = board.getBoardChar(newPos);
		if (currChar == '%' || currPos.getPositionY() == maxHeight - 1) {
			do { //make sure the pacman stay in limit
				newPos.setPosition(currPos.getPositionX(), minHeight++);
				currChar = board.getBoardChar(newPos);
			} while (currChar == '%');
		}
		break;
	case 's': //stop
		newPos.setPosition(currPos.getPositionX(), currPos.getPositionY());
		break;
	default:
		break;
	}
	boardPosition = board.getBoardChar(newPos);

	return boardPosition;
}

Pacman::Pacman(const Position& pos, char direction, int lives)
{
	_pos = pos;
	_direction = direction;
	_lives = lives;
}

void Pacman::Move(const char direction, Board& board, int& addToScore)
{
	Position newPos;
	char currDirection = direction;
	char boardPosition = getBoardPosAndNewPos(direction, board, _pos, newPos);
	switch (boardPosition)
	{
	case (char)250://breadCrums
		board.setBoardChar(newPos, ' ');
		gotoxy(_pos.getPositionX(), _pos.getPositionY());
		cout << board.getBoardChar(_pos);
		_pos = newPos;
		addToScore += 1;
		break;
	case ' ':
		gotoxy(_pos.getPositionX(), _pos.getPositionY());
		cout << board.getBoardChar(_pos);
		_pos = newPos;
		break;
	default:
		break;
	}
}

void Pacman::setLives(const int lives)
{
	_lives = lives;
}

const int Pacman::getLives() const
{
	return _lives;
}

void Pacman::print(const int color)
{
	changeColor(color);
	gotoxy(_pos.getPositionX(), _pos.getPositionY());
	char p = 2;
	cout << p;
}

