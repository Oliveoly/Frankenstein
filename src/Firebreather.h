#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ennemy.h"

class Firebreather : public Ennemy
{
public:
	Firebreather(double x_init, double y_init, double size_init);
	void update_sprite();
	void action();


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
