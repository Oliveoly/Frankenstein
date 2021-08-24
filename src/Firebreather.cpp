#include "Firebreather.h"
#include <iostream>
#include "Commandes.h"
#include "Hero.h"
#include "Fireball.h"

extern std::vector<Fireball*> fireballs;

Firebreather::Firebreather(double x, double y, double size) : Ennemy(x, y, size)
{
    if (!texture.loadFromFile("../../Ressources/zombieRed.png"))
    {
        std::cout << "Erreur lors du chargement de zombie.png" << std::endl;
    }
    speed = 0.5;
    texture.setSmooth(true);
    sprite.setTexture(texture);
    anim.x = 0;
    anim.y = Dir::Down;
    maxHP = 100;
};

void Firebreather::update_sprite()
{

    anim.x = (anim.x + 1) % 4;
    if (anim.x == 3) { sprite.setTextureRect(sf::IntRect(32, anim.y * 64, 32, 64)); }
    else { sprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 64, 32, 64)); }


}

void Firebreather::action()
{

    sprite.setPosition(get_x(), get_y());

    if (dirTimer.getElapsedTime().asSeconds() >= 2)
    {
        anim.y = rand() % 4;
        dirTimer.restart();
    }

    if (atkTimer.getElapsedTime().asSeconds() >= 3)
    {
        std::cout << "lancer fireball" << std::endl;
        Fireball* fireball = new Fireball(get_x(), get_y(), anim.y);
        fireballs.push_back(fireball);
        atkTimer.restart();
    }

    MoveUpCommand* buttonUp_ = new MoveUpCommand();
    MoveDownCommand* buttonDown_ = new MoveDownCommand();
    MoveLeftCommand* buttonLeft_ = new MoveLeftCommand();
    MoveRightCommand* buttonRight_ = new MoveRightCommand();

    switch (anim.y)
    {
    case Up:
        buttonUp_->execute(*this, speed);
        break;
    case Right:
        buttonRight_->execute(*this, speed);
        break;
    case Left:
        buttonLeft_->execute(*this, speed);
        break;
    case Down:
        buttonDown_->execute(*this, speed);
        break;
    }
}