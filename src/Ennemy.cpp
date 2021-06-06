#include "Ennemy.h"
#include <iostream>

Ennemy::Ennemy(double x, double y, double size) : size{ size }
{
    collider.setPosition(cd::Vector2<float>(x, y));
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
    set_x(std::min((float)width, std::max(0.f, get_x() + dir_x)));
    set_y(std::min((float)height, std::max(0.f, get_y() + dir_y)));
}


void Ennemy::update_sprite()
{
    sprite.setPosition(get_x(), get_y());
}