
#ifndef CARRIERFROMTHEVOID_ANIMATION_H
#define CARRIERFROMTHEVOID_ANIMATION_H
#include <SFML/Graphics.hpp>

class Animation: public sf::Drawable {
private:

    std::vector<sf::Sprite> frames;
    int counter;
    int maxCounter;

public:


    Animation(sf::Vector2f position, float duration, float size, std::vector<sf::Texture> &textures);
    ~Animation() override = default;

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    void update();
    int getCounter();
};


#endif //CARRIERFROMTHEVOID_ANIMATION_H
