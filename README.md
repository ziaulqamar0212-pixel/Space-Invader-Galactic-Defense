# Space Invaders

A 2D Space Invaders game written in C++ with SFML 3. The complete playable game
is in `main.cpp`; the original individual contributions are kept in
`abdullah.cpp` and `zia.cpp`.

## Gameplay

- Move the cyan player ship left and right.
- Shoot the green enemies; each enemy hit adds 10 points.
- Avoid red enemy bullets. The game ends when you lose all 3 lives.
- A new enemy formation appears when all enemies in a formation are defeated.
- Press `R` after Game Over to restart.

The game window is 800 x 600 pixels.

## Controls

| Key | Action |
| --- | --- |
| Left Arrow | Move left |
| Right Arrow | Move right |
| Space | Shoot |
| R | Restart after Game Over |

## Requirements

- A C++17-compatible compiler (the project has been built with MinGW g++).
- SFML 3 with its headers, libraries, and runtime DLLs installed.
- On Windows, the game loads Arial from `C:\Windows\Fonts\arial.ttf`.

Make sure the SFML `bin` directory is on `PATH` when launching the game so
Windows can find the SFML runtime DLLs.

## Build and Run (Windows PowerShell)

Run these commands from the project directory. The output folder is already
included in the project.

```powershell
g++ -std=c++17 main.cpp -o output\space_invader.exe -lsfml-graphics -lsfml-window -lsfml-system
.\output\space_invader.exe
```

The compiler must be configured to find the SFML include and library
directories. If SFML is installed with MSYS2 UCRT64, add
`C:\msys64\ucrt64\bin` to `PATH` before running the executable.

## Project Files

- `main.cpp` - Combined game source (player, enemies, bullets, collisions, and interface).
- `abdullah.cpp` - Original enemy and game-mechanics contribution.
- `zia.cpp` - Original player, window, and game-loop contribution.
- `output\space_invader.exe` - Built Windows game executable.

## Team

- **Abdullah** - Enemy system, bullets, collision detection, and game mechanics.
- **Zia** - Player movement, game window, main game loop, and user interface.
