#include "Iceball.h"
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>
#include "Hero.h"

extern std::vector<Element*> elements;

Iceball::Iceball(double x, double y, int dir) : Element(x, y)
{

    if (!texture.loadFromFile("../../Ressources/iceball.png"))
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

void Iceball::update_sprite()
{
    sprite.setPosition(get_x(), get_y());

    anim.x = (anim.x + 1) % 5;
    sprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 32, 64, 32));
}

void Iceball::action()
{
    //se déplacer dans la bonne direction
    set_x(get_x() + move_x);
    set_y(get_y() + move_y);

    sprite.setPosition(get_x(), get_y());

    std::vector<Element*>::iterator it;
    it = elements.begin();
    while (it != elements.end())
    {
        Ennemy* test = dynamic_cast<Ennemy*>(*it);
        if (test && collider.intersects((*it)->get_collider()))
        {
            std::cout << "bonk !" << std::endl;
            //Geler l'ennemi
            test->freeze();
        }
        it++;
    }
    
}

