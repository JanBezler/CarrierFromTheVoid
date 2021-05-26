
#ifndef CARRIERFROMTHEVOID_PARTICLE_H
#define CARRIERFROMTHEVOID_PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle: public sf::Drawable{
protected:
    sf::CircleShape shape;
    int shake_;


public:

    Particle(sf::Vector2f position = sf::Vector2f(0,0), float diameter = 10, sf::Color color = sf::Color::White, int shake = 2, int pointCount = 20);


    void update();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};



#endif //CARRIERFROMTHEVOID_PARTICLE_H
