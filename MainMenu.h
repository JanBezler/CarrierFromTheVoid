
#ifndef CARRIERFROMTHEVOID_MAINMENU_H
#define CARRIERFROMTHEVOID_MAINMENU_H
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>

class MainMenu: public Menu {

public:

    enum actions
    {
        None,
        Quit,
        Play
    };

private:
    button title;
    button play;
    button quit;
    button hint;

    actions chosenAction;

protected:
    sf::Vector2f windowSize;
    sf::Vector2f mousePosition;

public:

    MainMenu(sf::Vector2f windowSize, const sf::Font & font);

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    void update(sf::Vector2i positionOfMouse);

    MainMenu::actions getChosenAction();

};


#endif //CARRIERFROMTHEVOID_MAINMENU_H
