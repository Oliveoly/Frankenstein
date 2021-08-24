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
        //
        frank_ptr->receive_damage(1);
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