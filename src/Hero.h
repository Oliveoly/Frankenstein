#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include "Ennemy.h"
#include "PowerUp.h"
#include "Character.h"
#include "fsm.h"
#include "SpecialAttack.h"

class Hero : public Character
{
public:
	Hero(double x_init, double y_init, double size_init);
	void action();
	void move(double x, double y);
	void update_sprite();
	void attack();
	void receive_damage(int damage);
	void increase_modif(int n);
	
	int get_modif() const { return modif; };

private:
	double size;
	sf::Clock invincibility_timer;
	void switch_anim(int id);
	enum Anim
	{
		Attacking,
		Dead,
		Zombie
	};
	enum class States 
	{ 
		Normal,
		Dead,
		Zombie,
		Attacking,
		Recovering,
		Dashing
	};
	enum class Triggers 
	{
		Dies,
		Transform,
		GetHit,
		Dash,
		Attack
	};

	FSM::Fsm<States, States::Normal, Triggers> fsm;	
	int modif = 0;

	std::unique_ptr<SpecialAttack> special;
};

