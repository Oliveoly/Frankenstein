#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"


class Ennemy : public Character
{
public:
	Ennemy(double x_init, double y_init, double size_init);
	~Ennemy();
	virtual void update_sprite(); //g�re le changement de frame, qui est demand� toutes les 0,25s
	void move(double x, double y); //g�re le d�placement et les collisions
	virtual void attack(); //g�re l'attaque > appel� par action(), m�thode � part pour clarifier le code
	virtual void action(); //g�re le comportement de l'ennemi en direct (propre � chaque ennemi)


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

