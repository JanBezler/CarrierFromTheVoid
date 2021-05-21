
#ifndef CARRIERFROMTHEVOID_MENU_H
#define CARRIERFROMTHEVOID_MENU_H
#include <SFML/Graphics.hpp>

class Menu: public sf::Drawable {

protected:
    struct button {
        std::string name;
        sf::Text buttonText;
        sf::RectangleShape buttonBackground;
    };


    virtual bool mouseOnButton(sf::Vector2f mPos, button);


public:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    virtual void update();



 };


#endif //CARRIERFROMTHEVOID_MENU_H
