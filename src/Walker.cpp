#include "Walker.h"
#include <iostream>
#include "Commandes.h"
#include "Hero.h"

Walker::Walker(double x, double y, double size) : Ennemy(x, y, size)
{
    if (!texture.loadFromFile("../../Ressources/zombie.png"))
    {
        std::cout << "Erreur lors du chargement de zombie.png" << std::endl;
    }
    speed = 1;
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 64, 32, 64));
    anim.x = 0;
    anim.y = Dir::Down;
    maxHP = 100;
};

void Walker::update_sprite()
{
    
    anim.x = (anim.x + 1) % 4;
    if (anim.x == 3) { sprite.setTextureRect(sf::IntRect(32, anim.y * 64, 32, 64)); }
    else { sprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 64, 32, 64)); }

    
}

void Walker::action()
{

    sprite.setPosition(get_x(), get_y());

    if (dirTimer.getElapsedTime().asSeconds() >= 2)
    {
        anim.y = rand() % 4;
        dirTimer.restart();
    }

    MoveUpCommand buttonUp_ ;
    MoveDownCommand buttonDown_ ;
    MoveLeftCommand buttonLeft_ ;
    MoveRightCommand buttonRight_ ;

    switch (anim.y)
    {
    case Up:
        buttonUp_.execute(*this, speed);
        break;
    case Right:
        buttonRight_.execute(*this, speed);
        break;
    case Left:
        buttonLeft_.execute(*this, speed);
        break;
    case Down:
        buttonDown_.execute(*this, speed);
        break;
    }
}