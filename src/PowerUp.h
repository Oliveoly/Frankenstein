#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>
#include <list>
#include "Ennemy.h"
#include "Element.h"


class PowerUp : public Element
{
public:
	PowerUp(double x_init, double y_init, std::string type);
	void update_sprite();
	std::string type;
	void destroy();
	
private:
	
};