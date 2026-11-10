#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<optional>
using namespace std;
const int width = 800;
const int height = 600;
struct Bullet
{
    sf::rectangleshape shape;
    bool fromplayer;
};
struct Enemy
{
    sf::rectangleshape shape;
    bool alive;
};
void createEnemies(vector<enemy>& enemies)
{
    enemies.clear();
    for (int row=0; row<3; row++)
    {
            for (int col=0; col<6; col++)
            {
                Enemy enemy;
                enemy.shape.setSize({40.f,30.f});
                enemy.shape.setFillColour(sf::Color::Green);
                enemy.shape.setPosition({100.f+col*90.f,70.f + row*55.f});
                enemy.alive = true;
                enemies.push_back(enemy);
            }
    }
}