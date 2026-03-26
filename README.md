# Tic-Tac-Toe (SFML 3 GUI)

A responsive, graphical Tic-Tac-Toe game built with C++17 and **SFML 3**.

This project started as a raw prototype and has been refactored into a fully playable, desktop-native GUI application. It features a scalable board, mouse-hover interactions, and dynamic window-title-based game status tracking.

## 🚀 Features

- **Responsive GUI:** The game board scales gracefully when you resize the window.
- **Modern SFML 3 Implementation:** Utilizes modern SFML event handling and rendering APIs.
- **Mouse Interactivity:** Full mouse support with visual hover feedback, making the UI feel snappy and responsive.
- **Game State Management:** Detects wins for X and O, as well as draws. Press `R` to restart match instantly.

---

## 🛠️ How to Compile and Run on Windows

You have two main paths to build the project: using **MSYS2 (MinGW-w64)** directly or using **CMake**.

### Option 1: Using MSYS2 / UCRT64 (Recommended, Fastest)

This method assumes you are using MSYS2 on Windows, specifically the **UCRT64** environment.

1. **Install MSYS2** (if you haven't already) from [msys2.org](https://www.msys2.org/).
2. Open the **MSYS2 UCRT64** terminal and install the C++ compiler and SFML 3:
   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-sfml
   ```
3. Navigate to the project directory:
   ```bash
   cd path/to/Gui-Project-TicTacToe-
   ```
4. **Compile** the code:
   ```bash
   g++ -std=c++17 main.cpp drawing.cpp input_handler.cpp game_logic.cpp stats.cpp -o tic_tac_toe.exe -lsfml-graphics -lsfml-window -lsfml-system
   ```
5. **Run** the executable:
   ```bash
   .\tic_tac_toe.exe
   ```

### Option 2: Using CMake

If you prefer a CMake workflow (works with MSYS2, Visual Studio, or CLion):

1. Open a terminal in the project directory.
2. Generate build files (CMake will automatically fetch SFML 3 for you):
   ```bash
   cmake -S . -B build
   ```
3. Compile the project:
   ```bash
   cmake --build build --config Release
   ```
4. Run the generated executable located in the `build/` or `build/Release/` directory.

---

## 🧩 Codebase Architecture & Components

The application adopts a modular pattern, splitting rendering, IO parsing, and logical checks into their own dedicated files.

### 1. `main.cpp`

**The Entry Point.**
Manages the `sf::RenderWindow` instantiation and holds the global timeline/game loops.

- **`int main()`:** Initializes the window, sets Framerate/VSync, handles the primary `while(window.isOpen())` game loop, and delegates to event processors and drawing routines frame-by-frame.
- **`updateWindowTitle(sf::RenderWindow&)`:** Dynamically modifies the OS-level window title bar to display the current player's turn, winning congratulation, or a draw message based on global state.

### 2. `starter.h`

**The Shared Blueprint.**
Contains all shared structures and external declarations. By grouping state (`board[][]`, `currentPlayer`, `gameOver`) and function prototypes here, any `.cpp` file can easily interface with another. Includes definitions for `Player`, `Move`, and `GameState` structs.

### 3. `input_handler.cpp`

**The Controller.**
Listens to user input, maps window clicks to the internal grid, and executes state changes.

- **`processEvents(sf::RenderWindow&)`:** Polls through all user inputs (Mouse movements, Clicks, Keyboard press `R`, Resizes). Dispatches logic accordingly.
- **`mapPixelToCell(...)`:** Translates exact 2D pixel mouse coordinates (X, Y) into logical board array coordinates (Row 0-2, Col 0-2), taking window resizing into account.
- **`placeMark(int row, int col)`:** Safely handles the internal state assignment of `X` or `O`. Rejects invalid inputs or filled cells. After marking, it evaluates if a winner or draw was reached and swaps the turn.
- **`resetBoard()`:** Clears out the 2D array, reverts `currentPlayer` to 'X', and resets flags.

### 4. `drawing.cpp`

**The Renderer.**
Examines the global state variable (`board`) and paints the graphical representation using SFML Shapes.

- **`drawGrid(sf::RenderWindow&)`:** The main render routine. Draws the dark background, calculating line layout to establish the Tic-Tac-Toe grid, evaluating hover placements, and parsing the 2D memory array into visual graphics.
- **`getBoardArea(const sf::RenderWindow&)`:** Helper function to keep the grid perfectly centered and correctly sized even if the user resizes the OS window.
- **`drawX(...)` and `drawO(...)`:** Helpers to construct and mathematically place the visual components of standard game markings inside a single cell bounds cleanly.

### 5. `game_logic.cpp`

**The Rule Engine.**
Strictly stateless checks that survey the global `board`.

- **`checkWinner()`:** Runs an exhaustive iteration over all rows, all columns, and both diagonals to determine if 'X' or 'O' claims a line of three.
- **`isBoardFull()`:** Scans the `board` for empty spaces to establish when a Draw condition has occurred.

### 6. `stats.cpp`

**The File I/O.**
Handles saving and loading the persistent leaderboard.

- **`saveStats(const Player& p)`:** Writes a player struct data (name, wins, losses) to a flat text file `stats.txt`.
- **`loadStats(Player& p)`:** Reads from `stats.txt` to initialize previous game data back into the program. _(Note: Readily implemented, but waiting to be integrated into a broader UI leaderboard element!)_
