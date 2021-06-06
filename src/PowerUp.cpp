#include "PowerUp.h"
#include <iostream>
#include <CollisionDetection.hpp>

PowerUp::PowerUp(double x, double y)
{
    collider.setPosition(cd::Vector2<float>(x, y));
    //attention !!! adresse complete, ne marche que pour moi...
    if (!texture.loadFromFile("C:/Users/user/Documents/COURS/Cplusplus/PROJET/Frankenstein/Ressources/meat.png"))
    {
        std::cout << "Erreur lors du chargement de meat.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
};


void PowerUp::update_sprite()
{
    //std::cout << collider.getPosition().x << " , " << collider.getPosition().y << " , " << collider.getRadius() << std::endl;
    sprite.setPosition(get_x(), get_y());
}