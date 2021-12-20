#pragma once
class Position
{
private:
	int _x;
	int _y;

public:
	Position();
	Position(const int x, const int y);
	void setPosition(const int x, const int y);
	const int getPositionY() const;
	const int getPositionX() const;
};

