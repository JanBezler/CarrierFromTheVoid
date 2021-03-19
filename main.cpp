#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

int main()
{


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1700, 800), "SFML works!", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::View view;
    view.reset(sf::FloatRect(0.f, 0.f, 1700.f, 800.f));


    std::vector<sf::Vector2f> points{sf::Vector2f(308,0),
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
    unit.rotate(-90);


    Unit sample = Unit(sf::Vector2f(300, 300), points);
    Unit sample1 = Unit(sf::Vector2f(300, 600), points);
    sf::CircleShape pppp = sf::CircleShape(10,10);


    view.setCenter(unit.getPosition().x , unit.getPosition().y-300);


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



        float angle = unit.getRotation() - view.getRotation() - 90;
        sf::Vector2f deltaPosition = unit.getPosition() - view.getCenter();

        view.move(deltaPosition.x  + 300*sin(-angle * M_PI / 180.0), deltaPosition.y  + 300*cos(-angle * M_PI / 180.0));

        //view.setCenter(deltaPosition.x, deltaPosition.y);

        pppp.setPosition(view.getCenter());

        float oldrotation = view.getRotation();
        view.setRotation(unit.getRotation() + 90);



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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
        {
            unit.addAccelerationSideways(3);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            unit.addAccelerationSideways(-3);
        }

        window.setView(view);

        view.setRotation(oldrotation);

        unit.update();




        window.clear();
        window.draw(unit);
        window.draw(sample);
        window.draw(sample1);
        //window.draw(pppp);

        for (auto& bullet : bullets)
        {
            bullet.update();
            window.draw(bullet);
        }




        window.display();
    }

    return 0;
}