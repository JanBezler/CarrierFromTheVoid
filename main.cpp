#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"
#include "Background.h"
#include <iostream>
#include <stdlib.h>

enum unitType
{
    Player,
    Enemy,
    Neutral
};

enum enemyType
{
    light,
    medium,
    heavy
};

struct bulletElement
{
    Bullet bullet;
    int clock;
    unitType ownerType;
};

struct enemyElement
{
    Unit unit;
    int hp;
    enemyType type;
};



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


    sf::RectangleShape healthBar = sf::RectangleShape(sf::Vector2f(20,360));
    sf::RectangleShape healthStatus = sf::RectangleShape(sf::Vector2f(20,360));
    healthBar.setOrigin(160,850);
    healthBar.setOutlineColor(sf::Color(20,20,20,180));
    healthBar.setFillColor(sf::Color(30,30,30,160));
    healthBar.setOutlineThickness(4);
    healthStatus.setFillColor(sf::Color(250,30,50,180));
    healthStatus.setOrigin(160,850);

    float healthPoints = 360;

    sf::Texture shipTexture;
    if (!shipTexture.loadFromFile("assets/Textures/playerShip1_blue.png"))
    {
        std::cout << "Could not load shipTexture texture";
        return 0;
    }
    shipTexture.setSmooth(true);

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("assets/Textures/Enemies/enemyRed5.png"))
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

    sf::Music bulletSound;
    if (!bulletSound.openFromFile("assets/Sound/sfx_laser1.ogg"))
    {
        std::cout << "Could not load bulletSound sound";
        return 0;
    }

    sf::Music enemyBulletSound;
    if (!enemyBulletSound.openFromFile("assets/Sound/sfx_laser2.ogg"))
    {
        std::cout << "Could not load enemyBulletSound sound";
        return 0;
    }


    Unit player = Unit(sf::Vector2f(0, 0), shipTexture);




    float playerCameraOffset = 300;
    view.setCenter(player.getPosition().x , player.getPosition().y-playerCameraOffset);


    std::vector<bulletElement> bullets;
    std::vector<Background> backgrounds;
    std::vector<enemyElement> enemies;

    float squaresAroundPlayer = 1;

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            if (readyToShoot)
            {
                bulletSound.stop();
                bullets.emplace_back(bulletElement{Bullet(player, 20, playerBulletTexture),0,unitType::Player});
                bulletSound.play();


                readyToShoot = false;
            }
        }
        else readyToShoot = true;


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
            enemies.emplace_back(enemyElement{Unit(sf::Vector2f(-2000 + rand() % 4000, -2000 + rand() % 4000), enemyTexture),30,enemyType::medium});
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


        float angle = player.getRotation() - view.getRotation() ;
        sf::Vector2f deltaPosition = player.getPosition() - view.getCenter();

        view.move(deltaPosition.x  - playerCameraOffset*sin(-angle * M_PI / 180.0), deltaPosition.y  - playerCameraOffset*cos(-angle * M_PI / 180.0));

        float oldrotation = view.getRotation();
        view.setRotation(player.getRotation());


        if (healthPoints<0) healthPoints = 0;
        healthBar.setRotation(player.getRotation()-90);
        healthBar.setPosition(player.getPosition());
        healthStatus.setSize(sf::Vector2f(20,healthPoints));
        healthStatus.setRotation(player.getRotation()-90);
        healthStatus.setPosition(player.getPosition());


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
            it->bullet.update();
            window.draw(it->bullet);
            it->clock++;
            if (it->clock > 300) it = bullets.erase(it);
        }

        player.update();
        window.draw(player);


        for (auto it = enemies.begin(); it != enemies.end(); ++it)
        {
            float wantedRotation = atan2f(player.getPosition().y-it->unit.getPosition().y, player.getPosition().x-it->unit.getPosition().x) * 180 /M_PI + 90;
            float enemyRotation = it->unit.getRotation();
            if (enemyRotation>180) enemyRotation = enemyRotation-360;
            if (wantedRotation>180) wantedRotation = wantedRotation-360;

            if (enemyRotation<wantedRotation) it->unit.addTorque(3);
            else it->unit.addTorque(-3);
            if ((abs(player.getPosition().y-it->unit.getPosition().y) > 600) || (abs(player.getPosition().x-it->unit.getPosition().x) > 600))
            {
                it->unit.addAccelerationStraight(rand() % 6);
            }
            it->unit.update();

            if (!(rand() % 50))
            {
                enemyBulletSound.stop();
                bullets.emplace_back(bulletElement{Bullet(it->unit, 20, enemyBulletTexture),0,unitType::Enemy});

                enemyBulletSound.play();
            }
            window.draw(it->unit);



                for (auto itb = bullets.begin(); itb != bullets.end(); ++itb) {

                    if (itb->ownerType == unitType::Player) {
                        float distance = sqrtf(powf(itb->bullet.getPosition().x - it->unit.getPosition().x, 2) +
                                               powf(itb->bullet.getPosition().y - it->unit.getPosition().y, 2));
                        if ((distance > 0) && (distance < 2000)) {
                            if (distance < it->unit.getRadius()) {
                                it->hp -= 10;
                                if (it->hp <= 0)
                                {
                                    it->unit.setPosition(player.getPosition() + sf::Vector2f(-2000 + rand() % 4000, -2000 + rand() % 4000));
                                    it->hp = 30;
                                }
                                //itb = bullets.erase(itb);
                                it = enemies.erase(it);
                                //itb->bullet.setPosition(player.getPosition() + sf::Vector2f(9999,9999));
                                //itb->clock = 200;


                            }
                        }

                    }
                }
        }


        window.draw(healthBar);
        window.draw(healthStatus);

        window.display();



    }

    return 0;
}