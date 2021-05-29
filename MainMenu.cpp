
#include "MainMenu.h"

MainMenu::MainMenu(sf::Vector2f sizeOfWindow, const sf::Font & font)
{
    windowSize = sizeOfWindow;

    title = sf::Text("Carrier From The Void", font, 50);
    play = sf::Text("Play!", font, 30);
    quit = sf::Text("Quit Game", font, 30);
    hint = sf::Text("Moving: WSAD + mouse\nShoot: LMB or space\nPause: ESC", font, 24);

    setTextColor(play, sf::Color(120,120,205));
    setTextColor(quit, sf::Color(205,120,120));
    setTextColor(title);
    setTextColor(hint, sf::Color(220,220,220,160));

    setOriginOnCenter(title);
    setOriginOnCenter(hint);
    setOriginOnCenter(play);
    setOriginOnCenter(quit);

    title.setPosition(sf::Vector2f(0, -windowSize.y/4));
    hint.setPosition(sf::Vector2f(windowSize.x/3, -windowSize.y/8));
    play.setPosition(sf::Vector2f(0, 0));
    quit.setPosition(sf::Vector2f(0, windowSize.y/4));

}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(title, state);
    target.draw(hint, state);
    target.draw(play, state);
    target.draw(quit, state);

}

void MainMenu::update(sf::Vector2i positionOfMouse)
{
    mousePosition = {positionOfMouse.x - windowSize.x / 2 , positionOfMouse.y - windowSize.y / 2};
    bool clicked = false;

    if (mouseOnButton(mousePosition, play))
    {
        activateText(play);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            chosenAction = Menu::actions::Play;
            clicked = true;
        }
    }else{
        deactivateText(play);
    }

    if (mouseOnButton(mousePosition, quit))
    {
        activateText(quit);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            chosenAction = Menu::actions::Quit;
            clicked = true;
        }
    }else{
        deactivateText(quit);
    }

    if (!(clicked)){
        chosenAction = Menu::actions::None;
    }

}
