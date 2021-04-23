#include "Bullet.h"

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape, state);
}

Bullet::Bullet(Unit owner, float bulletSpeed, const sf::Texture &texture)
{
    shape.setTexture(texture);
    float rotation = owner.getRotation();
    velocity = {sinf(rotation * M_PI / 180.0) * bulletSpeed, -cosf(rotation * M_PI / 180.0) * bulletSpeed};
    velocity += owner.getVelocity();
    shape.setPosition(owner.getPosition());
    shape.setScale(0.6,0.6);
    shape.setOrigin(shape.getGlobalBounds().width/2,shape.getGlobalBounds().height/2);
    shape.setRotation(rotation);
}

sf::Vector2f Bullet::getPosition()
{
    return shape.getPosition();
}

void Bullet::update()
{
    shape.move(velocity);
}