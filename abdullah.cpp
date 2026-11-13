#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<optional>
using namespace std;

const int width=800;
const int height=600;
struct Bullet
{
    sf::RectangleShape shape;
    bool fromplayer;
};
struct Enemy
{
    sf::RectangleShape shape;
    bool alive;
};
void createEnemies(vector<Enemy>& enemies)
{
    enemies.clear();
    for(int row=0;row<3;row++)
    {
        for(int col=0;col<6;col++)
        {
            Enemy enemy;
            enemy.shape.setSize({40.f,30.f});
            enemy.shape.setFillColor(sf::Color::Green);
            enemy.shape.setPosition({100.f+col*90.f,70.f+row*55.f});
            enemy.alive=true;
            enemies.push_back(enemy);
        }
    }
}
void drawEnemies(sf::RenderWindow& window, vector<Enemy>&enemies)
{
   for (int i = 0; i<enemies.size(); i++)
   {
    if (enemies[i].alive)
    window.draw(enemies[i].shape);
   }
}
void moveEnemies(vector<Enemy>& enemies,float & direction)
{
    bool changeDirection = false;
    for (int i=0; i<enemies.size(); i++)
    {
        if (enemies[i].alive)
        {
            float x = enemies[i].shape.getPosition().x;
            if (x<=0 || x+40>=width)
            changeDirection = true;
        }
    }
    if (changeDirection)
    direction = - direction;
    for (int i=0; i<enemies.size(); i++)
    {
        if (enemies[i].alive)
        {
            enemies[i].shape.move({direction,0.5f});
        }
    }
}
void addPlayerBullet(vector<Bullet>& bullets,sf::RectangleShape & player)
{
    Bullet bullet;
    bullet.shape.setSize({5.f,15.f});
    bullet.shape.setFillColor(sf::Color::Yellow);
    bullet.shape.setPosition({player.getPosition().x+22.f,player.getPosition().y-15.f});
    bullet.fromplayer = true;
    bullets.push_back(bullet);
}
void addEnemyBullet(vector<Bullet>& bullets, vector<Enemy>& enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].alive)
        {
            Bullet bullet;
            bullet.shape.setSize({5.f, 15.f});
            bullet.shape.setFillColor(sf::Color::Red);
            bullet.shape.setPosition({ enemies[i].shape.getPosition().x + 18.f,
                enemies[i].shape.getPosition().y + 30.f});
            bullet.fromplayer = false;
            bullets.push_back(bullet);
            break;
        }
    }
}
void moveBullets(vector<Bullet>& bullets)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].fromplayer)
        bullets[i].shape.move({0.f, -7.f});
        else
            bullets[i].shape.move({0.f, 5.f});
    }
}
void drawBullets(sf::RenderWindow& window, vector<Bullet>& bullets)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        window.draw(bullets[i].shape);
    }
}