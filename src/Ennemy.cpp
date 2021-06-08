#include "Ennemy.h"
#include <iostream>

Ennemy::Ennemy(double x, double y, double size) : Character(x, y), size{ size }
{
    //attention !!! adresse complete, ne marche que pour moi...
    if (!texture.loadFromFile("C:/Users/dovaco/github/frankenstein/Frankenstein/Ressources/ennemy.png"))
    {
        std::cout << "Erreur lors du chargement de ennemy.png1234" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
};



void Ennemy::update_sprite()
{
    sprite.setPosition(get_x(), get_y());
}