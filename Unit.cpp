#include "Unit.h"

void Unit::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}

Unit::Unit(sf::Vector2f position, std::vector<sf::Vector2f> points)
{
    maxSpeed = 0;
    int vectorSize = points.size();
    shape.setPointCount(vectorSize);
    for (int i = 0; i < vectorSize; ++i) shape.setPoint(i, points[i]);
    shape.setPosition(position);
    shape.setScale(0.5,0.5);
    shape.setOrigin(shape.getGlobalBounds().width,0);
    shape.setRotation(10);
}

void Unit::update()
{

}

void Unit::rotate(float degree)
{
    shape.setRotation(shape.getRotation() + degree);
}

void Unit::moveForwardBackward(float distance)
{
    float rotation = getRotation();
    shape.move(sf::Vector2f{cosf(rotation * M_PI / 180.0) * distance, sinf(rotation * M_PI / 180.0) * distance});
}

void Unit::moveLeftRight(float distance)
{
    float rotation = getRotation();
    shape.move(sf::Vector2f{sinf(rotation * M_PI / 180.0) * distance, cosf(rotation * M_PI / 180.0) * distance});
}

void Unit::move(sf::Vector2f offset)
{
    shape.move(offset);
}

void Unit::setPosition(sf::Vector2f position)
{
    shape.setPosition(position);
}


sf::Vector2f Unit::getSize()
{
    return sf::Vector2f{shape.getGlobalBounds().width, shape.getGlobalBounds().height};
}

sf::Vector2f Unit::getPosition()
{
    return shape.getPosition();
}

float Unit::getRadius()
{
    return sqrtf(powf(shape.getGlobalBounds().width, 2.0) + powf(shape.getGlobalBounds().height, 2)) / 2;
}

float Unit::getRotation()
{
    return shape.getRotation();
}

float Unit::left()
{
    return this->shape.getGlobalBounds().left;
}

float Unit::right()
{
    return this->shape.getGlobalBounds().left + shape.getGlobalBounds().width;
}

float Unit::top()
{
    return this->shape.getGlobalBounds().top;
}

float Unit::bottom()
{
    return this->shape.getGlobalBounds().top + shape.getGlobalBounds().height;
}