
#ifndef CARRIERFROMTHEVOID_MAINMENU_H
#define CARRIERFROMTHEVOID_MAINMENU_H
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>

class MainMenu: public Menu {

private:
    sf::Text title;
    sf::Text play;
    sf::Text quit;
    sf::Text hint;

public:

    MainMenu(sf::Vector2f, const sf::Font &);

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    void update(sf::Vector2i positionOfMouse);

};


#endif //CARRIERFROMTHEVOID_MAINMENU_H
