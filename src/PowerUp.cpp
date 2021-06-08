#include "PowerUp.h"
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>

PowerUp::PowerUp(double x, double y) : Element(x, y)
{
    
    if (!texture.loadFromFile("../../Ressources/meat.png"))
    {
        std::cout << "Erreur lors du chargement de meat.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
};

PowerUp::~PowerUp() {
    
}

void PowerUp::update_sprite()
{
    //std::cout << collider.getPosition().x << " , " << collider.getPosition().y << " , " << collider.getRadius() << std::endl;
    sprite.setPosition(get_x(), get_y());
}

