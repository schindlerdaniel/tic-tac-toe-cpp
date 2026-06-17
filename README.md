# tic-tac-toe-cpp
A simple Tic-Tac-Toe game implemented in C++

# Object-Oriented Tic-Tac-Toe in C++

An object-oriented, console-based Tic-Tac-Toe game written in C++ as a university project. The application features a fully modular architecture, custom memory management without STL containers, and game state serialization (save/load).

## Key Features
- **Customizable Board Size:** Supports dynamic grid sizes starting from 3x3 up to reasonable limits.
- **Diagonal Win Settings:** Toggleable diagonal winning conditions at the start of each match.
- **Save and Load System:** Game state serialization allowing players to save progress to a file and resume later exactly where they left off.
- **Robust Input Handling:** Full validation for out-of-bounds coordinates, occupied cells, and invalid inputs.
- **Replayability:** Option to start a new match immediately after a game ends without restarting the application.

## Technical Details & Architecture
The project strictly follows Object-Oriented Programming (OOP) principles without using any STL containers:
- **`Game` Class:** Manages the game lifecycle, turn-switching, and move history.
- **`Board` Class:** Handles the 2D grid allocation, win-checking algorithms, rendering, and file I/O (save/load).
- **`Figure` Base Class & Inheritance:** Polymorphic approach where `XFigure` and `OFigure` extend the base `Figure` class to represent game pieces.

## Memory Management
- Developed **without STL containers** using manual dynamic memory allocation (2D pointer arrays).
- Features full memory leak protection, verified using the `memtrace` library to ensure all dynamic allocations are properly freed in the destructors.



