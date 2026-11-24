Space Invaders: Galactic Defense

About the Project

Space Invaders: Galactic Defense is a 2D shooting game developed in C++ using the SFML graphics library.

The player controls a spaceship and tries to destroy incoming enemies while avoiding their bullets. The game also includes a main menu, player name entry, sound effects, and a leaderboard to save high scores.

Game Features

- Main Menu: Start the game, view instructions, check the leaderboard, or exit.
- Player Movement: Control a cyan spaceship using the left and right arrow keys.
- Enemy Formation: 18 green enemies appear in three rows, with six enemies in each row.
- Shooting System: Press Space to shoot bullets at enemies.
- Enemy Movement: Enemies move sideways and gradually move downwards.
- Scoring System: Each destroyed enemy gives the player 10 points.
- Lives System: The player starts with three lives. Getting hit by an enemy bullet costs one life.
- New Enemy Waves: A new formation appears after all current enemies are destroyed.
- Game Over: The game ends when the player loses all three lives or an enemy reaches the player.
- Leaderboard: Player names and scores are saved in "leaderboard.txt". The highest five scores are displayed.
- Sound Effects: Sounds are included for shooting, enemy explosions, player damage, and game over.

Controls

Key| Action
Left Arrow| Move spaceship left
Right Arrow| Move spaceship right
Space| Shoot bullets
Enter| Confirm player name and start
Backspace| Delete the last character of the name
Escape| Return to the main menu while entering a name
R| Restart after Game Over
M| Return to the main menu
Mouse Click| Select menu and Back buttons
Window Close| Exit the game

Project Files

- "main.cpp" – Contains the complete combined game code.
- "zia.cpp" – Separate file containing an original team contribution.
- "abdullah.cpp" – Separate file containing another original team contribution.
- "sounds/" – Contains the sound effects used in the game.
- "leaderboard.txt" – Stores player names and scores.

Note: Compile "main.cpp" as the main game file. Do not compile "zia.cpp" and "abdullah.cpp" alongside it because their combined game code is already included in "main.cpp".

Technical Details

- Programming Language: C++
- Graphics Library: SFML
- Window Resolution: 800 × 600 pixels
- Frame Rate Limit: 60 FPS
- Score Storage: Text file ("leaderboard.txt")

How to Play

1. Launch the game to open the main menu.
2. Select Play Game and enter your name.
3. Press Enter to start playing.
4. Move your spaceship and shoot the enemies.
5. Avoid enemy bullets and try to achieve the highest score.
6. After Game Over, press R to play again or M to return to the main menu.

Building and Running the Project

Requirements:

- C++ compiler
- SFML graphics library
- Visual Studio or VS Code

Compiling the Game:

- Make sure SFML is installed and properly configured.
- Open the project in your IDE.
- Compile the main.cpp file with the required SFML libraries.
- Make sure the sounds folder and leaderboard.txt file are in the correct project directory.

Running the Game:

- Run the compiled game file.
- The main menu will appear on the screen.
- Select Play Game to start playing.

Note: Only main.cpp should be compiled as the main game file. The zia.cpp and abdullah.cpp files contain separate team contributions and are already included in main.cpp.
