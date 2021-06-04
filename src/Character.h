#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Character
{
public:
	Character(double x_init, double y_init, double size_init);
	int get_speed() { return speed; }
	double get_x() { return x; };
	double get_y() { return y; };
	sf::CircleShape get_shape() { return shape; }
	sf::Sprite get_sprite() { return sprite; }
	void set_x(double new_x) { x = new_x; };
	void set_y(double new_y) { y = new_y; };
	void handle_keyboard();
	void move(int x, int y);
	void update_sprite();

private:
	int speed = 3;
	double x;
	double y;
	double size;
	sf::CircleShape shape = sf::CircleShape(10.f); //non utilisé, pour tests uniquement
	sf::Texture texture;
	sf::Sprite sprite;


};

