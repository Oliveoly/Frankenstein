#include "Puddle.h"
#include <iostream>
#include <../Collider2D/include/CollisionDetection.hpp>
#include "Hero.h"

//extern std::unique_ptr<Hero> frank_ptr;
extern std::vector<std::unique_ptr<Element>> elements;

Puddle::Puddle(double x, double y) : Element(x, y)
{
    collider.setSize(cd::Vector2<float>(100.0, 20.0));
    solid = false;
    texture = TextureManager::getTexture("puddle");
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setPosition(get_x(), get_y());
    sprite.setTextureRect(sf::IntRect(anim.x * 100, anim.y * 31, 100, 31));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

};

void Puddle::update_sprite()
{
    anim.x = (anim.x + 1) % 4;
    sprite.setTextureRect(sf::IntRect(anim.x * 100, anim.y * 31, 100, 31));
}

void Puddle::action()
{
    if (lifetimer.getElapsedTime().asSeconds() > 3)
    {
        to_destroy = true;
        return;
    }

    std::vector<std::unique_ptr<Element>>::iterator it;
    for (it = elements.begin(); it != elements.end(); ++it)
    {
        Hero* frank_ptr = dynamic_cast<Hero*>(it->get());
        if (frank_ptr && collider.intersects(((*it)->get_collider())))
        {
            std::cout << "collision puddle -> frank" << std::endl;
            //
            frank_ptr->receive_damage(1);
        }
    }
}