#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include <string>
#include <fstream>

using namespace std;

const int width=800;
const int height=600;

// ==========================================
// ABDULLAH'S CODE STARTS HERE
// ==========================================

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

struct ScoreEntry
{
    string name;
    int score;
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
    for(int i=0;i<enemies.size();i++)
    {
        if(enemies[i].alive)
            window.draw(enemies[i].shape);
    }
}

void moveEnemies(vector<Enemy>& enemies,float& direction)
{
    bool changeDirection=false;

    for(int i=0;i<enemies.size();i++)
    {
        if(enemies[i].alive)
        {
            float x=enemies[i].shape.getPosition().x;

            if(x<=0 || x+40>=width)
                changeDirection=true;
        }
    }

    if(changeDirection)
        direction=-direction;

    for(int i=0;i<enemies.size();i++)
    {
        if(enemies[i].alive)
        {
            enemies[i].shape.move({direction,0.5f});
        }
    }
}

void addPlayerBullet(vector<Bullet>& bullets,sf::RectangleShape& player)
{
    Bullet bullet;

    bullet.shape.setSize({5.f,15.f});
    bullet.shape.setFillColor(sf::Color::Yellow);
    bullet.shape.setPosition({
        player.getPosition().x+22.f,
        player.getPosition().y-15.f
    });

    bullet.fromplayer=true;
    bullets.push_back(bullet);
}

void addEnemyBullet(vector<Bullet>& bullets,vector<Enemy>& enemies)
{
    for(int i=0;i<enemies.size();i++)
    {
        if(enemies[i].alive)
        {
            Bullet bullet;

            bullet.shape.setSize({5.f,15.f});
            bullet.shape.setFillColor(sf::Color::Red);
            bullet.shape.setPosition({
                enemies[i].shape.getPosition().x+18.f,
                enemies[i].shape.getPosition().y+30.f
            });

            bullet.fromplayer=false;
            bullets.push_back(bullet);
            break;
        }
    }
}

void moveBullets(vector<Bullet>& bullets)
{
    for(int i=0;i<bullets.size();i++)
    {
        if(bullets[i].fromplayer)
            bullets[i].shape.move({0.f,-7.f});
        else
            bullets[i].shape.move({0.f,5.f});
    }
}

void drawBullets(sf::RenderWindow& window,vector<Bullet>& bullets)
{
    for(int i=0;i<bullets.size();i++)
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
    for(int i=(int)bullets.size()-1;i>=0;i--)
    {
        bool bulletRemoved=false;

        if(bullets[i].fromplayer)
        {
            for(int j=0;j<enemies.size();j++)
            {
                if(enemies[j].alive &&
                   bullets[i].shape.getGlobalBounds().findIntersection(
                       enemies[j].shape.getGlobalBounds()))
                {
                    enemies[j].alive=false;
                    score+=10;

                    bullets.erase(bullets.begin()+i);
                    bulletRemoved=true;
                    break;
                }
            }
        }

        if(!bulletRemoved && i<bullets.size())
        {
            if(!bullets[i].fromplayer &&
               bullets[i].shape.getGlobalBounds().findIntersection(
                   player.getGlobalBounds()))
            {
                lives--;
                bullets.erase(bullets.begin()+i);
            }
        }
    }
}

int countEnemies(vector<Enemy>& enemies)
{
    int count=0;

    for(int i=0;i<enemies.size();i++)
    {
        if(enemies[i].alive)
            count++;
    }

    return count;
}

// ==========================================
// NEW CODE: LEADERBOARD
// ==========================================

// Save player's name and score
void saveScore(string name,int score)
{
    ofstream file("leaderboard.txt",ios::app);

    if(file.is_open())
    {
        file<<name<<"|"<<score<<endl;
        file.close();
    }
}

// Load leaderboard and sort scores
vector<ScoreEntry> loadLeaderboard()
{
    vector<ScoreEntry> scores;

    ifstream file("leaderboard.txt");

    ScoreEntry entry;

    while(getline(file,entry.name,'|'))
    {
        if(file>>entry.score)
        {
            scores.push_back(entry);
            file.ignore();
        }
    }

    file.close();

    // Bubble Sort: Highest score first
    for(int i=0;i<(int)scores.size()-1;i++)
    {
        for(int j=0;j<(int)scores.size()-i-1;j++)
        {
            if(scores[j].score<scores[j+1].score)
            {
                ScoreEntry temp=scores[j];
                scores[j]=scores[j+1];
                scores[j+1]=temp;
            }
        }
    }

    return scores;
}

// ==========================================
// ABDULLAH'S CODE ENDS HERE
// ZIA'S CODE STARTS HERE
// ==========================================

void drawPlayer(sf::RenderWindow& window,sf::RectangleShape& player)
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
        if(player.getPosition().x+50<width)
            player.move({5.f,0.f});
    }
}

// ==========================================
// MAIN FUNCTION
// ==========================================

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({width,height}),
        "Space Invaders"
    );

    window.setFramerateLimit(60);

    sf::Font font;

    if(!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        cout<<"Font Could Not Be Loaded!"<<endl;
        return 1;
    }

    sf::RectangleShape player({50.f,30.f});
    player.setFillColor(sf::Color::Cyan);
    player.setPosition({375.f,540.f});

    vector<Enemy> enemies;
    vector<Bullet> bullets;

    createEnemies(enemies);

    int score=0;
    int lives=3;

    float enemyDirection=2.f;

    bool enteringName=true;
    bool gameOver=false;
    bool scoreSaved=false;

    string playerName="";

    sf::Clock playerShootClock;
    sf::Clock enemyShootClock;

    // ======================================
    // TEXT OBJECTS
    // ======================================

    sf::Text titleText(font,"SPACE INVADERS",40);
    sf::Text nameText(font,"Enter Your Name:",25);
    sf::Text instructionText(font,"HOW TO PLAY",24);
    sf::Text menuLeaderboardTitle(font,"TOP 5 LEADERBOARD",24);
    sf::Text startText(font,"Press ENTER to Start",22);

    sf::Text scoreText(font,"Score: 0",24);
    sf::Text livesText(font,"Lives: 3",24);

    sf::Text gameOverText(font,"GAME OVER",35);
    sf::Text restartText(font,"Press R to Restart",22);
    sf::Text leaderboardTitle(font,"TOP 5 LEADERBOARD",28);

    // ======================================
    // TEXT POSITIONS
    // ======================================

    titleText.setPosition({220.f,40.f});

    nameText.setPosition({50.f,150.f});
    instructionText.setPosition({50.f,260.f});
    startText.setPosition({50.f,220.f});

    menuLeaderboardTitle.setPosition({460.f,150.f});

    scoreText.setPosition({20.f,15.f});
    livesText.setPosition({680.f,15.f});

    gameOverText.setPosition({300.f,100.f});
    leaderboardTitle.setPosition({250.f,170.f});
    restartText.setPosition({290.f,520.f});

    // ======================================
    // GAME LOOP
    // ======================================

    while(window.isOpen())
    {
        while(const optional event=window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // ==================================
            // PLAYER NAME INPUT
            // ==================================

            if(enteringName)
            {
                if(const auto* key=
                    event->getIf<sf::Event::KeyPressed>())
                {
                    if(key->code==sf::Keyboard::Key::Enter &&
                       playerName.length()>0)
                    {
                        enteringName=false;
                    }

                    if(key->code==sf::Keyboard::Key::Backspace &&
                       playerName.length()>0)
                    {
                        playerName.pop_back();
                    }
                }

                if(const auto* text=
                    event->getIf<sf::Event::TextEntered>())
                {
                    if(text->unicode>=32 &&
                       text->unicode<=126 &&
                       playerName.length()<15)
                    {
                        playerName+=static_cast<char>(text->unicode);
                    }
                }
            }

            // ==================================
            // RESTART GAME
            // ==================================

            else if(gameOver)
            {
                if(const auto* key=
                    event->getIf<sf::Event::KeyPressed>())
                {
                    if(key->code==sf::Keyboard::Key::R)
                    {
                        score=0;
                        lives=3;
                        gameOver=false;
                        scoreSaved=false;

                        bullets.clear();
                        createEnemies(enemies);

                        player.setPosition({375.f,540.f});
                        enemyDirection=2.f;

                        playerShootClock.restart();
                        enemyShootClock.restart();
                    }
                }
            }
        }

        // ======================================
        // GAMEPLAY
        // ======================================

        if(!enteringName && !gameOver)
        {
            movePlayer(player);

            if(sf::Keyboard::isKeyPressed(
                sf::Keyboard::Key::Space))
            {
                if(playerShootClock.getElapsedTime().asSeconds()>0.35f)
                {
                    addPlayerBullet(bullets,player);
                    playerShootClock.restart();
                }
            }

            if(enemyShootClock.getElapsedTime().asSeconds()>1.2f)
            {
                addEnemyBullet(bullets,enemies);
                enemyShootClock.restart();
            }

            moveEnemies(enemies,enemyDirection);
            moveBullets(bullets);

            checkCollisions(
                bullets,
                enemies,
                player,
                score,
                lives
            );

            if(countEnemies(enemies)==0)
            {
                createEnemies(enemies);
            }

            if(lives<=0)
            {
                gameOver=true;

                if(!scoreSaved)
                {
                    saveScore(playerName,score);
                    scoreSaved=true;
                }
            }

            // Remove bullets outside window
            for(int i=(int)bullets.size()-1;i>=0;i--)
            {
                float y=bullets[i].shape.getPosition().y;

                if(y<0 || y>height)
                {
                    bullets.erase(bullets.begin()+i);
                }
            }
        }

        // ======================================
        // UPDATE SCORE AND LIVES
        // ======================================

        scoreText.setString("Score: "+to_string(score));
        livesText.setString("Lives: "+to_string(lives));

        window.clear(sf::Color::Black);

        // ======================================
        // MAIN MENU DISPLAY
        // ======================================

        if(enteringName)
        {
            nameText.setString("Enter Your Name: "+playerName);

            window.draw(titleText);
            window.draw(nameText);
            window.draw(instructionText);
            window.draw(startText);
            window.draw(menuLeaderboardTitle);

            sf::Text instructions(
                font,
                "LEFT ARROW - Move Left\n"
                "RIGHT ARROW - Move Right\n"
                "SPACE - Shoot\n"
                "R - Restart after Game Over\n"
                "Close Window - Exit Game",
                17
            );

            instructions.setPosition({50.f,300.f});
            window.draw(instructions);

            // Display Top 5 leaderboard
            vector<ScoreEntry> scores=loadLeaderboard();

            if(scores.size()==0)
            {
                sf::Text emptyText(font,"No Scores Yet!",20);
                emptyText.setPosition({500.f,220.f});
                window.draw(emptyText);
            }

            for(int i=0;i<scores.size() && i<5;i++)
            {
                sf::Text entryText(
                    font,
                    to_string(i+1)+". "+
                    scores[i].name+" - "+
                    to_string(scores[i].score),
                    20
                );

                entryText.setPosition({
                    480.f,
                    220.f+i*40.f
                });

                window.draw(entryText);
            }
        }

        // ======================================
        // GAME OVER DISPLAY
        // ======================================

        else if(gameOver)
        {
            window.draw(gameOverText);
            window.draw(leaderboardTitle);
            window.draw(scoreText);
            window.draw(restartText);

            vector<ScoreEntry> scores=loadLeaderboard();

            if(scores.size()==0)
            {
                sf::Text emptyText(font,"No Scores Yet!",20);
                emptyText.setPosition({300.f,230.f});
                window.draw(emptyText);
            }

            for(int i=0;i<scores.size() && i<5;i++)
            {
                sf::Text entryText(
                    font,
                    to_string(i+1)+". "+
                    scores[i].name+" - "+
                    to_string(scores[i].score),
                    22
                );

                entryText.setPosition({
                    260.f,
                    230.f+i*40.f
                });

                window.draw(entryText);
            }
        }

        // ======================================
        // NORMAL GAME SCREEN
        // ======================================

        else
        {
            drawPlayer(window,player);
            drawEnemies(window,enemies);
            drawBullets(window,bullets);

            window.draw(scoreText);
            window.draw(livesText);
        }

        window.display();
    }

    return 0;
}

// ==========================================
// ZIA'S CODE ENDS HERE
// ==========================================taskkill /F /IM game.exe