#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <conio.h>
#include "Ennemy.h"
#include "PowerUp.h"
#include "Character.h"
#include "fsm.h"




extern std::list<Ennemy*> ennemies;
extern std::list<Ennemy*>::iterator it;
extern std::list<PowerUp*> powerups;
extern std::list<PowerUp*>::iterator itp;

class Hero : public Character
{
public:
	Hero(double x_init, double y_init, double size_init);
	void handle_keyboard();
	void move(int x, int y);
	void update_sprite();

private:
	double size;
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

