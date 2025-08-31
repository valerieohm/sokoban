#ifndef GAME_H_9b47c15f853c5a1d
#define GAME_H_9b47c15f853c5a1d

#include "board.hpp"
#include "types.hpp"
#include <chrono>
#include <string>

enum class GameState { MENU, PLAYING, PAUSED, LEVEL_COMPLETE, GAME_OVER, QUIT };

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Game {
public:
    static Game &instance();

    // Game state management
    bool initialize();
    void run();
    void pause();
    void resume();
    void quit();

    // Level management
    bool loadLevel(const std::string &filename);
    bool isLevelComplete() const;

    // Player movement
    bool movePlayer(Direction dir);

    // Game loop control
    void update(double deltaTime);
    void render() const;

    // Input handling
    void processInput();

    // Testing helpers
    void updateStateFromBoard(); // For testing - just updates player position
                                 // and box counts

private:
    Game();
    ~Game() = default;

    // Game state
    GameState state_;
    Board &board_;
    size_t playerX_;
    size_t playerY_;
    size_t numBoxes_;
    size_t numBoxesOnGoal_;

    // Game loop timing
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime_;

    // Utility functions
    bool tryMove(size_t fromX, size_t fromY, size_t toX, size_t toY);
    void findPlayer();
    void countBoxes();
    void updateGameState();
};

#endif // GAME_H_9b47c15f853c5a1d
