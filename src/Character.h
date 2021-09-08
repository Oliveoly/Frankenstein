#pragma once

#include "Element.h"

class Character : public Element
{
public:
	Character(double x, double y);
	int get_speed() { return speed; }
	virtual void move(double x, double y) = 0;
	virtual void attack() = 0;
	int get_maxHP() const { return maxHP; };
	int get_currentHP() const { return currentHP; };
	virtual void receive_damage(int n) = 0;


protected:
	double speed = 3;
	int maxHP;
	int currentHP;
	enum Dir
	{
		Down,
		Left,
		Right,
		Up
	};
	sf::Vector2i anim;
};