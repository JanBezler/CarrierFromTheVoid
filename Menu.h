
#ifndef CARRIERFROMTHEVOID_MENU_H
#define CARRIERFROMTHEVOID_MENU_H
#include <SFML/Graphics.hpp>

class Menu: public sf::Drawable {

public:
    enum actions
    {
        None,
        Quit,
        Play
    };


protected:
    sf::Vector2f windowSize;
    sf::Vector2f mousePosition;

    actions chosenAction;

    static bool mouseOnButton(const sf::Vector2f&, const sf::Text&);
    static void setOriginOnCenter(sf::Text &);
    static void setTextColor(sf::Text&, sf::Color = sf::Color::White);
    static void activateText(sf::Text&);
    static void deactivateText(sf::Text&);


public:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    virtual void update(sf::Vector2i);
    virtual Menu::actions getChosenAction();

 };


#endif //CARRIERFROMTHEVOID_MENU_H
