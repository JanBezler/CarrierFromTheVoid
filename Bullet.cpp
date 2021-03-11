#include "Bullet.h"

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}

Bullet::Bullet(Unit owner, float radius, float bulletSpeed, float scaleY)
{
    bulletSpeed = bulletSpeed;
    float rotation = owner.getRotation();
    velocity = {cosf(rotation * M_PI / 180.0) * bulletSpeed, sinf(rotation * M_PI / 180.0) * bulletSpeed};
    shape.setPosition(owner.getPosition());
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.scale(1, scaleY);
    shape.setRotation(rotation);
    shape.setFillColor(sf::Color::Red);
}

sf::Vector2f Bullet::getPosition()
{
    return shape.getPosition();
}

void Bullet::update()
{
    shape.move(velocity);

}