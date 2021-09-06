#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>
#include <list>
#include "Ennemy.h"
#include "Element.h"


class Iceball : public Element
{
public:
	Iceball(double x_init, double y_init, int dir);
	void update_sprite();
	void action();

private:
	sf::Vector2i anim;
	double move_x;
	double move_y;
	double speed = 4;
	sf::Clock lifetimer;
};
