# Space Invaders Game

## Project Description
Space Invaders is a 2D shooting game developed using C++ and SFML. The player controls a spaceship and shoots enemies to earn points while avoiding enemy attacks.

## Team Members
- **Abdullah** – Enemy system, bullets, collision detection, and game mechanics.
- **Zia** – Player movement, game window, main game loop, and user interface.

## Technologies Used
- C++
- SFML 3
- Visual Studio Code
- GitHub

## Project Files
- `abdullah.cpp` – Abdullah's original contribution.
- `zia.cpp` – Zia's original contribution.
- `main.cpp` – Final combined game code.
- `README.md` – Project information and documentation.

## Build and Run
Build from the project directory with SFML 3 installed:

```powershell
g++ -std=c++17 main.cpp -o output\space_invader_combined.exe -lsfml-graphics -lsfml-window -lsfml-system
.\output\space_invader_combined.exe
```

Use the left and right arrow keys to move, Space to shoot, and R to restart after Game Over.

## Team Collaboration
The original contributions are kept in their separate files; the playable game combines both contributions in `main.cpp`.

## Project Goal
To develop a simple and enjoyable 2D Space Invaders game while learning C++, SFML, and teamwork through GitHub.
