#include "Hero.h"
#include <iostream>
#include <conio.h>
#include <../Collider2D/include/CollisionDetection.hpp>
#include "Commandes.h"

extern std::vector<Element*> elements;

Hero::Hero(double x, double y, double size) : Character(x, y), size{ size }
{
    //attention !!! adresse complete, ne marche que pour moi...
    if (!texture.loadFromFile("../../Ressources/perso2.png"))
    {
        std::cout << "Erreur lors du chargement de perso.png" << std::endl;
    }
    maxHP = 100;
    currentHP = 100;
    texture.setSmooth(true);
    sprite.setTexture(texture);

    fsm.add_transitions(
        {
            //  from state	  ,to state			    ,triggers			,guard						,action
            { States::Normal  ,States::Attacking	,Triggers::Attack	,[this] {return true; }		,[this] { switch_anim(Anim::Attacking); } }
        });
};

void Hero::move(double dir_x, double dir_y)
{
    int old_x = get_x();
    int old_y = get_y();

    // 0 < x + dir_x < 1000
    set_x( std::min((double)width, std::max(0.0, get_x() + dir_x)) );
    // 0 < y + dir_y < 600
    set_y( std::min((double)height, std::max(0.0, get_y() + dir_y)) );

    std::vector<Element*>::iterator it;
    for (it = elements.begin(); it != elements.end(); ++it)
    {
        Ennemy* test = dynamic_cast<Ennemy*>(*it);
        if (test && collider.intersects((*it)->get_collider()))
        {
            std::cout << "collision hero -> zombie" << std::endl;
            //Prendre des dégâts, et devenir invincible pendant quelques secondes.
            set_x(old_x);
            set_y(old_y);
            receive_damage(1);
        }
    }
    /*
    std::vector<Ennemy*>::iterator it;
    for (it = ennemies.begin(); it != ennemies.end(); ++it)
    {
        //std::cout << collider.getPosition().x << " , " << collider.getPosition().y << " , " << collider.getRadius() << std::endl;
        //std::cout << (*it)->get_collider().getPosition().x << " , " << (*it)->get_collider().getPosition().y << " , " << (*it)->get_collider().getRadius() << std::endl;
        if (collider.intersects((*it)->get_collider()))
        {
            std::cout << "collision hero -> zombie" << std::endl;
            //Prendre des dégâts, et devenir invincible pendant quelques secondes.
            set_x(old_x);
            set_y(old_y);
            receive_damage(1);
        }
    }
    */
    
}

void Hero::handle_keyboard()
{
    MoveUpCommand *buttonUp_ = &MoveUpCommand() ;
    MoveDownCommand *buttonDown_= &MoveDownCommand();
    
    MoveLeftCommand* buttonLeft_ = &MoveLeftCommand();
    MoveRightCommand* buttonRight_ =&MoveRightCommand();
    AttackCommand* buttonAttack_ = &AttackCommand();
    PowerUpCommand* buttonPower_ = &PowerUpCommand();

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
        //buttonAttack_->execute(*this, speed);
        cd::CircleCollision attack_area = cd::CircleCollision(cd::Vector2<float>(get_x(), get_y()), 50.f);
        std::vector<Element*>::iterator it;
        it = elements.begin();
        while (it != elements.end())
        {
            Ennemy* test = dynamic_cast<Ennemy*>(*it);
            if (test && attack_area.intersects((*it)->get_collider()))
            {
                std::cout << "bonk !" << std::endl;
                //Tuer l'ennemi
                elements.erase(it);
                break;
            }
            it++;
        }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        std::vector<Element*>::iterator it;
        for (it = elements.begin(); it != elements.end(); ++it)
        {
            PowerUp* test = dynamic_cast<PowerUp*>(*it);
            if (test && collider.intersects((*it)->get_collider()))
            {
                std::cout << "nom nom !" << std::endl;
                /*
                Appliquer un buff au perso, puis détruire le power-up et le retirer de la liste.
                */
                sprite.setColor(sf::Color::Green);
                speed+=3;
                elements.erase(it);
                break;
            }
        }
    }
    
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

void Hero::attack()
{
    /*
    cd::CircleCollision attack_area = cd::CircleCollision(cd::Vector2<float>(get_x(), get_y()), 50.f);
    
    while (it != ennemies.end())
    {
        //std::cout << collider.getPosition().x << " , " << collider.getPosition().y << " , " << collider.getRadius() << std::endl;
        //std::cout << (*it)->get_collider().getPosition().x << " , " << (*it)->get_collider().getPosition().y << " , " << (*it)->get_collider().getRadius() << std::endl;
        if (attack_area.intersects((*it)->get_collider()))
        {
            std::cout << "bonk !" << std::endl;
            
            //Tuer l'ennemi
            
            ennemies.erase(it);
            delete (*it);
        }
        ++it;
    }
    */
}

void Hero::receive_damage(int damage)
{
    if (invincibility_timer.getElapsedTime().asMilliseconds() > 2000)
    {
        currentHP -= damage;
        invincibility_timer.restart();
    }
    
}
