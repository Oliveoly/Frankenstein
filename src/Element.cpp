#include "Element.h"
#include <iostream>

Element::Element()
{
    collider.setPosition(cd::Vector2<float>(0, 0));
}

Element::Element(double x, double y)
{
    collider.setPosition(cd::Vector2<float>(x, y));
    
};

void Element::update_sprite()
{
    
}

void Element::action()
{

}

void Element::destroy()
{

}
