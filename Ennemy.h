#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"


class Ennemy : public Character
{
public:
	Ennemy(double x_init, double y_init, double size_init);
	void update_sprite();

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


};

