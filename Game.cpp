#pragma once
#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include "Game.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "Position.h"
#include "Fruit.h"
#include "misc.h"
#include "GameObject.h"

static char ESC = 27;

Game::Game(const int winScore, const int totalScore, const bool isDesigned, const int userDifficulty)
{
	_gameOver = false;
	_isDesigned = isDesigned;
	_score = totalScore;
	_winScore = winScore;
	_difficulty = userDifficulty;
}

void Game::setWinScore(const int winScore)
{
	_winScore = winScore;
}

void Game::setScore(const int score)
{
	_score = score;
}

const int Game::getScore() const
{
	return _score;
}

void Game::setIsDesigned(const bool isDesigned)
{
	_isDesigned = isDesigned;
}

//main game loop
void Game::start(const char newBoard[25][80], const int ghostCounter, Position(&ghostPositions)[4],
	const Position& pacmanPos, const Position& scorePos, int& totalScore, int& pacmanLives, bool& gameOver)
{
	char direction = 's';
	bool hitGhost = false;

	//initialise pacman
	Pacman pacman(pacmanPos);
	pacman.setLives(pacmanLives);

	//initialise ghosts
	Ghost* ghosts = new Ghost[ghostCounter];
	for (int i = 0; i < ghostCounter; i++)
		ghosts[i].setPosition(ghostPositions[i]);

	//initialise board
	Board board(newBoard);

	//initialise fruit
	Fruit fruit(board);

	printAll(pacman, board, fruit, ghosts, ghostCounter);
	char input = _getch();

	while (!_gameOver)
	{

		//check for new keystroke
		handleKeystroke(pacman, board, fruit, ghosts, input, direction, ghostCounter);

		int addToScore = 0;
		pacman.Move(direction, board, addToScore);
		_score += addToScore;

		//check for pacman collision with ghost
		if (this->collisionCheck(pacman, ghosts, ghostCounter, fruit))
			hitGhost = true;

		fruit.gameLoop(fruit, board, _isDesigned);

		if (this->collisionCheck(pacman, ghosts, ghostCounter, fruit))
			hitGhost = true;

		for (int i = 0; i < ghostCounter; i++)
			ghosts[i].Move(ghosts[i], board, pacman.getPosition(), _isDesigned, _difficulty);

		if (this->collisionCheck(pacman, ghosts, ghostCounter, fruit))
			hitGhost = true;

		//reset board positions if pacman is hit by ghost
		if (hitGhost)
			handleGhostCollision(pacman, board, ghosts, ghostPositions, pacmanPos, ghostCounter, hitGhost, input, pacmanLives);

		pacman.print(15 - _isDesigned);
		for (int i = 0; i < ghostCounter; i++)
			ghosts[i].print(15 - _isDesigned * (8 + i));

		_gameOver = gameStatus(pacman.getLives(), scorePos, totalScore, gameOver);

		Sleep(110);
	}
	delete[] ghosts;
}

//updates and prints score, lives and checks if game is over
const bool Game::gameStatus(const int lives, Position scorePos, int& totalScore, bool& gameOver)
{
	const char heart = 3;

	// print score
	changeColor(15); //white
	gotoxy(scorePos.getPositionX(), scorePos.getPositionY());
	cout << "Score: " << _score;

	//print lives
	changeColor(15 - 3 * _isDesigned); //red
	gotoxy(scorePos.getPositionX() + 2, scorePos.getPositionY() + 1);
	for (int i = 0; i < 3; i++) {
		if (i < lives)
			cout << heart << " ";
		else
			cout << " ";
	}
	changeColor(15 - 14 * _isDesigned);

	//check if player lost
	if (lives == 0) {
		totalScore = 0;
		gameOver = true;
		return true;
	}

	//check if player cleard level
	if (_score == _winScore) {
		totalScore = _score;
		return true;
	}
	return false;
}

void Game::handleKeystroke(Pacman& pacman, Board& board, Fruit& fruit, Ghost*& ghosts, char& input, char& direction, int ghostCounter)
{
	_flushall();

	if (_kbhit()) {
		input = _getch();
		if (input == ESC) {
			printGamePaused(15 - 7 * _isDesigned);
			//checks for ESC press to resume game
			do { input = _getch(); } while (input != ESC);

			//print all after stop pauses
			system("cls");
			printAll(pacman, board, fruit, ghosts, ghostCounter);
		}

	}
	if (isLegal(input)) {
		direction = input;
	}
}

void Game::printAll(Pacman& pacman, Board& board, Fruit& fruit, Ghost*& ghosts, const int ghostCounter)
{
	board.print(15 - 14 * _isDesigned);  //blue

	pacman.print(15 - _isDesigned); // yellow

	fruit.print(15 - 13 * _isDesigned); //green

	for (int i = 0; i < ghostCounter; i++) {
		ghosts[i].print(15 - _isDesigned * (8 + i));

	}
}

void Game::handleGhostCollision(Pacman& pacman, Board& board, Ghost*& ghosts, Position ghostPositions[4],
	Position pacmanPos, const int ghostCounter, bool& hitGhost, char& input, int& pacmanLives)
{
	gotoxy(pacman.getPosition().getPositionX(), pacman.getPosition().getPositionY());
	cout << " ";
	input = 's';
	pacman.setPosition(pacmanPos);
	for (int i = 0; i < ghostCounter; i++)
	{
		int x = ghosts[i].getPosition().getPositionX();
		int y = ghosts[i].getPosition().getPositionY();
		gotoxy(ghosts[i].getPosition().getPositionX(), ghosts[i].getPosition().getPositionY());
		changeColor(15 - 14 * _isDesigned); //blue
		cout << board.getBoardChar(ghosts[i].getPosition());
		ghosts[i].setPosition(ghostPositions[i]);
	}
	pacman.setLives(pacman.getLives() - 1);
	pacmanLives = pacman.getLives();
	hitGhost = false;
	Sleep(110);
}

const bool Game::collisionCheck(Pacman& p, Ghost* ghosts, const int numOfGhosts, Fruit& fruit)
{
	//ghost-pacman collision
	for (int i = 0; i < numOfGhosts; i++)
	{
		if (p.getPosition().getPositionX() == ghosts[i].getPosition().getPositionX() &&
			p.getPosition().getPositionY() == ghosts[i].getPosition().getPositionY())
			return true;
	}
	//pacman-fruit collison 
	if (p.getPosition().getPositionX() == fruit.getPosition().getPositionX() &&
		p.getPosition().getPositionY() == fruit.getPosition().getPositionY()) {
		this->setWinScore(this->_winScore + fruit.getValue());
		this->setScore(this->_score + fruit.getValue());
		fruit.setActivated(false);
		fruit.setMovesLeft(0);
		fruit.setValue(0);
	}
	//ghost-fruit collision
	for (int i = 0; i < numOfGhosts; i++)
	{
		if (fruit.getPosition().getPositionX() == ghosts[i].getPosition().getPositionX() &&
			fruit.getPosition().getPositionY() == ghosts[i].getPosition().getPositionY()) {
			fruit.setActivated(false);
			fruit.setMovesLeft(0);
		}
	}
	return false;
}


