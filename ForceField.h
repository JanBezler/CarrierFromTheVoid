#ifndef CARRIERFROMTHEVOID_FORCEFIELD_H
#define CARRIERFROMTHEVOID_FORCEFIELD_H

#include <SFML/Graphics.hpp>
#include "Unit.h"

class ForceField: public sf::Drawable {

private:
    sf::CircleShape shape;
    Unit owner;

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
    ForceField(Unit owner(sf::Vector2f position, std::vector<sf::Vector2f> points));
    ForceField() = delete;
    ~ForceField() = default;

    float getRadius();
    sf::Vector2f getPosition();
    void update();

};

#endif
