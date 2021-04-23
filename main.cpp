#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Background.h"
#include <iostream>
#include <stdlib.h>
#include "AssetsLoader.cpp"
#include <algorithm>


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "CarrierFromTheVoid", sf::Style::Fullscreen, settings);
    window.setMouseCursorVisible(false);

    window.setFramerateLimit(60);

    sf::Vector2i windowCenter {static_cast<int>(window.getSize().x/2),static_cast<int>(window.getSize().y/2)};

    sf::View view;

    float zoom = 0;

    view.reset(sf::FloatRect(0.f*zoom, 0.f*zoom, 1920.f*(zoom+1), 1080.f*(zoom+1)));

    sf::Mouse::setPosition(windowCenter, window);


    sf::Texture shipTexture;
    if (!shipTexture.loadFromFile("assets/Textures/playerShip1_blue.png"))
    {
        std::cout << "Could not load player texture";
        return 0;
    }
    shipTexture.setSmooth(true);

    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile("assets/Textures/Lasers/laserBlue01.png"))
    {
        std::cout << "Could not load bullet texture";
        return 0;
    }
    bulletTexture.setSmooth(true);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/Textures/Backgrounds/star.png"))
    {
        std::cout << "Could not load bullet texture";
        return 0;
    }
    backgroundTexture.setSmooth(true);


    Unit player = Unit(sf::Vector2f(0, 0), shipTexture);


    float playerCameraOffset = 440;
    view.setCenter(player.getPosition().x , player.getPosition().y-playerCameraOffset);


    std::vector<Bullet> bullets;
    std::vector<sf::Sprite> backgroundStars;
    std::vector<Background> backgrounds;

    for (int i=-2000; i<=2000; i+=2000)
    {
        for (int j=-2000; j<=2000; j+=2000)
        {
            backgrounds.emplace_back(Background(sf::Vector2f(i,j),backgroundTexture));
        }
    }



    bool readyToShoot = true;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }



        float angle = player.getRotation() - view.getRotation() ;
        sf::Vector2f deltaPosition = player.getPosition() - view.getCenter();

        view.move(deltaPosition.x  - playerCameraOffset*sin(-angle * M_PI / 180.0), deltaPosition.y  - playerCameraOffset*cos(-angle * M_PI / 180.0));

        float oldrotation = view.getRotation();
        view.setRotation(player.getRotation());



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            if (readyToShoot)
            {
                bullets.emplace_back(Bullet(player, 20, bulletTexture));
                readyToShoot = false;
            }
        }
        else readyToShoot = true;


//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
//        {
//            player.addTorque(1 );
//        }
//        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//        {
//            player.addTorque(-1);
//        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            player.addAccelerationStraight(7);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.addAccelerationStraight(-7);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.addAccelerationSideways(4);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.addAccelerationSideways(-4);
        }



        float mouseCenterOffset = sf::Mouse::getPosition(window).x - windowCenter.x;

//        if (mouseCenterOffset < -200) mouseCenterOffset = -200;
//        else if (mouseCenterOffset > 200) mouseCenterOffset = 200;
//        if (mouseCenterOffset < 100 && mouseCenterOffset > -100)
//        {
//            mouseCenterOffset /= 2;
//        }

        player.addTorque(mouseCenterOffset/70);

        if (mouseCenterOffset > 0)
        {
            if (mouseCenterOffset > 222) sf::Mouse::setPosition(sf::Vector2i(windowCenter.x+222,window.getSize().y/2), window);
            else sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(window).x-3-mouseCenterOffset/60,window.getSize().y/2), window);
        }
        if (mouseCenterOffset < 0)
        {
            if (mouseCenterOffset < -222) sf::Mouse::setPosition(sf::Vector2i(windowCenter.x-222,window.getSize().y/2), window);
            else sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(window).x+3-mouseCenterOffset/60,window.getSize().y/2), window);
        }

        mouseCenterOffset = 0;


        window.setView(view);

        view.setRotation(oldrotation);

        window.clear(sf::Color(42,45,51));

        for (auto it = backgrounds.begin(); it != backgrounds.end(); ++it)
        {
//            if((abs(abs(it->getPosition().x)-abs(player.getPosition().x)) > 2000) && (abs(abs(it->getPosition().y)-abs(player.getPosition().y)) > 2000))
//            {
//                backgrounds.erase(it);
//            }
            window.draw(*it);
        }


        for (auto& bullet : bullets)
        {
            bullet.update();
            window.draw(bullet);
        }

        player.update();
        window.draw(player);

        window.display();
    }

    return 0;
}