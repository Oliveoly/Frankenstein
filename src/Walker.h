#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ennemy.h"

class Walker : public Ennemy
{
public:
	Walker(double x_init, double y_init, double size_init);
	void update_sprite();
	void action(); //change de direction toutes les 2s


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
