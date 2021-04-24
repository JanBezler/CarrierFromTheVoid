#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Background.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <list>


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
        std::cout << "Could not load shipTexture texture";
        return 0;
    }
    shipTexture.setSmooth(true);

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("assets/Textures/playerShip2_orange.png"))
    {
        std::cout << "Could not load enemyTexture texture";
        return 0;
    }
    enemyTexture.setSmooth(true);

    sf::Texture playerBulletTexture;
    if (!playerBulletTexture.loadFromFile("assets/Textures/Lasers/laserBlue01.png"))
    {
        std::cout << "Could not load playerBulletTexture texture";
        return 0;
    }
    playerBulletTexture.setSmooth(true);

    sf::Texture enemyBulletTexture;
    if (!enemyBulletTexture.loadFromFile("assets/Textures/Lasers/laserRed07.png"))
    {
        std::cout << "Could not load enemyBulletTexture texture";
        return 0;
    }
    enemyBulletTexture.setSmooth(true);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/Textures/Backgrounds/star.png"))
    {
        std::cout << "Could not load backgroundTexture texture";
        return 0;
    }
    backgroundTexture.setSmooth(true);


    Unit player = Unit(sf::Vector2f(0, 0), shipTexture);




    float playerCameraOffset = 300;
    view.setCenter(player.getPosition().x , player.getPosition().y-playerCameraOffset);


    std::vector<std::pair<Bullet,unsigned int>> bullets;
    std::vector<sf::Sprite> backgroundStars;
    std::vector<Background> backgrounds;
    std::vector<Unit> enemies;

    float squaresAroundPlayer = 2;

    for (int i=-2000*squaresAroundPlayer; i<=2000*squaresAroundPlayer; i+=2000)
    {
        for (int j=-2000*squaresAroundPlayer; j<=2000*squaresAroundPlayer; j+=2000)
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
                bullets.emplace_back(Bullet(player, 20, playerBulletTexture),0);
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
            player.addAccelerationStraight(-4);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.addAccelerationSideways(4);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.addAccelerationSideways(-4);
        }

        if (enemies.size()<10)
        {
            enemies.emplace_back(Unit(sf::Vector2f(-2000 + rand() % 4000, -2000 + rand() % 4000), enemyTexture));
        }



        float mouseCenterOffset = sf::Mouse::getPosition(window).x - windowCenter.x;

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
            window.draw(*it);
            if((abs(abs(it->getPosition().x)-abs(player.getPosition().x)) > 2000) && (abs(abs(it->getPosition().y)-abs(player.getPosition().y)) > 2000))
            {
                //backgrounds.erase(it);
            }
        }




        for (auto it = bullets.begin(); it != bullets.end(); ++it)
        {
            it->first.update();
            window.draw(it->first);
            it->second++;
            if (it->second > 300) bullets.erase(it);
        }

        player.update();
        window.draw(player);

        for (auto it = enemies.begin(); it != enemies.end(); ++it)
        {
            //enemies.erase(it);
            float wantedRotation = atan2f(player.getPosition().y-it->getPosition().y, player.getPosition().x-it->getPosition().x) * 180 /M_PI + 90;
            float enemyRotation = it->getRotation();
            if (enemyRotation>180) enemyRotation = enemyRotation-360;
            if (wantedRotation>180) wantedRotation = wantedRotation-360;

            if (enemyRotation<wantedRotation) it->addTorque(3);
            else it->addTorque(-3);
            if ((abs(player.getPosition().y-it->getPosition().y) > 700) || (abs(player.getPosition().x-it->getPosition().x) > 700))
            {
                it->addAccelerationStraight(rand() % 9);
            }
            it->update();

            if (!(rand() % 30)) bullets.emplace_back(Bullet(*it,20,enemyBulletTexture),0);
            window.draw(*it);

        }


        window.display();



    }

    return 0;
}