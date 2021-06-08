#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"


class Ennemy : public Character
{
public:
	Ennemy(double x_init, double y_init, double size_init);
	~Ennemy();
	void update_sprite();
	void move(int x, int y);
	void attack();


private:
	double size;
	enum Dir
	{
		Down,
		Left, 
		Right,
		Up
	};
	sf::Vector2i anim;
	sf::Clock dirTimer;


};

