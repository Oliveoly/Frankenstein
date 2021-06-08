#include "Ennemy.h"
#include <iostream>

Ennemy::Ennemy(double x, double y, double size) : Character(x, y), size{ size }
{
    //attention !!! adresse complete, ne marche que pour moi...
    if (!texture.loadFromFile("../../Ressources/zombie.png"))
    {
        std::cout << "Erreur lors du chargement de zombie.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    anim.x = 0;
    anim.y = Dir::Down;
};



void Ennemy::update_sprite()
{
    sprite.setPosition(get_x(), get_y());
    anim.x = (anim.x + 1) % 4;
    if(anim.x == 3){    sprite.setTextureRect(sf::IntRect(32, anim.y * 64, 32, 64)); }
    else {              sprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 64, 32, 64)); }
}