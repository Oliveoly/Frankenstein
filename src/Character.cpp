#include "Character.h"
#include <iostream>
#include <CollisionDetection.hpp>

Character::Character(double x, double y, double size) : size{ size }
{
    collider.setPosition(cd::Vector2<float>(x, y));
    //attention !!! adresse complete, ne marche que pour moi...
    if (!texture.loadFromFile("C:/Users/user/Documents/COURS/Cplusplus/PROJET/Frankenstein/Ressources/perso.png"))
    {
        std::cout << "Erreur lors du chargement de perso.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
};

void Character::move(int dir_x, int dir_y)
{
    int old_x = get_x();
    int old_y = get_y();

    // 0 < x + dir_x < 1000
    set_x( std::min((float)width, std::max(0.f, get_x() + dir_x)) );
    // 0 < y + dir_y < 600
    set_y( std::min((float)height, std::max(0.f, get_y() + dir_y)) );

    for (it = ennemies.begin(); it != ennemies.end(); ++it)
    {
        //std::cout << collider.getPosition().x << " , " << collider.getPosition().y << " , " << collider.getRadius() << std::endl;
        //std::cout << (*it)->get_collider().getPosition().x << " , " << (*it)->get_collider().getPosition().y << " , " << (*it)->get_collider().getRadius() << std::endl;
        if (collider.intersects((*it)->get_collider()))
        {
            std::cout << "aie !" << std::endl;
            /*
            Prendre des dégâts, et devenir invincible pendant quelques secondes.
            */
            set_x(old_x);
            set_y(old_y);
        }
    }
    
}

void Character::handle_keyboard()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move(0, -speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move(0, speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move(speed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move(-speed, 0);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        for (itp = powerups.begin(); itp != powerups.end(); ++itp)
        {
            if (collider.intersects((*itp)->get_collider()))
            {
                std::cout << "nom nom !" << std::endl;
                /*
                Appliquer un buff au perso, puis détruire le power-up et le retirer de la liste.
                */
            }
        }
    }
    
    
    update_sprite();
}

void Character::update_sprite()
{
    sprite.setPosition(get_x(), get_y());
}