#include "Character.h"
#include <iostream>

Character::Character(double x, double y, double size) : x{ x }, y{ y }, size{ size }
{
    shape.setPosition(x, y);
    //attention !!! adresse complete, ne marche que pour moi...
    if (!texture.loadFromFile("C:/Users/user/Documents/COURS/Cplusplus/PROJET/Frankenstein/Ressources/perso.png"))
    {
        std::cout << "Erreur lors du chargement de perso.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
};

void Character::move(int dir_x, int dir_y)
{
    x = x + dir_x;
    y = y + dir_y;
}

void Character::handle_keyboard()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move(0, -speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move(0, speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move(speed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move(-speed, 0);
    }
    
    update_sprite();
}

void Character::update_sprite()
{
    sprite.setPosition(x, y);
}