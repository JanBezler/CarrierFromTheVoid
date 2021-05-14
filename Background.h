
#ifndef CARRIERFROMTHEVOID_BACKGROUND_H
#define CARRIERFROMTHEVOID_BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class Background: public sf::Drawable {

private:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    std::vector<sf::Sprite> stars;
    sf::Vector2f position;

public:
    Background(sf::Vector2f position, const sf::Texture &starTexture);
    Background() = delete;
    ~Background() override = default;

    [[maybe_unused]] sf::Vector2f getPosition();

};



#endif //CARRIERFROMTHEVOID_BACKGROUND_H
