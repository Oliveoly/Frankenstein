#include "PowerUp.h"
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>

PowerUp::PowerUp(double x, double y, std::string t) : Element(x, y)
{
    type = t;

    if (type == "speed")
    {
        texture = TextureManager::getTexture("meat");
    }
    else if (type == "ice")
    {
        texture = TextureManager::getTexture("frozen_meat");
    }
    else if (type == "fire")
    {
        texture = TextureManager::getTexture("fire_meat");
    }
    solid = false;
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
};

void PowerUp::update_sprite()
{
    sprite.setPosition(get_x(), get_y());
}

void PowerUp::destroy()
{
    to_destroy = true;
}