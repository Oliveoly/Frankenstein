#include "Hero.h"
#include <iostream>
#include <conio.h>
#include <../Collider2D/include/CollisionDetection.hpp>
#include "Commandes.h"
#include "Iceball.h"
#include "Special_None.h"
#include "Special_Ice.h"
#include "Special_Fire.h"

extern std::vector<std::unique_ptr<Element>> elements;
extern std::vector<std::unique_ptr<Element>> new_elements;

Hero::Hero(double x, double y, double size) : Character(x, y), size{ size }
{
    maxHP = 15;
    currentHP = 15;
    texture = TextureManager::getTexture("hero");
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 48, 32, 48));

    special = std::make_unique<Special_None>();

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

    std::vector<std::unique_ptr<Element>>::iterator it;
    for (it = elements.begin(); it != elements.end(); ++it)
    {
        Ennemy* test = dynamic_cast<Ennemy*>(it->get());
        if (test && collider.intersects((*it)->get_collider()))
        {
            //std::cout << "collision hero -> zombie" << std::endl;
            //Prendre des dégâts, et devenir invincible pendant quelques secondes.
            set_x(old_x);
            set_y(old_y);
            receive_damage(1);
            if (currentHP <= 0) {
                std::cout << "Game Over!" << std::endl;
            }
        }
    }
    
}

void Hero::action()
{
    if (currentHP > 0) {
        sprite.setPosition(get_x(), get_y());

        if ( (special->get_buff_duration() != 0) && (special->get_Timer().getElapsedTime().asSeconds() > special->get_buff_duration()) )
        {
            special = std::make_unique<Special_None>();
        }

        MoveUpCommand buttonUp_;
        MoveDownCommand buttonDown_;
        MoveLeftCommand buttonLeft_;
        MoveRightCommand buttonRight_;
        AttackCommand buttonAttack_;
        PowerUpCommand buttonPower_;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            anim.y = 3;
            buttonUp_.execute(*this, speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            anim.y = 0;
            buttonDown_.execute(*this, speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            anim.y = 2;
            buttonRight_.execute(*this, speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            anim.y = 1;
            buttonLeft_.execute(*this, speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            //buttonAttack_->execute(*this, speed);
            cd::CircleCollision attack_area = cd::CircleCollision(cd::Vector2<float>(get_x(), get_y()), 50.f);
            std::vector<std::unique_ptr<Element>>::iterator it;
            it = elements.begin();
            while (it != elements.end())
            {
                Ennemy* ennemt_ptr = dynamic_cast<Ennemy*>(it->get());
                if (ennemt_ptr && attack_area.intersects((*it)->get_collider()))
                {
                    std::cout << "bonk !" << std::endl;
                    //Tuer l'ennemi
                    ennemt_ptr->receive_damage(1);
                    break;
                }
                it++;
            }
        }


        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            std::vector<std::unique_ptr<Element>>::iterator it;
            for (it = elements.begin(); it != elements.end(); ++it)
            {
                
                PowerUp* test = dynamic_cast<PowerUp*>(it->get());
                if (test && collider.intersects((*it)->get_collider()))
                {
                    std::cout << "nom nom !" << std::endl;
                    //Appliquer un buff au perso, puis détruire le power-up et le retirer de la liste.
                    //TODO : différents buffs en fonction du power-up
                    if (test->type == "speed")
                    {
                        sprite.setColor(sf::Color::Green);
                        speed += 1;
                        modif++;
                        (*it)->destroy();
                        break;
                    }
                    else if (test->type == "ice")
                    {
                        special = std::make_unique<Special_Ice>();
                        modif++;
                        (*it)->destroy();
                        break;
                    }
                    else if (test->type == "fire")
                    {
                        special = std::make_unique<Special_Fire>();
                        modif++;
                        (*it)->destroy();
                        break;
                    }
                }
            }
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        {
            special->action(get_x(), get_y(), anim.y);
        }
    }
    
}

void Hero::update_sprite()
{
    anim.x = (anim.x + 1) % 3;
    sprite.setTextureRect(sf::IntRect(anim.x * 48, anim.y * 48, 48, 48));
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
    if (invincibility_timer.getElapsedTime().asMilliseconds() > 1000)
    {
        currentHP -= damage;
        invincibility_timer.restart();
        if (currentHP<=0) {
            
        std::cout << "GameOver" << std::endl;
        
        }
    }
    
}



int Hero::get_modif()
{
    return modif;
}
