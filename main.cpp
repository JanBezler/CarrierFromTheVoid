#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Unit.h"
#include "Bullet.h"
#include "Background.h"
#include <iostream>
#include <algorithm>
#include "Animation.h"


#pragma region enumsAndStructures

enum shipType
{
    light,
    medium,
    heavy,
    boss,
    player
};

struct bulletElement
{
    Bullet bullet;
    int clock;
    shipType type;
};

struct shipElement
{
    Unit unit;
    int hp;
    shipType type;
};

#pragma endregion

#pragma region additionalFunctions

bool collisionDetectionBullet(shipElement &sel, bulletElement &bel)
{
    float distance = sqrtf(powf(bel.bullet.getPosition().x - sel.unit.getPosition().x, 2) + powf(bel.bullet.getPosition().y - sel.unit.getPosition().y, 2));
    if (((distance > 0) & (distance < 2000)) & (distance < sel.unit.getRadius()))
    {
        return true;
    }
    return false;
}

void bulletsErasingOrDrawing(std::vector<bulletElement> &vbel, sf::RenderWindow &w)
{
    vbel.erase(std::remove_if(vbel.begin(),vbel.end(),[](bulletElement b){return b.clock>300;}),vbel.end());
    for(auto &b : vbel)
    {
        b.bullet.update();
        b.clock++;
        w.draw(b.bullet);
    }

}

#pragma endregion

int main()
{
    int enemiesSpawned = 0;
    bool readyToShoot = true;
    int powerUpTimer = 0;
    std::vector<sf::Texture> blowUpTextures;
    std::vector<bulletElement> enemyBullets;
    std::vector<bulletElement> playerBullets;
    std::vector<Background> backgrounds;
    std::vector<shipElement> enemies;
    std::vector<Animation> animations;


#pragma region loadingAssets

    for (int i = 0; i<=7; i++)
    {
        blowUpTextures.emplace_back(sf::Texture());
        if (!blowUpTextures[i].loadFromFile("assets/Textures/BlowUp/expl" + std::to_string(i+1) + ".png"))
        {
            std::cout << "Could not load blowUpTexture" + std::to_string(i+1) + " texture";
            return 0;
        }
        blowUpTextures[i].setSmooth(true);
    }


    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/Textures/playerShip1_blue.png"))
    {
        std::cout << "Could not load playerTexture texture";
        return 0;
    }
    playerTexture.setSmooth(true);

    sf::Texture enemy1Texture;
    if (!enemy1Texture.loadFromFile("assets/Textures/Enemies/enemyRed1.png"))
    {
        std::cout << "Could not load enemy1Texture texture";
        return 0;
    }
    enemy1Texture.setSmooth(true);

    sf::Texture enemy2Texture;
    if (!enemy2Texture.loadFromFile("assets/Textures/Enemies/enemyRed3.png"))
    {
        std::cout << "Could not load enemy2Texture texture";
        return 0;
    }
    enemy2Texture.setSmooth(true);

    sf::Texture enemy3Texture;
    if (!enemy3Texture.loadFromFile("assets/Textures/Enemies/enemyRed5.png"))
    {
        std::cout << "Could not load enemy3Texture texture";
        return 0;
    }
    enemy3Texture.setSmooth(true);

    sf::Texture bossTexture;
    if (!bossTexture.loadFromFile("assets/Textures/Enemies/boss.png"))
    {
        std::cout << "Could not load bossTexture texture";
        return 0;
    }
    bossTexture.setSmooth(true);

    sf::Texture playerBulletTexture;
    if (!playerBulletTexture.loadFromFile("assets/Textures/Lasers/laserBlue01.png"))
    {
        std::cout << "Could not load playerBulletTexture texture";
        return 0;
    }
    playerBulletTexture.setSmooth(true);

    sf::Texture enemyBullet1Texture;
    if (!enemyBullet1Texture.loadFromFile("assets/Textures/Lasers/laserRed07.png"))
    {
        std::cout << "Could not load enemyBullet1Texture texture";
        return 0;
    }
    enemyBullet1Texture.setSmooth(true);

    sf::Texture enemyBullet2Texture;
    if (!enemyBullet2Texture.loadFromFile("assets/Textures/Lasers/laserRed01.png"))
    {
        std::cout << "Could not load enemyBullet2Texture texture";
        return 0;
    }
    enemyBullet2Texture.setSmooth(true);

    sf::Texture enemyBullet3Texture;
    if (!enemyBullet3Texture.loadFromFile("assets/Textures/Lasers/laserRed16.png"))
    {
        std::cout << "Could not load enemyBullet3Texture texture";
        return 0;
    }
    enemyBullet3Texture.setSmooth(true);

    sf::Texture enemyBulletBossTexture;
    if (!enemyBulletBossTexture.loadFromFile("assets/Textures/Lasers/laserRedBoss.png"))
    {
        std::cout << "Could not load enemyBulletBossTexture texture";
        return 0;
    }
    enemyBulletBossTexture.setSmooth(true);

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

    sf::Music enemyExplosionSound;
    if (!enemyExplosionSound.openFromFile("assets/Sound/sfx_explosion2.ogg"))
    {
        std::cout << "Could not load enemyExplosionSound sound";
        return 0;
    }

    sf::Font font;
    if (!font.loadFromFile("assets/kenvector_future_thin.ttf"))
    {
        std::cout << "Could not load font";
        return 0;
    }

#pragma endregion

    shipElement player = shipElement{Unit(sf::Vector2f(0, 0), playerTexture),360,shipType::player};

#pragma region setUpWindowView

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    sf::RenderWindow window(sf::VideoMode(), "CarrierFromTheVoid", sf::Style::Fullscreen, settings);
    window.setMouseCursorVisible(false);


    window.setFramerateLimit(60);

    sf::Vector2i windowCenter {static_cast<int>(window.getSize().x/2),static_cast<int>(window.getSize().y/2)};

    sf::View view;

    float zoom = 0 ;

    view.reset(sf::FloatRect(0.f*zoom, 0.f*zoom, 1920.f*(zoom+1), 1080.f*(zoom+1)));

    sf::Mouse::setPosition(windowCenter, window);

    float playerCameraOffset = 300;
    view.setCenter(player.unit.getPosition().x , player.unit.getPosition().y-playerCameraOffset);

#pragma endregion

#pragma region setHealthBar

    sf::Vector2f healthBarPosition {160 * (3 * zoom+1),850 * (zoom+1)};
    sf::RectangleShape healthBar = sf::RectangleShape(sf::Vector2f(20 * (zoom+1),360 * (zoom+1)));
    sf::RectangleShape healthStatus = sf::RectangleShape();
    healthBar.setOrigin(healthBarPosition);
    healthBar.setOutlineColor(sf::Color(20,20,20,180));
    healthBar.setFillColor(sf::Color(30,30,30,160));
    healthBar.setOutlineThickness(4 * (zoom+1));
    healthStatus.setFillColor(sf::Color(250,30,50,180));
    healthStatus.setOrigin(healthBarPosition);

#pragma endregion

#pragma region backgroundGeneration

    float squaresAroundPlayer = (zoom+1);
    float borderDistance = squaresAroundPlayer * 4000 + 2000;

    sf::RectangleShape border = sf::RectangleShape(sf::Vector2f(borderDistance + 200, borderDistance + 200));
    border.setOutlineThickness(30);
    border.setOutlineColor(sf::Color(32,35,41));
    border.setFillColor(sf::Color::Transparent);
    border.setPosition(-borderDistance/2,-borderDistance/2);

    for (int i=-2000*squaresAroundPlayer; i<=2000*squaresAroundPlayer; i+=2000)
    {
        for (int j=-2000*squaresAroundPlayer; j<=2000*squaresAroundPlayer; j+=2000)
        {
            backgrounds.emplace_back(Background(sf::Vector2f(i,j),backgroundTexture));
        }
    }

#pragma endregion

    while (window.isOpen())
    {

#pragma region keypressAndEvents

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (readyToShoot)
            {
                bulletSound.stop();
                playerBullets.emplace_back(bulletElement{Bullet(player.unit.getPosition(), player.unit.getRotation(), 20, playerBulletTexture),0,shipType::player});
                playerBullets.emplace_back(bulletElement{Bullet(player.unit.getPosition(), player.unit.getRotation(), 20, playerBulletTexture),0,shipType::player});
                playerBullets.emplace_back(bulletElement{Bullet(player.unit.getPosition(), player.unit.getRotation(), 20, playerBulletTexture),0,shipType::player});
                playerBullets.emplace_back(bulletElement{Bullet(player.unit.getPosition(), player.unit.getRotation(), 20, playerBulletTexture),0,shipType::player});
                bulletSound.play();

                //readyToShoot = false;
            }
        }
        else readyToShoot = true;


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            player.unit.addAccelerationStraight(7);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.unit.addAccelerationStraight(-4);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.unit.addAccelerationSideways(4);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.unit.addAccelerationSideways(-4);
        }

#pragma endregion

#pragma region mouseSteering

        float mouseCenterOffset = sf::Mouse::getPosition(window).x - windowCenter.x;

        player.unit.addTorque(mouseCenterOffset/70);

        if (mouseCenterOffset > 0)
        {
            if (mouseCenterOffset > 222)
            {
                sf::Mouse::setPosition(sf::Vector2i(windowCenter.x+222,window.getSize().y/2), window);
            }
            else
            {
                sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(window).x-3-mouseCenterOffset/60,window.getSize().y/2), window);
            }
        }
        if (mouseCenterOffset < 0)
        {
            if (mouseCenterOffset < -222)
            {
                sf::Mouse::setPosition(sf::Vector2i(windowCenter.x-222,window.getSize().y/2), window);
            }
            else
            {
                sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(window).x+3-mouseCenterOffset/60,window.getSize().y/2), window);
            }
        }
        mouseCenterOffset = 0;

#pragma endregion

#pragma region cameraMovement

        float angle = player.unit.getRotation() - view.getRotation() ;
        sf::Vector2f deltaPosition = player.unit.getPosition() - view.getCenter();

        view.move(deltaPosition.x  - playerCameraOffset*sin(-angle * M_PI / 180.0), deltaPosition.y  - playerCameraOffset*cos(-angle * M_PI / 180.0));

        float oldrotation = view.getRotation();
        view.setRotation(player.unit.getRotation());

        window.setView(view);
        view.setRotation(oldrotation);

#pragma endregion

#pragma region backgroundUpdate

        window.clear(sf::Color(42,45,51));
        window.draw(border);
        for (auto &bg : backgrounds) window.draw(bg);

        for (auto ita = animations.begin(); ita != animations.end(); ++ita)
        {
            ita->update();
            if (ita->getCounter()>0)
            {
                window.draw(*ita);
            }
            else if ((animations.size()>1) && (ita->getCounter()<0))
            {
                ita = animations.erase(ita);
            }
        }


#pragma endregion

#pragma region healthBarUpdate

        for (auto itb = enemyBullets.begin(); itb != enemyBullets.end(); ++itb)
        {
            if (collisionDetectionBullet(player,*itb))
            {
                itb->bullet.setPosition(player.unit.getPosition() + sf::Vector2f(9999,9999));
                itb->clock = 270;
                switch (itb->type)
                {
                    case shipType::light: {player.hp -= 10; break;}
                    case shipType::medium: {player.hp -= 16; break;}
                    case shipType::heavy: {player.hp -= 30; break;}
                    case shipType::boss: {player.hp -= 70; break;}
                }

            }
        }

        if ((player.unit.right()>border.getGlobalBounds().left + border.getGlobalBounds().width) ||
                (player.unit.bottom()>border.getGlobalBounds().top + border.getGlobalBounds().height) ||
                (player.unit.left()<border.getGlobalBounds().left || player.unit.top()<border.getGlobalBounds().top))
        {
            player.hp--;
        }


        if (player.hp<0)
        {
            player.hp = 0;
            enemyExplosionSound.stop();
            enemyExplosionSound.setVolume(100);
            animations.emplace_back(player.unit.getPosition(),0.76f,2,blowUpTextures);
            enemyExplosionSound.play();
        }
        healthBar.setRotation(player.unit.getRotation()-90);
        healthBar.setPosition(player.unit.getPosition());
        healthStatus.setSize(sf::Vector2f(20 * (zoom+1),player.hp * (zoom+1)));
        healthStatus.setRotation(player.unit.getRotation()-90);
        healthStatus.setPosition(player.unit.getPosition());

#pragma endregion

#pragma region enemySpawning

        if (enemies.size()<6)
        {
            int temp_random =1+ rand() % 101;
            if (temp_random < 32) {
                enemies.emplace_back(shipElement{Unit(player.unit.getPosition() +
                                                      sf::Vector2f(-3000 * (zoom + 1) + rand() % 6000 * (zoom + 1),
                                                                   -3000 * (zoom + 1) + rand() % 6000 * (zoom + 1)),
                                                      enemy1Texture), 30, shipType::light});
            }
            else if (temp_random < 70) {
                enemies.emplace_back(shipElement{Unit(player.unit.getPosition() +
                                                      sf::Vector2f(-3000 * (zoom + 1) + rand() % 6000 * (zoom + 1),
                                                                   -3000 * (zoom + 1) + rand() % 6000 * (zoom + 1)),
                                                      enemy2Texture), 40, shipType::medium});
            }
            else {
                enemies.emplace_back(shipElement{Unit(player.unit.getPosition() +
                                                      sf::Vector2f(-3000 * (zoom + 1) + rand() % 6000 * (zoom + 1),
                                                                   -3000 * (zoom + 1) + rand() % 6000 * (zoom + 1)),
                                                      enemy3Texture), 60, shipType::heavy});
            }
            enemiesSpawned++;

            if (enemiesSpawned % 10 == 0) {
                enemies.emplace_back(shipElement{Unit(player.unit.getPosition() +
                                                      sf::Vector2f(-3000 * (zoom + 1) + rand() % 6000 * (zoom + 1),
                                                                   -3000 * (zoom + 1) + rand() % 6000 * (zoom + 1)),
                                                      bossTexture), 200, shipType::boss});
            }
        }



#pragma endregion

#pragma region enemyUpdate

        for (auto it = enemies.begin(); it != enemies.end(); ++it)
        {
            float wantedRotation = atan2f(player.unit.getPosition().y-it->unit.getPosition().y, player.unit.getPosition().x-it->unit.getPosition().x) * 180 /M_PI + 90;
            float enemyRotation = it->unit.getRotation();
            if (enemyRotation>180)
            {
                enemyRotation = enemyRotation-360;
            }
            if (wantedRotation>180)
            {
                wantedRotation = wantedRotation-360;
            }
            float explodeSize;

            switch (it->type) {
                case shipType::light:
                {
                    if (enemyRotation<wantedRotation)
                    {
                        it->unit.addTorque(5);
                    }
                    else
                    {
                        it->unit.addTorque(-5);
                    }
                    if ((abs(player.unit.getPosition().y-it->unit.getPosition().y) > 500) || (abs(player.unit.getPosition().x-it->unit.getPosition().x) > 500))
                    {
                        it->unit.addAccelerationStraight(rand() % 20);
                    }
                    if (!(rand() % 33))
                    {
                        enemyBulletSound.stop();
                        enemyBullets.emplace_back(bulletElement{Bullet(it->unit.getPosition(), it->unit.getRotation(), 20, enemyBullet1Texture),250, shipType::light});
                        enemyBulletSound.play();
                    }
                    explodeSize = 1.4;

                    break;
                }
                case shipType::medium:
                {
                    if (enemyRotation<wantedRotation)
                    {
                        it->unit.addTorque(3);
                    }
                    else
                    {
                        it->unit.addTorque(-3);
                    }
                    if ((abs(player.unit.getPosition().y-it->unit.getPosition().y) > 640) || (abs(player.unit.getPosition().x-it->unit.getPosition().x) > 640))
                    {
                        it->unit.addAccelerationStraight(rand() % 12);
                    }
                    if (!(rand() % 45))
                    {
                        enemyBulletSound.stop();
                        enemyBullets.emplace_back(bulletElement{Bullet(it->unit.getPosition(), it->unit.getRotation(), 11, enemyBullet2Texture),160, shipType::medium});
                        enemyBulletSound.play();
                    }
                    explodeSize = 1.9;
                    break;
                }
                case shipType::heavy:
                {
                    if (enemyRotation<wantedRotation)
                    {
                        it->unit.addTorque(1);
                    }
                    else
                    {
                        it->unit.addTorque(-1);
                    }
                    if ((abs(player.unit.getPosition().y-it->unit.getPosition().y) > 800) || (abs(player.unit.getPosition().x-it->unit.getPosition().x) > 800))
                    {
                        it->unit.addAccelerationStraight(rand() % 8);
                    }
                    if (!(rand() % 90))
                    {
                        enemyBulletSound.stop();
                        enemyBullets.emplace_back(bulletElement{Bullet(it->unit.getPosition(), it->unit.getRotation(), 10, enemyBullet3Texture),0, shipType::heavy});
                        enemyBulletSound.play();
                    }
                    explodeSize = 2.4;
                    break;
                }
                case shipType::boss:
                {
                    if (enemyRotation<wantedRotation)
                    {
                        it->unit.addTorque(0.5);
                    }
                    else
                    {
                        it->unit.addTorque(-0.5);
                    }
                    if ((abs(player.unit.getPosition().y-it->unit.getPosition().y) > 800) || (abs(player.unit.getPosition().x-it->unit.getPosition().x) > 800))
                    {
                        it->unit.addAccelerationStraight(rand() % 4);
                    }
                    if (!(rand() % 100))
                    {
                        enemyBulletSound.stop();
                        enemyBullets.emplace_back(bulletElement{Bullet(it->unit.getPosition(), it->unit.getRotation(), 6, enemyBulletBossTexture),0, shipType::boss});
                        enemyBulletSound.play();

                    }
                    explodeSize = 4;
                    break;
                }
            }
            enemyBulletSound.setVolume(explodeSize*25/2 +50);
            it->unit.update();

            for (auto itb = playerBullets.begin(); itb != playerBullets.end(); ++itb) {

                if (collisionDetectionBullet(*it,*itb))
                {
                    it->hp -= 10;
                    if (it->hp <= 0)
                    {
                        enemyExplosionSound.stop();
                        enemyExplosionSound.setVolume(explodeSize*25);
                        animations.emplace_back(it->unit.getPosition(),0.76f,explodeSize,blowUpTextures);
                        enemyExplosionSound.play();
                        it = enemies.erase(it);
                    }

                    itb->bullet.setPosition(player.unit.getPosition() + sf::Vector2f(9999,9999));
                    itb->clock = 200;
                }
            }
        }

        for (auto &enemy : enemies)
        {
            window.draw(enemy.unit);
        }

#pragma endregion

        bulletsErasingOrDrawing(playerBullets, window);
        bulletsErasingOrDrawing(enemyBullets, window);

        player.unit.update();
        window.draw(player.unit);

        window.draw(healthBar);
        window.draw(healthStatus);


        window.draw(sf::Text("21:37",font,30));

        window.display();

    }

    return 0;
}