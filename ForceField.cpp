#include "ForceField.h"

void ForceField::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}


ForceField::ForceField(Unit owner(sf::Vector2f, std::vector<sf::Vector2f>))
{

}


void ForceField::update()
{

}

sf::Vector2f ForceField::getPosition()
{
    return shape.getPosition();
}

float ForceField::getRadius()
{
    return shape.getRadius();
}