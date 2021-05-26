
#include "Particle.h"

Particle::Particle(sf::Vector2f position, float diameter, sf::Color color, int shake, int pointCount)
{
    shape.setPointCount(pointCount);
    shape.setPosition(position);
    shape.setRadius(diameter/2);
    shape.setOrigin(diameter/2,diameter/2);
    shape.setFillColor(color);
    shake_ = shake;
}

void Particle::update()
{
    shape.move(sf::Vector2f(shake_ - rand()%(2*shake_+1),shake_ - rand()%(2*shake_+1)));
    if (shape.getFillColor().a > 0){
        shape.setFillColor(sf::Color(shape.getFillColor()-sf::Color(1,1,0,rand()%4)));
    }
    if (shape.getRadius() > 0){
        shape.setRadius(shape.getRadius()-0.07);
    }
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (shape.getFillColor().a > 0){
        target.draw(shape, states);
    }
}