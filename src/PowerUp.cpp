#include "PowerUp.h"
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>

PowerUp::PowerUp(double x, double y, std::string t) : Element(x, y)
{
    type = t;

    if (type == "speed")
    {
        if (!texture.loadFromFile("../../Ressources/meat.png"))
        {
            std::cout << "Erreur lors du chargement de meat.png" << std::endl;
        }
    }
    else if (type == "ice")
    {
        if (!texture.loadFromFile("../../Ressources/frozen_meat.png"))
        {
            std::cout << "Erreur lors du chargement de meat.png" << std::endl;
        }
    }
    
    texture.setSmooth(true);
    sprite.setTexture(texture);
};

void PowerUp::update_sprite()
{
    sprite.setPosition(get_x(), get_y());
}

