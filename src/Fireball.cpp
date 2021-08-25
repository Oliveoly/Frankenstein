#include "Fireball.h"
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>
#include "Hero.h"

extern Hero* frank_ptr;

Fireball::Fireball(double x, double y, int dir) : Element(x, y)
{

    if (!texture.loadFromFile("../../Ressources/fireball.png"))
    {
        std::cout << "Erreur lors du chargement de fireball.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 32, 64, 32));

    switch (dir)
    {
    case 0: //Down
        move_x = 0;
        move_y = speed;
        sprite.rotate(90);
        break;
    case 1: //Left
        move_x = -speed;
        move_y = 0;
        sprite.rotate(180);
        break;
    case 2: //Right
        move_x = speed;
        move_y = 0;
        break;
    case 3: //Up
        move_x = 0;
        move_y = -speed;
        sprite.rotate(-90);
        break;
    }

    
};

void Fireball::update_sprite()
{
    sprite.setPosition(get_x(), get_y());

    anim.x = (anim.x + 1) % 5;
    sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 32, 64, 32));
}

void Fireball::action()
{
    //se déplacer dans la bonne direction
    set_x(get_x() + move_x);
    set_y(get_y() + move_y);
    
    sprite.setPosition(get_x(), get_y());

    if (collider.intersects((frank_ptr->get_collider())))
    {
        std::cout << "collision fireball -> hero" << std::endl;
        //
        frank_ptr->receive_damage(1);
    }
}

