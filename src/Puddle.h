#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>
#include <list>
#include "Ennemy.h"
#include "Element.h"


class Puddle : public Element
{
public:
	Puddle(double x_init, double y_init);
	void update_sprite();
	void action();

private:
	sf::Vector2i anim;
	double move_x;
	double move_y;
	double speed = 4;

};