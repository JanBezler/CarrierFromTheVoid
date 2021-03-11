#ifndef CARRIERFROMTHEVOID_UNIT_H
#define CARRIERFROMTHEVOID_UNIT_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Unit: public sf::Drawable {

private:
    float drag;

    sf::ConvexShape shape;
    sf::Vector2f velocity;
    float rotationSpeed;
    float accelerationStraight;
    float accelerationSideways;
    float torque;
    float maxSpeed;

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
    Unit(sf::Vector2f position, std::vector<sf::Vector2f> points);
    Unit(){delete(this);}
    ~Unit() = default;

    void update();

    void rotate(float degree);
    void moveForwardBackward(float distance);
    void moveLeftRight(float distance);
    void move(sf::Vector2f offset);
    void setPosition(sf::Vector2f position);

    void addTorque(float torque);
    void addAccelerationStraight(float acceleration);
    void addAccelerationSideways(float acceleration);




    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    float getRadius();
    float getRotation();
    float left();
    float right();
    float top();
    float bottom();

};

#endif