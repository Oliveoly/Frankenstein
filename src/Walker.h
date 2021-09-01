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
	void destroy();

private:
	double size;
	sf::Clock dirTimer;


};
