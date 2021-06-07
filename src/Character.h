#pragma once

#include "Element.h"

class Character : public Element
{
public:
	Character(double x, double y);
	int get_speed() { return speed; }
	void move(int x, int y);



protected:
	int speed = 3;
	int maxHP;
	int currentHP;
};