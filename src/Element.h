#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>
#include <list>
#include "TextureManager.h"


extern int width;
extern int height;

class Element
{
public:
	Element();
	Element(double x_init, double y_init);
	float get_x() { return collider.getPosition().x; };
	float get_y() { return collider.getPosition().y; };
	sf::Sprite get_sprite() { return sprite; };
	void set_x(float new_x) { collider.setPosition(cd::Vector2<float>(new_x, collider.getPosition().y)); };
	void set_y(float new_y) { collider.setPosition(cd::Vector2<float>(collider.getPosition().x, new_y)); };
	virtual void update_sprite();
	virtual void action();
	virtual void destroy();
	cd::AABBCollision get_collider() { return collider; };
	bool get_solid() { return solid; };
	bool get_to_destroy() { return to_destroy; };

protected:
	sf::Texture* texture;
	sf::Sprite sprite;
	cd::AABBCollision collider = cd::AABBCollision();
	bool to_destroy = false;
	bool solid = true;
};