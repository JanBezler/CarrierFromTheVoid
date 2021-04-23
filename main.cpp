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
    if (!backgroundTexture.loadFromFile("assets/Textures/Backgrounds/blue.png"))
    {
        std::cout << "Could not load bullet texture";
        return 0;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    Unit player = Unit(sf::Vector2f(200, 200), shipTexture);


    float playerCameraOffset = 320;
    view.setCenter(player.getPosition().x , player.getPosition().y-playerCameraOffset);


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



        float angle = player.getRotation() - view.getRotation() ;
        sf::Vector2f deltaPosition = player.getPosition() - view.getCenter();

        view.move(deltaPosition.x  - playerCameraOffset*sin(-angle * M_PI / 180.0), deltaPosition.y  - playerCameraOffset*cos(-angle * M_PI / 180.0));

        float oldrotation = view.getRotation();
        view.setRotation(player.getRotation());



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            if (readyToShoot)
            {
                bullets.emplace_back(Bullet(player, 15, bulletTexture));
                readyToShoot = false;
            }
        }
        else readyToShoot = true;


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.addTorque(4);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.addTorque(-4);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            player.addAccelerationStraight(7);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.addAccelerationStraight(-7);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
        {
            player.addAccelerationSideways(3);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            player.addAccelerationSideways(-3);
        }

        window.setView(view);

        view.setRotation(oldrotation);
        window.clear();

        unsigned int backgroundSize = 256;

        for (unsigned int i=0; i<static_cast<int>(window.getSize().x/backgroundSize)+1; i+=backgroundSize)
        {
            for (unsigned int j=0; j<static_cast<int>(window.getSize().y/backgroundSize)+1; j+=backgroundSize)
            {
                backgroundSprite.setPosition(view.getCenter()+sf::Vector2f<unsigned int>(i,j))
                window.draw(backgroundSprite);
            }
        }



        player.update();
        window.draw(player);

        for (auto& bullet : bullets)
        {
            bullet.update();
            window.draw(bullet);
        }

        window.display();
    }

    return 0;
}