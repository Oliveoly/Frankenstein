#pragma once

#include "Element.h"

class Character : public Element
{
public:
	Character(double x, double y);
	int get_speed() { return speed; }
	virtual void move(int x, int y) = 0;
	virtual void attack() = 0;



protected:
	int speed = 3;
	int maxHP;
	int currentHP;
};