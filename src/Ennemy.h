#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"


class Ennemy : public Character
{
public:
	Ennemy(double x_init, double y_init, double size_init);
	~Ennemy();
	virtual void update_sprite(); //gère le changement de frame, qui est demandé toutes les 0,25s
	void move(double x, double y); //gère le déplacement et les collisions
	virtual void attack(); //gère l'attaque > appelé par action(), méthode à part pour clarifier le code
	virtual void action(); //gère le comportement de l'ennemi en direct (propre à chaque ennemi)


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

