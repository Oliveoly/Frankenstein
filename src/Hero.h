#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include "Ennemy.h"
#include "PowerUp.h"
#include "Character.h"
#include "fsm.h"

class Hero : public Character
{
public:
	Hero(double x_init, double y_init, double size_init);
	void handle_keyboard();
	void move(double x, double y);
	void update_sprite();
	void attack();
	void receive_damage(int damage);

private:
	double size;
	sf::Clock invincibility_timer;
	void switch_anim(int id);
	enum Anim
	{
		Attacking
	};
	enum class States 
	{ 
		Normal,
		Attacking,
		Recovering,
		Dashing
	};
	enum class Triggers 
	{
		GetHit,
		Dash,
		Attack
	};
	FSM::Fsm<States, States::Normal, Triggers> fsm;	
};

