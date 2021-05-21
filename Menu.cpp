
#include "Menu.h"

void Menu::draw(sf::RenderTarget& target, sf::RenderStates state) const {

}

void Menu::update() {

}

bool Menu::mouseOnButton(sf::Vector2f mPos, button bttn)
{
    if (bttn.buttonBackground.getGlobalBounds().contains(mPos)){
        return true;
    } else{
        return false;
    }
}