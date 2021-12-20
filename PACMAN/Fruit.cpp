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
#include "GameObject.h"

using namespace std;

char getBoardPosAndNewPos(Fruit& fruit, Board board, Position _pos, Position& newPos) {
	switch (fruit.getDirection()) {
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

	if (boardPosition == '#')
		fruit.setDirection(randomNum(1, 4));

	return boardPosition;
}

Fruit::Fruit(const Board& board)
{
	_value = randomNum(5, 9);
	_movesLeft = 80;
	do
	{
		int height = randomNum(0, 79);
		int width = randomNum(0, 24);
		Position pos(height, width);
		_pos = pos;
	} while (board.getBoardChar(_pos) == '#' || board.getBoardChar(_pos) == '%');
}

void Fruit::randomise(const Board& board)
{
	do
	{
		int height = randomNum(0, 79);
		int width = randomNum(0, 24);

		Position pos(height, width);
		_pos = pos;
	} while (board.getBoardChar(_pos) == '#' || board.getBoardChar(_pos) == '%');

	_value = randomNum(5, 9);
}

void Fruit::print(const int color)
{
	changeColor(color);
	gotoxy(_pos.getPositionX(), _pos.getPositionY());
	char fruit = _value + 48;
	cout << fruit;
}

void Fruit::Move(Fruit& fruit, Board& board, const bool isDesigned)
{
	Position newPos;
	if (_movesLeft == 0) {
		_movesLeft == 80;
	}
	else if (_movesLeft % 4 == 0) {
		const char boardPosition = getBoardPosAndNewPos(fruit, board, _pos, newPos);
		GameObject::Move(board, _pos, newPos, boardPosition, isDesigned);
	}
}

void Fruit::setValue(const int value)
{
	_value = value;
}

const int Fruit::getValue() const
{
	return _value;
}

void Fruit::setMovesLeft(const int movesLeft)
{
	_movesLeft = movesLeft;
}

const int Fruit::getMovesLeft() const
{
	return _movesLeft;
}

void Fruit::setActivated(const bool activated)
{
	_activated = activated;
}

const bool Fruit::getActivated() const
{
	return _activated;
}

void Fruit::gameLoop(Fruit& fruit, Board& board, const bool isDesigned)
{
	if (fruit.getActivated()) {
		fruit.Move(fruit, board, isDesigned);
		if (getMovesLeft() < 16)
			fruit.print(15 - 3 * isDesigned); //red
		else
			fruit.print(15 - 13 * isDesigned); // green

		fruit.setMovesLeft(fruit.getMovesLeft() - 1);
	}
	if (fruit.getMovesLeft() == 0) {
		fruit.setActivated(false);
		gotoxy(fruit.getPosition().getPositionX(), fruit.getPosition().getPositionY());
		changeColor(15 - 14 * isDesigned); //blue
		cout << board.getBoardChar(fruit.getPosition());
		fruit.randomise(board);
	}
	if (!fruit.getActivated()) {
		fruit.setMovesLeft(fruit.getMovesLeft() + 1);
		if (fruit.getMovesLeft() == 80) {
			fruit.setActivated(true);
		}
	}
}
