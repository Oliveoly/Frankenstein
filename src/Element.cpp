#include "Element.h"
#include <iostream>

Element::Element()
{
    collider.setPosition(cd::Vector2<float>(0, 0));
}

Element::Element(double x, double y)
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

void Element::update_sprite()
{
    sprite.setPosition(get_x(), get_y());
}