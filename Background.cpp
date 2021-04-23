
#include "Background.h"

void Background::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    for (auto &shape : stars) target.draw(shape, state);
}

Background::Background(sf::Vector2f position, const sf::Texture &starTexture)
{
    this->position = position;
    unsigned int spaceBetween = 150;
    for (unsigned int i=0; i<static_cast<int>(2000/spaceBetween)+1; i++)
    {
        for (unsigned int j=0; j<static_cast<int>(2000/spaceBetween)+1; j++)
        {
            sf::Sprite starSprite;
            starSprite.setTexture(starTexture);
            starSprite.setPosition(position.x-1000+i*spaceBetween+rand() % 255,position.y-1000+j*spaceBetween+rand() % 255);
            starSprite.setColor(sf::Color(80+rand() % 40,80+rand() % 40,80+rand() % 40,80+rand() % 170));
            float tempScale = 0.7+(rand() % 50)/80;
            starSprite.setRotation(rand() % 180);
            starSprite.setScale(tempScale,tempScale);
            stars.emplace_back(starSprite);
        }
    }
}

sf::Vector2f Background::getPosition()
{
    return position;
}