
#include "DeathMenu.h"
#include <string>

DeathMenu::DeathMenu(sf::Vector2f sizeOfWindow, const sf::Font & font)
{
    windowSize = sizeOfWindow;

    youLose = sf::Text("Game OVER!", font, 50);
    playAgain = sf::Text("Play Again", font, 30);
    quit = sf::Text("Quit Game", font, 30);
    points = sf::Text("You earned some points!", font, 24);

    setTextColor(playAgain, sf::Color(120,120,205));
    setTextColor(quit, sf::Color(205,120,120));
    setTextColor(youLose);
    setTextColor(points);

    setOriginOnCenter(youLose);
    setOriginOnCenter(points);
    setOriginOnCenter(playAgain);
    setOriginOnCenter(quit);

    youLose.setPosition(sf::Vector2f(0, -windowSize.y/4));
    points.setPosition(sf::Vector2f(0, -windowSize.y/8));
    playAgain.setPosition(sf::Vector2f(0, 0));
    quit.setPosition(sf::Vector2f(0, windowSize.y/4));

}

void DeathMenu::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(youLose, state);
    target.draw(points, state);
    target.draw(playAgain, state);
    target.draw(quit, state);

}

void DeathMenu::update(sf::Vector2i positionOfMouse, int score)
{
    points.setString("You earned " + std::to_string(score) + " points!");
    setOriginOnCenter(points);

    mousePosition = {positionOfMouse.x - windowSize.x / 2 , positionOfMouse.y - windowSize.y / 2};
    bool clicked = false;

    if (mouseOnButton(mousePosition, playAgain))
    {
        activateText(playAgain);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            chosenAction = Menu::actions::Play;
            clicked = true;
        }
    }else{
        deactivateText(playAgain);
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
