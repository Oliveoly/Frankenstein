#include "Ennemy.h"
#include <iostream>
#include "Commandes.h"
#include "Hero.h"

//extern std::unique_ptr<Hero> frank_ptr;
extern std::vector<std::unique_ptr<Element>> elements;

Ennemy::Ennemy(double x, double y, double size) : Character(x, y), size{ size }
{
    
};

Ennemy::~Ennemy()
{
    //std::cout << "ennemi détruit" << std::endl;
}

void Ennemy::update_sprite()
{

}


void Ennemy::move(double dir_x, double dir_y)
{
    if (frozen_timer.getElapsedTime().asSeconds() > 2.5)
    {
        frozen = false;
        sprite.setColor(sf::Color::White);
    }
    if (frozen)
    {
        return;
    }

    int old_x = get_x();
    int old_y = get_y();

    // 0 < x + dir_x < 1000
    set_x(std::min((double)width, std::max(0.0, get_x() + dir_x)));
    // 0 < y + dir_y < 600
    set_y(std::min((double)height, std::max(0.0, get_y() + dir_y)));

    std::vector<std::unique_ptr<Element>>::iterator it;
    for (it = elements.begin(); it != elements.end(); ++it)
    {
        //s'il y a collision...
        if (collider.intersects((*it)->get_collider()) && (this != it->get()) )
        {
            //...avec frank
            Hero* frank_ptr = dynamic_cast<Hero*>(it->get()); 
            if(frank_ptr) //si ce n'est pas un Hero, le dynamic_cast echoue et le test vaut false
            {
                //std::cout << "collision zombie -> hero" << std::endl;
                set_x(old_x);
                set_y(old_y);
                frank_ptr->receive_damage(1);
            }
            //...ou avec un objet solide
            else if ((*it)->get_solid() && collider.intersects((*it)->get_collider()) && (this != it->get()))
            {
                //std::cout << "collision zombie -> zombie" << std::endl;
                set_x(old_x);
                set_y(old_y);
            }
        }
    }
}

void Ennemy::attack()
{

}

void Ennemy::action()
{

}

void Ennemy::freeze()
{
    std::cout << "frozen !" << std::endl;
    frozen_timer.restart();
    frozen = true;
    sprite.setColor(sf::Color::Blue);
}

void Ennemy::receive_damage(int n)
{
    if (invincibility_timer.getElapsedTime().asMilliseconds() > 1000)
    {
        currentHP -= n;
        invincibility_timer.restart();
        if (currentHP <= 0) 
        {
            destroy();
        }
    }
}