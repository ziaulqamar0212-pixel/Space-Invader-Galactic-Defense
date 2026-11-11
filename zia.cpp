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
}