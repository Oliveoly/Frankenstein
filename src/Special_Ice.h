#pragma once
#include "SpecialAttack.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Iceball.h"

extern std::vector<std::unique_ptr<Element>> elements;
extern std::vector<std::unique_ptr<Element>> new_elements;

class Special_Ice : public SpecialAttack
{
public:
    Special_Ice() { buff_duration = 10; };
	void action(float x, float y, int dir)
	{
        if (reload_timer.getElapsedTime().asMilliseconds() > 500)
        {
            std::cout << "iceball !" << std::endl;
            auto iceball = std::make_unique<Iceball>(Iceball(x, y, dir));
            new_elements.push_back(std::move(iceball));
            reload_timer.restart();
        }
	}

private:
    sf::Clock reload_timer;
};