#include "Character.h"

Character::Character(double x, double y) : Element(x, y)
{
    maxHP = 0;
    currentHP = 0;
}

void Character::move(int dir_x, int dir_y)
{
    set_x(std::min((float)width, std::max(0.f, get_x() + dir_x)));
    set_y(std::min((float)height, std::max(0.f, get_y() + dir_y)));
}
