#pragma once
#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "Fruit.h"
#include "GameObject.h"

class Pacman;
class Ghost;
class Fruit;

class Game
{
public:
	enum Difficulty { BEST, GOOD, NOVICE };
private:
	bool _gameOver;
	int _score;
	int _winScore;
	bool _isDesigned;
	int _difficulty;
public:
	Game(const int winScore, const int totalScore, const bool isDesigned, const int userDifficulty);
	void start(const char newBoard[25][80], const int ghostCounter, Position(&ghostPositions)[4],
		const Position& pacmanPos, const Position& scorePos, int& totalScore, int& pacmanLives, bool& gameOver);
	const bool collisionCheck(Pacman& p, Ghost* ghosts, const int numOfGhosts, Fruit& fruit);
	void setWinScore(const int winScore);
	void setScore(const int score);
	const int getScore() const;
	void setIsDesigned(const bool isDesigned);
	const bool gameStatus(const int lives, Position scorePos, int& totalScore, bool& gameOver);
	void handleKeystroke(Pacman& pacman, Board& board, Fruit& fruit, Ghost*& ghosts, char& input, char& direction, int ghostCounter);
	void printAll(Pacman& pacman, Board& board, Fruit& fruit, Ghost*& ghosts, const int ghostCounter);
	void handleGhostCollision(Pacman& pacman, Board& board, Ghost*& ghosts, Position ghostPositions[4],
		Position pacmanPos, const int ghostCounter, bool& hitGhost, char& input, int& pacmanLives);
};

