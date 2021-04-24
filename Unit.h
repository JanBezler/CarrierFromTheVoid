#ifndef CARRIERFROMTHEVOID_UNIT_H
#define CARRIERFROMTHEVOID_UNIT_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Unit: public sf::Drawable {

private:
    float drag;
    sf::Sprite shape;
    sf::Vector2f velocity;
    float rotationSpeed;
    float accelerationStraight;
    float accelerationSideways;
    float torque;
    float maxSpeed;

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
    Unit(sf::Vector2f position, const sf::Texture &texture);
    Unit(){delete(this);}
    ~Unit() = default;

    void update();

    void rotate(float degree);
    void moveForwardBackward(float distance);
    void moveLeftRight(float distance);
    void move(sf::Vector2f offset);
    void setPosition(sf::Vector2f position);
    void setRotation(float degree);

    void addTorque(float torque);
    void addAccelerationStraight(float acceleration);
    void addAccelerationSideways(float acceleration);




    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    sf::Vector2f getVelocity();
    float getRadius();
    float getRotation();
    float left();
    float right();
    float top();
    float bottom();

};

#endif