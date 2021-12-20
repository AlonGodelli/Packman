#pragma once
#include "Position.h"
#include "Game.h"
#include "GameObject.h"

class Board;


class Pacman : public GameObject
{
private:
	int _lives;
public:
	Pacman(const Position& pos, char direction = 's', int lives = 3);
	void Move(const char direction, Board& board, int& addToScore);
	void print(const int color);
	void setLives(const int lives);
	const int getLives() const;
};




