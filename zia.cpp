#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include <string>
using namespace std;
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
void drawButton(sf::RenderWindow& window,sf::RectangleShape& button,sf::Text& text)
{
    window.draw(button);
    window.draw(text);
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
    std::string playerName="";
    bool mainMenu=true;
    bool enteringName=false;
    bool showInstructions=false;
    bool showLeaderboard=false;
    bool playing=false;
    bool gameOver=false;
    bool scoreSaved=false;

    sf::Clock playerShootClock;
    sf::Clock enemyShootClock;

    sf::RectangleShape playButton({240.f,50.f});
    sf::RectangleShape instructionButton({240.f,50.f});
    sf::RectangleShape leaderboardButton({240.f,50.f});
    sf::RectangleShape exitButton({240.f,50.f});
    sf::RectangleShape backButton({180.f,45.f});

    playButton.setPosition({280.f,190.f});
    instructionButton.setPosition({280.f,260.f});
    leaderboardButton.setPosition({280.f,330.f});
    exitButton.setPosition({280.f,400.f});
    backButton.setPosition({310.f,510.f});

    playButton.setFillColor(sf::Color(0,120,200));
    instructionButton.setFillColor(sf::Color(0,120,200));
    leaderboardButton.setFillColor(sf::Color(0,120,200));
    exitButton.setFillColor(sf::Color(180,40,40));
    backButton.setFillColor(sf::Color(0,120,200));

    sf::Text titleText(font,"SPACE INVADERS",42);
    sf::Text playText(font,"PLAY GAME",22);
    sf::Text instructionMenuText(font,"INSTRUCTIONS",22);
    sf::Text leaderboardMenuText(font,"LEADERBOARD",22);
    sf::Text exitText(font,"EXIT",22);
    sf::Text backText(font,"BACK",20);
    sf::Text nameText(font,"Enter Your Name:",25);
    sf::Text startText(font,"Press ENTER to Start",22);
    sf::Text instructionsTitle(font,"HOW TO PLAY",32);

    sf::Text instructionsText(font,"LEFT ARROW  - Move Left\n" "RIGHT ARROW - Move Right\n" "SPACE - Shoot\n" "Destroy enemies  to earn 10 points\n""Avoid enemy bullets\n""Game ends when lives become zero\n""R - Restart after Game Over",20);
    sf::Text menuleaderboardTitle(font,"TOP 5 LEADERBOARD",30);
    sf::Text scoreText(font,"Score: 0",24);
    sf::Text livesText(font,"Lives: 3",24);
    sf::Text gameOverText(font,"GAME OVER",40);
    sf::Text restartText(font,"R - Restart    M - Main Menu",22);

    titleText.setPosition({205.f,65.f});
    playText.setPosition({340.f,200.f});
    instructionMenuText.setPosition({315.f,270.f});
    leaderboardMenuText.setPosition({310.f,340.f});
    exitText.setPosition({370.f,410.f});
    backText.setPosition({370.f,518.f});
    nameText.setPosition({230.f,240.f});
    startText.setPosition({300.f,330.f});
    instructionsTitle.setPosition({275.f,100.f});
    instructionsText.setPosition({180.f,190.f});
    menuleaderboardTitle.setPosition({250.f,100.f});
    scoreText.setPosition({20.f,15.f});
    livesText.setPosition({680.f,15.f});
    gameOverText.setPosition({300.f,100.f});
    restartText.setPosition({260.f,530.f});

   while(window.isOpen())
{
    while(const optional event=window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if(const auto* mouseButton=event->getIf<sf::Event::MouseButtonPressed>())
        {
            if(mouseButton->button==sf::Mouse::Button::Left)
            {
                sf::Vector2f mousePosition(
                    static_cast<float>(mouseButton->position.x),
                    static_cast<float>(mouseButton->position.y)
                );

                if(mainMenu)
                {
                    if(playButton.getGlobalBounds().contains(mousePosition))
                    {
                        mainMenu=false;
                        enteringName=true;
                    }
                    else if(instructionButton.getGlobalBounds().contains(mousePosition))
                    {
                        mainMenu=false;
                        showInstructions=true;
                    }
                    else if(leaderboardButton.getGlobalBounds().contains(mousePosition))
                    {
                        mainMenu=false;
                        showLeaderboard=true;
                    }
                    else if(exitButton.getGlobalBounds().contains(mousePosition))
                    {
                        window.close();
                    }
                }
                else if(showInstructions || showLeaderboard)
                {
                    if(backButton.getGlobalBounds().contains(mousePosition))
                    {
                        showInstructions=false;
                        showLeaderboard=false;
                        mainMenu=true;
                    }
                }
            }
        }

        if(enteringName)
        {
            if(const auto* key=event->getIf<sf::Event::KeyPressed>())
            {
                if(key->code==sf::Keyboard::Key::Enter && playerName.length()>0)
                {
                    enteringName=false;
                    playing=true;
                    score=0;
                    lives=3;
                    scoreSaved=false;
                    bullets.clear();
                    createEnemies(enemies);
                    player.setPosition({375.f,540.f});
                    enemyDirection=2.f;
                    playerShootClock.restart();
                    enemyShootClock.restart();
                }

                if(key->code==sf::Keyboard::Key::Backspace && playerName.length()>0)
                {
                    playerName.pop_back();
                }

                if(key->code==sf::Keyboard::Key::Escape)
                {
                    enteringName=false;
                    mainMenu=true;
                }
            }

            if(const auto* text=event->getIf<sf::Event::TextEntered>())
            {
                if(text->unicode>=32 && text->unicode<=126 && playerName.length()<15)
                {
                    playerName+=static_cast<char>(text->unicode);
                }
            }
        }
        else if(gameOver)
        {
            if(const auto* key=event->getIf<sf::Event::KeyPressed>())
            {
                if(key->code==sf::Keyboard::Key::R)
                {
                    score=0;
                    lives=3;
                    gameOver=false;
                    playing=true;
                    scoreSaved=false;
                    bullets.clear();
                    createEnemies(enemies);
                    player.setPosition({375.f,540.f});
                    enemyDirection=2.f;
                    playerShootClock.restart();
                    enemyShootClock.restart();
                }

                if(key->code==sf::Keyboard::Key::M)
                {
                    gameOver=false;
                    mainMenu=true;
                    playing=false;
                    playerName="";
                }
            }
        }
    }

    if(playing && !gameOver)
    {
        movePlayer(player);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
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

        if(enemyReachedPlayer(enemies,player))
        {
            lives=0;
        }

        moveBullets(bullets);

        checkCollisions(bullets,enemies,player,score,lives);

        if(countEnemies(enemies)==0)
        {
            createEnemies(enemies);
        }

        if(lives<=0)
        {
            gameOver=true;
            playing=false;

            if(!scoreSaved)
            {
                savecore(playerName,score);
                scoreSaved=true;
            }
        }

        for(int i=(int)bullets.size()-1;i>=0;i--)
        {
            float y=bullets[i].shape.getPosition().y;

            if(y<0 || y>HEIGHT)
            {
                bullets.erase(bullets.begin()+i);
            }
        }
    }

    scoreText.setString("Score: "+to_string(score));
    livesText.setString("Lives: "+to_string(lives));
    window.clear(sf::Color::Black);

    if(mainMenu)
    {
        window.draw(titleText);
        drawButton(window,playButton,playText);
        drawButton(window,instructionButton,instructionMenuText);
        drawButton(window,leaderboardButton,leaderboardMenuText);
        drawButton(window,exitButton,exitText);
    }
    else if(enteringName)
    {
        nameText.setString("Enter Your Name: "+playerName);
        window.draw(titleText);
        window.draw(nameText);
        window.draw(startText);
    }
    else if(showInstructions)
    {
        window.draw(instructionsTitle);
        window.draw(instructionsText);
        drawButton(window,backButton,backText);
    }
    else if(showLeaderboard)
    {
        window.draw(menuLeaderboardTitle);
        vector<scoreentry> scores;
        loadleaderboard(scores);

        if(scores.size()==0)
        {
            sf::Text emptyText(font,"No Scores Yet!",22);
            emptyText.setPosition({310.f,220.f});
            window.draw(emptyText);
        }

        for(int i=0;i<scores.size() && i<5;i++)
        {
            sf::Text entryText(font,to_string(i+1)+". "+scores[i].name+" - "+to_string(scores[i].score),22);
            entryText.setPosition({260.f,190.f+i*45.f});
            window.draw(entryText);
        }

        drawButton(window,backButton,backText);
    }
    else if(gameOver)
    {
        window.draw(gameOverText);
        window.draw(scoreText);

        sf::Text leaderboardTitle(font,"TOP 5 LEADERBOARD",28);
        leaderboardTitle.setPosition({250.f,170.f});
        window.draw(leaderboardTitle);

        vector<scoreentry> scores;
        loadleaderboard(scores);

        for(int i=0;i<scores.size() && i<5;i++)
        {
            sf::Text entryText(font, to_string(i+1)+". "+scores[i].name+" - "+to_string(scores[i].score),22);
            entryText.setPosition({260.f,230.f+i*40.f});
            window.draw(entryText);
        }

        window.draw(restartText);
    }
    else if(playing)
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
