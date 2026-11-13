# Space Invaders: Galactic Defense

A small 2D Space Invaders-style game written in C++ with SFML 3. The player
controls a cyan ship at the bottom of an 800 x 600 window, shoots green enemies,
and avoids the red bullets they fire.

The complete playable game is in `main.cpp`. The separate `zia.cpp` and
`abdullah.cpp` files preserve the original team contributions; do not compile
them alongside `main.cpp`, because the combined game already contains their
code.

## Gameplay

- The game starts with 18 enemies arranged in three rows.
- Enemies move sideways while gradually descending. When the formation is
  cleared, a new formation appears.
- Shoot enemies with Space. Each enemy hit adds 10 points.
- Enemies fire red bullets periodically. A hit costs one life; the player
  starts with three lives.
- Losing all three lives displays the Game Over message. Press R to restart
  with a new formation, three lives, and a score of zero.
- The game window is 800 x 600 pixels and is limited to 60 frames per second.

## Controls

| Key | Action |
| --- | --- |
| Left Arrow | Move the player left |
| Right Arrow | Move the player right |
| Space | Fire a player bullet |
| R | Restart after Game Over |
| Close button | Exit the game |

## How the Code Works

- `Enemy` stores an enemy's rectangle and whether it is still alive.
- `Bullet` stores a bullet's rectangle and whether it belongs to the player or
  an enemy.
- Helper functions create, move, draw, and count enemies and bullets, and
  detect bullet collisions to update the score and lives.
- The main loop processes window events and keyboard input, controls the
  firing timers, updates game state, and draws the scene and score display.

The game uses colored rectangles rather than image sprites and does not
currently include sound, a menu, or a separate victory screen.

## Project Files

| File or folder | Purpose |
| --- | --- |
| `main.cpp` | Combined, playable game; compile this file to build the game. |
| `zia.cpp` | Zia's original player, window, and game-loop contribution. |
| `abdullah.cpp` | Abdullah's original enemy, bullet, and collision contribution. |
| `abdullah.html` | Empty HTML starter file; it is not used by the C++ game. |
| `.vscode/` | Visual Studio Code C/C++ configuration files. |
| `output/` | Folder for the built Windows executable. |

## Requirements

- Windows, because the game loads Arial from
  `C:\Windows\Fonts\arial.ttf`.
- A C++17-compatible compiler such as MinGW-w64 g++.
- SFML 3 development headers and libraries for the same compiler and
  architecture as your compiler.
- SFML runtime DLLs available on `PATH` when launching the game.

The commands below assume MSYS2 UCRT64 and SFML 3 are installed under
`C:\msys64\ucrt64`. If you installed them elsewhere, adjust `PATH` and the
compiler's include, library, and runtime DLL paths to match your installation.

## Build and Run (PowerShell)

Run these commands from the project directory:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
g++ -std=c++17 main.cpp -o output\space_invader.exe -lsfml-graphics -lsfml-window -lsfml-system
.\output\space_invader.exe
```

Only `main.cpp` is passed to the compiler. The SFML graphics, window, and system
libraries are required for linking. The `output` folder is included in the
project; create it if it is missing.

## Troubleshooting

- **`g++` is not recognized:** install a C++ compiler or add its `bin` folder
  to `PATH`. For the default MSYS2 UCRT64 installation, use the `PATH` command
  shown above.
- **SFML headers or libraries cannot be found:** install the SFML 3 development
  files for your compiler, and ensure the compiler can find their include and
  library directories. Do not mix libraries built for a different compiler or
  architecture.
- **An SFML DLL is missing when starting the game:** add the SFML `bin`
  directory to `PATH`. With the default MSYS2 UCRT64 installation, that is
  `C:\msys64\ucrt64\bin`.
- **The font cannot be loaded:** the game expects
  `C:\Windows\Fonts\arial.ttf`. Make sure Arial is installed at that path.

## Team

- **Zia** — Player movement, game window, main game loop, and interface.
- **Abdullah** — Enemy system, bullets, collision detection, and game mechanics.

The individual contribution files are retained for reference. The combined
version in `main.cpp` is the source to build and run.
