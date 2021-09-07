#pragma once
#include "SpecialAttack.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Fireball.h"

extern std::vector<std::unique_ptr<Element>> elements;
extern std::vector<std::unique_ptr<Element>> new_elements;

class Special_Fire : public SpecialAttack
{
public:
    Special_Fire() { buff_duration = 5; };
    void action(float x, float y, int dir)
    {
        if (reload_timer.getElapsedTime().asMilliseconds() > 100)
        {
            std::cout << "fireball !" << std::endl;
            auto fireball = std::make_unique<Fireball>(Fireball(x, y, dir));
            new_elements.push_back(std::move(fireball));
            reload_timer.restart();
        }
    }

private:
    sf::Clock reload_timer;
};