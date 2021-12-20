#pragma once
#include "GameObject.h"
class Board;


class Fruit :
    public GameObject
{
private:
    int _value;
    int _movesLeft;
    bool _activated = true;
public:
    Fruit(const Board& board);
    void randomise(const Board& board);
    void print(const int color);
    void Move(Fruit& fruit, Board& board, const bool isDesigned);
    void setValue(const int value);
    const int getValue() const;
    void setMovesLeft(const int movesLeft);
    const int getMovesLeft() const;
    void setActivated(const bool activated);
    const bool getActivated() const;
    void gameLoop(Fruit& fruit, Board& board, const bool isDesigned);
};

