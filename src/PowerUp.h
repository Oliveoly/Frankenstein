#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <CollisionDetection.hpp>
#include <list>
#include "Ennemy.h"



extern int width;
extern int height;
extern std::list<Ennemy*> ennemies;
extern std::list<Ennemy*>::iterator it;

class PowerUp
{
public:
	PowerUp(double x_init, double y_init);
	float get_x() { return collider.getPosition().x; };
	float get_y() { return collider.getPosition().y; };
	sf::Sprite get_sprite() { return sprite; }
	void set_x(float new_x) { collider.setPosition(cd::Vector2<float>(new_x, collider.getPosition().y)); };
	void set_y(float new_y) { collider.setPosition(cd::Vector2<float>(collider.getPosition().x, new_y)); };
	void update_sprite();
	cd::CircleCollision get_collider() { return collider; }



private:
	sf::Texture texture;
	sf::Sprite sprite;
	cd::CircleCollision collider = cd::CircleCollision(cd::Vector2<float>(0, 0), 10.f);
};