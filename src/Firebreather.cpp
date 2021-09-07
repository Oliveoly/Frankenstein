#include "Firebreather.h"
#include <iostream>
#include "Commandes.h"
#include "Hero.h"
#include "Fireball.h"
#include "PowerUp.h"

extern std::vector<std::unique_ptr<Element>> elements;
extern std::vector<std::unique_ptr<Element>> new_elements;



Firebreather::Firebreather(double x, double y, double size) : Ennemy(x, y, size)
{
    collider.setSize(cd::Vector2<float>(30.0, 30.0));
    speed = 0.5;
    texture = TextureManager::getTexture("firebreather");
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 64, 32, 64));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
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
        std::unique_ptr<Fireball> fireball = std::make_unique<Fireball>(Fireball(get_x(), get_y(), anim.y));
        new_elements.push_back(std::move(fireball)); //les éléments créés ne peuvent être ajouté directement dans le liste elements car elle est en train d'être parcourue
        atkTimer.restart();
    }

    MoveUpCommand buttonUp_;
    MoveDownCommand buttonDown_ ;
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

void Firebreather::destroy()
{
    std::unique_ptr<PowerUp> powerup = std::make_unique<PowerUp>(PowerUp(get_x(), get_y(), "fire")); //new PowerUp(get_x(), get_y(), "ice");
    new_elements.push_back(std::move(powerup));
    to_destroy = true;
}