#include <SFML/Graphics.hpp>
#include<iostream>
const int WIDTH = 800;
const int HEIGHT = 600;
void drawPlayer(sf::RenderWindow& window,sf::RectangleShape&player)
{
    window.draw(player);
}
void movePlayer(sf::RectangleShape& player)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if(player.getPosition().x>0)
        player.move({-5.f,0.f});
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if(player.getPosition().x+50<800)
            player.move({5.f,0.f});
    }
}
int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH,HEIGHT}),"Space Invaders Test");
    window.setFramerateLimit(60);
    sf::Font font;
    if(!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout<<"Font Could Not Be Loaded! "<<std::endl;
        return 1;
}
sf::RectangleShape player({50.f,30.f});
    player.setFillColor(sf::Color::Cyan);
    player.setPosition({375.f,540.f});
    
   std::vector<Enemy> enemies;
   std:: vector<Bullet> bullets;

    createEnemies(enemies);

    int score=0;
    int lives=3;

    float enemyDirection=2.f;
    bool gameOver=false;

    sf::Clock playerShootClock;
    sf::Clock enemyShootClock;

    sf::Text scoreText(font, "Score: 0", 24);
    sf::Text livesText(font, "Lives: 3", 24);
    sf::Text gameOverText(font,"Game Over - Press R to Resart",30);

    scoreText.setPosition({20.5,15.f});
    livesText.setPosition({680.f,15.f});
    gameOverText.setPosition({150.f,270.f});

    while(window.isOpen())
    {
        while(const optional event =window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        if(!gameOver)
        {
            movePlayer(player);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                if(playerShootClock.getElapsedTime().asSeconds()>0.35f)
                {
                    addPlayerBullet(bullets, player);
                    playerShootClock.restart();
                }
            }
            if(enemyShootClock.getElapsedTime().asSeconds()>1.2f)
            {
                addEnemyBullet(bullets, enemies);
                enemyShootClock.restart();
            }
        

            moveEnemies(enemies, enemyDirection);
            moveBullets(bullets);

            checkCollisions(
                bullets,
                enemies,
                player,
                score,
                lives
            );

            if (countEnemies(enemies) == 0)
            {
                createEnemies(enemies);
            }

            if (lives <= 0)
            {
                gameOver = true;
            }

            for (int i = (int)bullets.size() - 1; i >= 0; i--)
            {
                float y = bullets[i].shape.getPosition().y;

                if (y < 0 || y > HEIGHT)
                {
                    bullets.erase(bullets.begin() + i);
                }
            }
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(
                sf::Keyboard::Key::R))
            {
                score = 0;
                lives = 3;
                gameOver = false;

                bullets.clear();
                createEnemies(enemies);

                player.setPosition({375.f, 540.f});
                enemyDirection = 2.f;
            }
        }

        scoreText.setString("Score: " + to_string(score));
        livesText.setString("Lives: " + to_string(lives));

        window.clear(sf::Color::Black);

        drawPlayer(window, player);
        drawEnemies(window, enemies);
        drawBullets(window, bullets);

        window.draw(scoreText);
        window.draw(livesText);

        if (gameOver)
        {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
