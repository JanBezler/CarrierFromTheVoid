#include "Bullet.h"

#ifndef M_PI
#define M_PI = 3.14159265358979323846;
#endif

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}

Bullet::Bullet(sf::Vector2f ownerPosition, float ownerRotation, float bulletSpeed, const sf::Texture &texture)
{
    shape.setTexture(texture);
    float rotation = ownerRotation - 4 + rand() % 9;
    velocity = {sinf(rotation * M_PI / 180.0) * bulletSpeed, -cosf(rotation * M_PI / 180.0) * bulletSpeed};
    //velocity += owner.getVelocity();
    shape.setPosition(ownerPosition);
    shape.setScale(0.6,0.6);
    shape.setOrigin(shape.getGlobalBounds().width/2,shape.getGlobalBounds().height/2);
    shape.setRotation(rotation);
}

sf::Vector2f Bullet::getPosition()
{
    return shape.getPosition();
}

void Bullet::setPosition(sf::Vector2f position)
{
    shape.setPosition(position);
}

void Bullet::update()
{
    shape.move(velocity);
}