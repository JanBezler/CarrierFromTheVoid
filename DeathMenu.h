
#ifndef CARRIERFROMTHEVOID_DEATHMENU_H
#define CARRIERFROMTHEVOID_DEATHMENU_H
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>

class DeathMenu: public Menu {


private:
    sf::Text youLose;
    sf::Text playAgain;
    sf::Text points;
    sf::Text quit;


public:

    DeathMenu(sf::Vector2f, const sf::Font &);

    void draw(sf::RenderTarget&, sf::RenderStates ) const override;
    void update(sf::Vector2i, int);

};

#endif //CARRIERFROMTHEVOID_DEATHMENU_H
