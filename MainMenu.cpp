
#include "MainMenu.h"

MainMenu::MainMenu(sf::Vector2f sizeOfWindow, const sf::Font & font)
{
    windowSize = sizeOfWindow;

    title = button{"Title", sf::Text("Carrier From The Void", font, 50), sf::RectangleShape()};
    play = button{"Play", sf::Text("Play!", font, 30), sf::RectangleShape()};
    quit = button{"Quit", sf::Text("Quit Game", font, 30), sf::RectangleShape()};
    hint = button{"Hint", sf::Text("Moving: WSAD + mouse\nShoot: LMB or space\nPause: ESC", font, 24), sf::RectangleShape()};

    play.buttonBackground.setSize(sf::Vector2f(play.buttonText.getLocalBounds().width + (2 * play.buttonText.getLocalBounds().height), play.buttonText.getLocalBounds().height * 3));
    quit.buttonBackground.setSize(sf::Vector2f(quit.buttonText.getLocalBounds().width + (2 * quit.buttonText.getLocalBounds().height), quit.buttonText.getLocalBounds().height * 3));

    title.buttonText.setOrigin(sf::Vector2f(title.buttonText.getLocalBounds().width / 2, title.buttonText.getLocalBounds().height));
    hint.buttonText.setOrigin(sf::Vector2f(title.buttonText.getLocalBounds().width / 2, title.buttonText.getLocalBounds().height));
    play.buttonText.setOrigin(sf::Vector2f(play.buttonText.getLocalBounds().width / 2, play.buttonText.getLocalBounds().height));
    quit.buttonText.setOrigin(sf::Vector2f(quit.buttonText.getLocalBounds().width / 2, quit.buttonText.getLocalBounds().height));

    hint.buttonText.setFillColor(hint.buttonText.getFillColor()-sf::Color(0,0,0,160));

    play.buttonBackground.setOrigin(sf::Vector2f(play.buttonBackground.getLocalBounds().width / 2, play.buttonBackground.getLocalBounds().height / 2));
    quit.buttonBackground.setOrigin(sf::Vector2f(quit.buttonBackground.getLocalBounds().width / 2, quit.buttonBackground.getLocalBounds().height / 2));

    title.buttonText.setPosition(sf::Vector2f(0, -windowSize.y/4));
    hint.buttonText.setPosition(sf::Vector2f(windowSize.x/3, -windowSize.y/8));
    play.buttonText.setPosition(sf::Vector2f(0, 0));
    quit.buttonText.setPosition(sf::Vector2f(0, +windowSize.y/4));

    play.buttonBackground.setPosition(play.buttonText.getPosition());
    quit.buttonBackground.setPosition(quit.buttonText.getPosition());

    play.buttonBackground.setFillColor(sf::Color(100,120,220,200));
    quit.buttonBackground.setFillColor(sf::Color(220,120,100,200));

    play.buttonBackground.setOutlineColor(sf::Color(80,100,200,200));
    quit.buttonBackground.setOutlineColor(sf::Color(200,100,80,220));

    play.buttonBackground.setOutlineThickness(5.f);
    quit.buttonBackground.setOutlineThickness(5.f);
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(title.buttonText, state);

    target.draw(hint.buttonText, state);

    target.draw(play.buttonBackground, state);
    target.draw(play.buttonText, state);

    target.draw(quit.buttonBackground, state);
    target.draw(quit.buttonText, state);

}

void MainMenu::update(sf::Vector2i positionOfMouse)
{
    mousePosition = {positionOfMouse.x - windowSize.x / 2 , positionOfMouse.y - windowSize.y / 2};
    bool clicked = false;
    if (mouseOnButton(mousePosition, play))
    {
        play.buttonBackground.setFillColor(sf::Color(140,160,250,200));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            chosenAction = MainMenu::actions::Play;
            clicked = true;
        }
    }else{
        play.buttonBackground.setFillColor(sf::Color(100,120,220,200));
    }

    if (mouseOnButton(mousePosition, quit))
    {
        quit.buttonBackground.setFillColor(sf::Color(250,160,140,200));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            chosenAction = MainMenu::actions::Quit;
            clicked = true;
        }
    }else{
        quit.buttonBackground.setFillColor(sf::Color(220,120,100,200));
    }

    if (!(clicked)){
        chosenAction = MainMenu::actions::None;
    }

}

MainMenu::actions MainMenu::getChosenAction()
{
    return chosenAction;
}