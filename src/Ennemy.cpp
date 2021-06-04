#include "Ennemy.h"
#include <iostream>

Ennemy::Ennemy(double x, double y, double size) : x{ x }, y{ y }, size{ size }
{
    shape.setPosition(x, y);
    //attention !!! adresse complete, ne marche que pour moi...
    if (!texture.loadFromFile("C:/Users/user/Documents/COURS/Cplusplus/PROJET/Frankenstein/Ressources/ennemy.png"))
    {
        std::cout << "Erreur lors du chargement de ennemy.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
};

void Ennemy::move(int dir_x, int dir_y)
{
    x = x + dir_x;
    y = y + dir_y;
}


void Ennemy::update_sprite()
{
    sprite.setPosition(x, y);
}