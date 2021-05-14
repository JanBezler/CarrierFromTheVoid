#include "Animation.h"
#include <iostream>

void Animation::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(frames[static_cast<int>(frames.size() - 0.99f * counter/maxCounter * frames.size())], state);
}

Animation::Animation(sf::Vector2f position, float duration, float size, std::vector<sf::Texture> &textures)
{
    counter = duration*60;
    maxCounter = counter;
    int randRotation = rand() % 180;
    for (auto & texture: textures)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setOrigin(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2);
        sprite.setScale(size,size);
        sprite.setRotation(randRotation);
        frames.emplace_back(sprite);
    }

}


void Animation::update()
{
    counter--;
}

int Animation::getCounter()
{
    return counter;
}