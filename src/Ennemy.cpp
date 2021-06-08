#include "Ennemy.h"
#include <iostream>
#include "Commandes.h"

Ennemy::Ennemy(double x, double y, double size) : Character(x, y), size{ size }
{
    //attention !!! adresse complete, ne marche que pour moi...
    if (!texture.loadFromFile("../../Ressources/zombie.png"))
    {
        std::cout << "Erreur lors du chargement de zombie.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    anim.x = 0;
    anim.y = Dir::Down;
    maxHP = 100;
};

Ennemy::~Ennemy()
{
    std::cout << "ded" << std::endl;
}

void Ennemy::update_sprite()
{
    sprite.setPosition(get_x(), get_y());
    anim.x = (anim.x + 1) % 4;
    if(anim.x == 3){    sprite.setTextureRect(sf::IntRect(32, anim.y * 64, 32, 64)); }
    else {              sprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 64, 32, 64)); }

    if (dirTimer.getElapsedTime().asSeconds() >= 2)
    {
        anim.y = rand() % 4;
        dirTimer.restart();
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


void Ennemy::move(int dir_x, int dir_y)
{
    int old_x = get_x();
    int old_y = get_y();

    // 0 < x + dir_x < 1000
    set_x(std::min((float)width, std::max(0.f, get_x() + dir_x)));
    // 0 < y + dir_y < 600
    set_y(std::min((float)height, std::max(0.f, get_y() + dir_y)));

    
}

void Ennemy::attack()
{

}