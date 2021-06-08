#include "Hero.h"
#include <iostream>
#include <conio.h>
#include <../Collider2D/include/CollisionDetection.hpp>
#include "Commandes.h"


Hero::Hero(double x, double y, double size) : Character(x, y), size{ size }
{
    //attention !!! adresse complete, ne marche que pour moi...
    if (!texture.loadFromFile("../../Ressources/perso2.png"))
    {
        std::cout << "Erreur lors du chargement de perso.png" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);

    fsm.add_transitions(
        {
            //  from state	  ,to state			    ,triggers			,guard						,action
            { States::Normal  ,States::Attacking	,Triggers::Attack	,[this] {return true; }		,[this] { switch_anim(Anim::Attacking); } }
        });
};

void Hero::move(int dir_x, int dir_y)
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

void Hero::handle_keyboard()
{
    MoveUpCommand* buttonUp_ = new MoveUpCommand();
    MoveDownCommand* buttonDown_ = new MoveDownCommand();
    MoveLeftCommand* buttonLeft_= new MoveLeftCommand();
    MoveRightCommand* buttonRight_ = new MoveRightCommand();
    AttackCommand* buttonAttack_ = new AttackCommand();
    PowerUpCommand* buttonPower_ = new PowerUpCommand();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        buttonUp_->execute(*this,speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        buttonDown_->execute(*this, speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        buttonRight_->execute(*this, speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        buttonLeft_->execute(*this, speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {

        std::cout << "AAAAAAAAA" << std::endl;
        std::cout << fsm.execute(Triggers::Attack) << std::endl;
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

void Hero::update_sprite()
{
    sprite.setPosition(get_x(), get_y());
}

void Hero::switch_anim(int id)
{
    switch (id)
    {
    case Anim::Attacking:
        std::cout << "Attacking" << std::endl;
        sprite.setColor(sf::Color::Red);
        break;
    default:
        break;
    }
}