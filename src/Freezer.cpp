#include "Freezer.h"
#include <iostream>
#include "Commandes.h"
#include "Hero.h"
#include "Puddle.h"

extern std::vector<std::unique_ptr<Element>> elements;
extern std::vector<std::unique_ptr<Element>> new_elements;



Freezer::Freezer(double x, double y, double size) : Ennemy(x, y, size)
{
    speed = 0.5;
    texture = TextureManager::getTexture("freezer");
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 64, 32, 64));
    anim.x = 0;
    anim.y = Dir::Down;
    maxHP = 100;
};

void Freezer::update_sprite()
{

    anim.x = (anim.x + 1) % 4;
    if (anim.x == 3) { sprite.setTextureRect(sf::IntRect(32, anim.y * 64, 32, 64)); }
    else { sprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 64, 32, 64)); }


}

void Freezer::action()
{
    sprite.setPosition(get_x(), get_y());

    if (dirTimer.getElapsedTime().asSeconds() >= 2)
    {
        anim.y = rand() % 4;
        dirTimer.restart();
    }

    if (atkTimer.getElapsedTime().asSeconds() >= 1)
    {
        std::unique_ptr<Puddle> puddle = std::make_unique<Puddle>(Puddle(get_x(), get_y()));
        new_elements.push_back(std::move(puddle));
        atkTimer.restart();
    }


    MoveUpCommand buttonUp_;
    MoveDownCommand buttonDown_;
    MoveLeftCommand buttonLeft_;
    MoveRightCommand buttonRight_;

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

void Freezer::destroy()
{
    std::unique_ptr<PowerUp> powerup = std::make_unique<PowerUp>(PowerUp(10, 10, "ice")); //new PowerUp(get_x(), get_y(), "ice");
    new_elements.push_back(std::move(powerup));
    to_destroy = true;
}