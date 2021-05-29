
#include "Menu.h"

void Menu::draw(sf::RenderTarget& target, sf::RenderStates state) const {

}

void Menu::update(sf::Vector2i) {
    chosenAction = Menu::actions::None;
}

bool Menu::mouseOnButton(const sf::Vector2f &mPos, const sf::Text &bttn)
{
    if (bttn.getGlobalBounds().contains(mPos)){
        return true;
    } else{
        return false;
    }
}


void Menu::setTextColor(sf::Text &bttn, sf::Color color)
{
    bttn.setFillColor(color);
}


void Menu::setOriginOnCenter(sf::Text &bttn)
{
    bttn.setOrigin(bttn.getGlobalBounds().width/2, bttn.getGlobalBounds().height/2);
}

void Menu::activateText(sf::Text &bttn)
{
    bttn.setOutlineThickness(3);
    bttn.setOutlineColor(sf::Color::White);
}

void Menu::deactivateText(sf::Text &bttn)
{
    bttn.setOutlineThickness(2);
    bttn.setOutlineColor(sf::Color(200,200,200));
}

Menu::actions Menu::getChosenAction()
{
    return chosenAction;
}