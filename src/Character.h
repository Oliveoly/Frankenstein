#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <CollisionDetection.hpp>
#include <list>
#include "Ennemy.h"
#include "PowerUp.h"




extern int width;
extern int height;
extern std::list<Ennemy*> ennemies;
extern std::list<Ennemy*>::iterator it;
extern std::list<PowerUp*> powerups;
extern std::list<PowerUp*>::iterator itp;

class Character
{
public:
	Character(double x_init, double y_init, double size_init);
	int get_speed() { return speed; }
	float get_x() { return collider.getPosition().x; };
	float get_y() { return collider.getPosition().y; };
	sf::Sprite get_sprite() { return sprite; }
	void set_x(float new_x) { collider.setPosition(cd::Vector2<float>(new_x, collider.getPosition().y)); };
	void set_y(float new_y) { collider.setPosition(cd::Vector2<float>(collider.getPosition().x, new_y)); };
	void handle_keyboard();
	void move(int x, int y);
	void update_sprite();
	

private:
	int speed = 3;
	double size;
	sf::Texture texture;
	sf::Sprite sprite;
	cd::CircleCollision collider = cd::CircleCollision(cd::Vector2<float>(0, 0), 10.f);


};

