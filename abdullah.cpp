#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<optional>
#include<fstream>
#include<string>
#include<SFML/Audio.hpp>
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
sf::SoundBuffer shootBuffer;
sf::SoundBuffer explosionBuffer;
sf::SoundBuffer hitBuffer;
sf::SoundBuffer gameoverBuffer;

sf::Sound shootSound(shootBuffer);
sf::Sound explosionSound(explosionBuffer);
sf::Sound hitSound(hitBuffer);
sf::Sound gameoverSound(gameoverBuffer);
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
void checkCollisions(vector<Bullet>& bullets, vector<Enemy>& enemies, sf::RectangleShape& player, int& score, int& lives)
{
    for (int i = (int)bullets.size() - 1; i >= 0; i--)
    {
        bool bulletRemoved = false;
        if (bullets[i].fromplayer)
        {
            for (int j = 0; j < enemies.size(); j++)
            {
                if (enemies[j].alive && bullets[i].shape.getGlobalBounds().findIntersection
                ( enemies[j].shape.getGlobalBounds()))
                {
                    enemies[j].alive = false;
                    score += 10;
                    explosionSound.play();
                    bullets.erase(bullets.begin() + i);
                    bulletRemoved = true;
                    break;
                }
            }
        }
        if (!bulletRemoved && i < bullets.size())
        {
            if (!bullets[i].fromplayer && bullets[i].shape.getGlobalBounds().findIntersection(
                    player.getGlobalBounds()))
            {
                lives--;
                hitSound.play();
                bullets.erase(bullets.begin() + i);
            }
        }
    }
}
int countEnemies(vector<Enemy>& enemies)
{
    int count = 0;
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].alive)
            count++;
    }
    return count;
}
struct scoreentry
{
    string name;
    int score;
};
void loadSounds()
{
    shootBuffer.loadFromFile("sounds/shoot.wav");
    explosionBuffer.loadFromFile("sounds/explosion.wav");
    hitBuffer.loadFromFile("sounds/hit.wav");
    gameoverBuffer.loadFromFile("sounds/gameover.wav");
}
void sortleaderboard(vector<scoreentry>& scores)
{
    for (int i = 0; i < (int)scores.size() - 1; i++)
    {
        for (int j = 0; j < (int)scores.size() - i - 1; j++)
        {
            if (scores[j].score < scores[j + 1].score)
            {
                scoreentry temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
}
void loadleaderboard(vector<scoreentry>& scores)
{
    scores.clear();
    ifstream file("leaderboard.txt");
    string line;
    while(getline(file,line))
    {
        scoreentry entry;
        entry.score=0;
        entry.name="";
        int i=0;
        while(line[i]!=' ' && line[i]!='\0')
        {
            entry.score=entry.score*10+(line[i]-'0');
            i++;
        }
        if(line[i]==' ')
        {
            i++;
            entry.name="";
            while(line[i]!='\0')
            {
                entry.name+=line[i];
                i++;
            }
        }
        if(entry.name!="")
            scores.push_back(entry);
    }
    file.close();
    sortleaderboard(scores);
}
void savecore(const string& name, int score)
{
    ofstream file("leaderboard.txt", ios::app);

    if (file.is_open())
    {
        file << score << " " << name << endl;
        file.close();
    }
    else
    {
        cout << "Could not save leaderboard file!" << endl;
    }
}
bool enemyreachedplayer(vector<Enemy>& enemies, sf::RectangleShape& player)
{
    for(int i=0;i<enemies.size();i++)
    {
        if(enemies[i].alive)
        {
            if(enemies[i].shape.getGlobalBounds().findIntersection(
                player.getGlobalBounds()))
            {
                return true;
            }
        }
    }
    return false;
}