#ifndef CARRIERFROMTHEVOID_BULLET_H
#define CARRIERFROMTHEVOID_BULLET_H

#include <SFML/Graphics.hpp>
#include <cmath>


class Bullet: public sf::Drawable {

private:
    sf::Sprite shape;
    sf::Vector2f velocity;

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
    Bullet(sf::Vector2f ownerPosition, float ownerRotation, float bulletSpeed, const sf::Texture &texture);
    Bullet() = delete;
    ~Bullet() = default;

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
    void update();
};

#endif