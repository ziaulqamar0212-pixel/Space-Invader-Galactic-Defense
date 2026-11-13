#include <SFML/Graphics.hpp>

#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

struct Bullet
{
    sf::RectangleShape shape;
    bool fromPlayer;
};

struct Enemy
{
    sf::RectangleShape shape;
    bool alive;
};

void createEnemies(vector<Enemy>& enemies)
{
    enemies.clear();
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 6; col++)
        {
            Enemy enemy;
            enemy.shape.setSize({40.f, 30.f});
            enemy.shape.setFillColor(sf::Color::Green);
            enemy.shape.setPosition({100.f + col * 90.f, 70.f + row * 55.f});
            enemy.alive = true;
            enemies.push_back(enemy);
        }
    }
}

void drawEnemies(sf::RenderWindow& window, vector<Enemy>& enemies)
{
    for (std::size_t i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].alive)
        {
            window.draw(enemies[i].shape);
        }
    }
}

void moveEnemies(vector<Enemy>& enemies, float& direction)
{
    bool changeDirection = false;
    for (std::size_t i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].alive)
        {
            float x = enemies[i].shape.getPosition().x;
            if (x <= 0 || x + 40 >= WIDTH)
            {
                changeDirection = true;
            }
        }
    }
    if (changeDirection)
    {
        direction = -direction;
    }
    for (std::size_t i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].alive)
        {
            enemies[i].shape.move({direction, 0.5f});
        }
    }
}

void addPlayerBullet(vector<Bullet>& bullets, sf::RectangleShape& player)
{
    Bullet bullet;
    bullet.shape.setSize({5.f, 15.f});
    bullet.shape.setFillColor(sf::Color::Yellow);
    bullet.shape.setPosition({player.getPosition().x + 22.f, player.getPosition().y - 15.f});
    bullet.fromPlayer = true;
    bullets.push_back(bullet);
}

void addEnemyBullet(vector<Bullet>& bullets, vector<Enemy>& enemies)
{
    for (std::size_t i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].alive)
        {
            Bullet bullet;
            bullet.shape.setSize({5.f, 15.f});
            bullet.shape.setFillColor(sf::Color::Red);
            bullet.shape.setPosition({
                enemies[i].shape.getPosition().x + 18.f,
                enemies[i].shape.getPosition().y + 30.f
            });
            bullet.fromPlayer = false;
            bullets.push_back(bullet);
            break;
        }
    }
}

void moveBullets(vector<Bullet>& bullets)
{
    for (std::size_t i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].fromPlayer)
        {
            bullets[i].shape.move({0.f, -7.f});
        }
        else
        {
            bullets[i].shape.move({0.f, 5.f});
        }
    }
}

void drawBullets(sf::RenderWindow& window, vector<Bullet>& bullets)
{
    for (std::size_t i = 0; i < bullets.size(); i++)
    {
        window.draw(bullets[i].shape);
    }
}

void checkCollisions(
    vector<Bullet>& bullets,
    vector<Enemy>& enemies,
    sf::RectangleShape& player,
    int& score,
    int& lives)
{
    for (int i = static_cast<int>(bullets.size()) - 1; i >= 0; i--)
    {
        bool bulletRemoved = false;
        if (bullets[i].fromPlayer)
        {
            for (std::size_t j = 0; j < enemies.size(); j++)
            {
                if (enemies[j].alive &&
                    bullets[i].shape.getGlobalBounds().findIntersection(
                        enemies[j].shape.getGlobalBounds()))
                {
                    enemies[j].alive = false;
                    score += 10;
                    bullets.erase(bullets.begin() + i);
                    bulletRemoved = true;
                    break;
                }
            }
        }
        if (!bulletRemoved && static_cast<std::size_t>(i) < bullets.size() &&
            !bullets[i].fromPlayer &&
            bullets[i].shape.getGlobalBounds().findIntersection(player.getGlobalBounds()))
        {
            lives--;
            bullets.erase(bullets.begin() + i);
        }
    }
}

int countEnemies(vector<Enemy>& enemies)
{
    int count = 0;
    for (std::size_t i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].alive)
        {
            count++;
        }
    }
    return count;
}

void drawPlayer(sf::RenderWindow& window, sf::RectangleShape& player)
{
    window.draw(player);
}

void movePlayer(sf::RectangleShape& player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) &&
        player.getPosition().x > 0)
    {
        player.move({-5.f, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
        player.getPosition().x + 50 < WIDTH)
    {
        player.move({5.f, 0.f});
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Space Invaders");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        cerr << "Font could not be loaded." << endl;
        return 1;
    }

    sf::RectangleShape player({50.f, 30.f});
    player.setFillColor(sf::Color::Cyan);
    player.setPosition({375.f, 540.f});

    vector<Enemy> enemies;
    vector<Bullet> bullets;
    createEnemies(enemies);

    int score = 0;
    int lives = 3;
    float enemyDirection = 2.f;
    bool gameOver = false;

    sf::Clock playerShootClock;
    sf::Clock enemyShootClock;

    sf::Text scoreText(font, "Score: 0", 24);
    sf::Text livesText(font, "Lives: 3", 24);
    sf::Text gameOverText(font, "Game Over - Press R to Restart", 30);

    scoreText.setPosition({20.5f, 15.f});
    livesText.setPosition({680.f, 15.f});
    gameOverText.setPosition({150.f, 270.f});

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (!gameOver)
        {
            movePlayer(player);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
                playerShootClock.getElapsedTime().asSeconds() > 0.35f)
            {
                addPlayerBullet(bullets, player);
                playerShootClock.restart();
            }
            if (enemyShootClock.getElapsedTime().asSeconds() > 1.2f)
            {
                addEnemyBullet(bullets, enemies);
                enemyShootClock.restart();
            }

            moveEnemies(enemies, enemyDirection);
            moveBullets(bullets);
            checkCollisions(bullets, enemies, player, score, lives);

            if (countEnemies(enemies) == 0)
            {
                createEnemies(enemies);
            }
            if (lives <= 0)
            {
                gameOver = true;
            }

            for (int i = static_cast<int>(bullets.size()) - 1; i >= 0; i--)
            {
                float y = bullets[i].shape.getPosition().y;
                if (y < 0 || y > HEIGHT)
                {
                    bullets.erase(bullets.begin() + i);
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        {
            score = 0;
            lives = 3;
            gameOver = false;
            bullets.clear();
            createEnemies(enemies);
            player.setPosition({375.f, 540.f});
            enemyDirection = 2.f;
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
