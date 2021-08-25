#include "Puddle.h"
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>
#include "Hero.h"

extern Hero* frank_ptr;

Puddle::Puddle(double x, double y) : Element(x, y)
{

    if (!texture.loadFromFile("../../Ressources/puddle.png"))
    {
        std::cout << "Erreur lors du chargement de fireball.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(get_x(), get_y());
    sprite.setTextureRect(sf::IntRect(anim.x * 100, anim.y * 31, 100, 31));

};

void Puddle::update_sprite()
{
    anim.x = (anim.x + 1) % 4;
    sprite.setTextureRect(sf::IntRect(anim.x * 100, anim.y * 31, 100, 31));
}

void Puddle::action()
{

    if (collider.intersects((frank_ptr->get_collider())))
    {
        std::cout << "collision puddle -> hero" << std::endl;
        //
        frank_ptr->receive_damage(1);
    }
}

