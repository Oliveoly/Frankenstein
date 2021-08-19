#include "Ennemy.h"
#include <iostream>
#include "Commandes.h"
#include "Hero.h"

extern Hero* frank_ptr;

Ennemy::Ennemy(double x, double y, double size) : Character(x, y), size{ size }
{
    
};

Ennemy::~Ennemy()
{
    std::cout << "ennemi détruit" << std::endl;
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


void Ennemy::move(double dir_x, double dir_y)
{
    int old_x = get_x();
    int old_y = get_y();

    // 0 < x + dir_x < 1000
    set_x(std::min((double)width, std::max(0.0, get_x() + dir_x)));
    // 0 < y + dir_y < 600
    set_y(std::min((double)height, std::max(0.0, get_y() + dir_y)));

    if (collider.intersects((frank_ptr->get_collider())))
    {
        std::cout << "collision zombie -> hero" << std::endl;
        set_x(old_x);
        set_y(old_y);
    }
    

    std::vector<Ennemy*>::iterator it;
    for (it = ennemies.begin(); it != ennemies.end(); ++it)
    {
        //on vérifie que l'ennemi ne rentre dans aucun autre ennemi (différent de lui-même)
        if (collider.intersects((*it)->get_collider()) && (this != (*it) ) )
        {
            std::cout << "collision zombie -> zombie" << std::endl;
            set_x(old_x);
            set_y(old_y);
        }
    }
}

void Ennemy::attack()
{

}

void Ennemy::action()
{

}