#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1700, 800), "SFML works!", sf::Style::Default, settings);
    window.setFramerateLimit(60);


    std::vector<sf::Vector2f> points{sf::Vector2f(208,0),
                                     sf::Vector2f(192,32),
                                     sf::Vector2f(128,96),
                                     sf::Vector2f(96,32),
                                     sf::Vector2f(32,64),
                                     sf::Vector2f(32,32),
                                     sf::Vector2f(16,16),
                                     sf::Vector2f(16,-16),
                                     sf::Vector2f(32,-32),
                                     sf::Vector2f(32,-64),
                                     sf::Vector2f(96,-32),
                                     sf::Vector2f(128,-96),
                                     sf::Vector2f(192,-32)};

    Unit unit = Unit(sf::Vector2f(200, 200), points);

    std::vector<Bullet> bullets;


    bool readyToShoot = true;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            if (readyToShoot)
            {
                bullets.insert(bullets.begin(), Bullet(unit, 14, 60));
                readyToShoot = false;
            }
        }
        else readyToShoot = true;




        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            unit.addTorque(4);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            unit.addTorque(-4);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            unit.addAccelerationStraight(7);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            unit.addAccelerationStraight(-7);
        }

        unit.update();


        window.clear();
        window.draw(unit);
        for (auto& bullet : bullets)
        {
            bullet.update();
            window.draw(bullet);
        }

        window.display();
    }

    return 0;
}