#include "game.hpp"
#include <iostream>
#include <thread>

// Singleton implementation
Game &Game::instance() {
    static Game inst;
    return inst;
}

Game::Game()
    : state_(GameState::MENU), board_(Board::instance()), playerX_(0),
      playerY_(0), numBoxes_(0), numBoxesOnGoal_(0) {}

bool Game::initialize() {
    // Initialize game state
    state_ = GameState::MENU;

    // Default setup if no level is loaded
    board_.resize(5, 5);

    // Create a simple level for testing
    for (size_t y = 0; y < board_.height(); ++y) {
        for (size_t x = 0; x < board_.width(); ++x) {
            // Create walls around the border
            if (x == 0 || y == 0 || x == board_.width() - 1 ||
                y == board_.height() - 1) {
                board_[y][x] = Type::Wall;
            } else {
                board_[y][x] = Type::Floor;
            }
        }
    }

    // Add player, box and goal
    board_[1][1] = Type::Floor | Type::At;   // Player
    board_[2][2] = Type::Floor | Type::Box;  // Box
    board_[3][3] = Type::Floor | Type::Goal; // Goal

    // Find player position and count boxes
    findPlayer();
    countBoxes();

    // Initialize timing
    lastFrameTime_ = std::chrono::high_resolution_clock::now();

    return true;
}

void Game::run() {
    state_ = GameState::PLAYING;

    // Main game loop
    while (state_ != GameState::QUIT) {
        // Calculate delta time
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = currentTime - lastFrameTime_;
        double deltaTime = diff.count();
        lastFrameTime_ = currentTime;

        // Process player input
        processInput();

        // Update game state
        if (state_ == GameState::PLAYING) {
            update(deltaTime);
        }

        // Render the game
        render();

        // Check for level completion
        if (isLevelComplete() && state_ == GameState::PLAYING) {
            state_ = GameState::LEVEL_COMPLETE;
            std::cout << "Level Complete!" << std::endl;
        }

        // Simple frame limiting
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Game::pause() {
    if (state_ == GameState::PLAYING) {
        state_ = GameState::PAUSED;
        std::cout << "Game paused" << std::endl;
    }
}

void Game::resume() {
    if (state_ == GameState::PAUSED) {
        state_ = GameState::PLAYING;
        std::cout << "Game resumed" << std::endl;
    }
}

void Game::quit() {
    state_ = GameState::QUIT;
    std::cout << "Quitting game" << std::endl;
}

bool Game::loadLevel(const std::string &filename) {
    if (board_.loadFromFile(filename)) {
        findPlayer();
        countBoxes();
        state_ = GameState::PLAYING;
        return true;
    }
    return false;
}

bool Game::isLevelComplete() const {
    return numBoxesOnGoal_ == numBoxes_ && numBoxes_ > 0;
}

bool Game::movePlayer(Direction dir) {
    size_t newX = playerX_;
    size_t newY = playerY_;

    // Calculate new position based on direction
    switch (dir) {
    case Direction::UP:
        if (newY > 0)
            newY--;
        break;
    case Direction::DOWN:
        if (newY < board_.height() - 1)
            newY++;
        break;
    case Direction::LEFT:
        if (newX > 0)
            newX--;
        break;
    case Direction::RIGHT:
        if (newX < board_.width() - 1)
            newX++;
        break;
    }

    // Check if the move is valid
    if (newX == playerX_ && newY == playerY_) {
        return false; // No movement (would move outside the board)
    }

    // Check destination tile
    Flag destTile = board_[newY][newX];

    // Cannot move into a wall
    if (destTile & Type::Wall) {
        return false;
    }

    // If there's a box, check if we can push it
    if (destTile & Type::Box) {
        // Calculate position after the box
        size_t boxNewX = newX;
        size_t boxNewY = newY;

        switch (dir) {
        case Direction::UP:
            if (boxNewY > 0)
                boxNewY--;
            break;
        case Direction::DOWN:
            if (boxNewY < board_.height() - 1)
                boxNewY++;
            break;
        case Direction::LEFT:
            if (boxNewX > 0)
                boxNewX--;
            break;
        case Direction::RIGHT:
            if (boxNewX < board_.width() - 1)
                boxNewX++;
            break;
        }

        // Check if the box can be pushed
        Flag boxDestTile = board_[boxNewY][boxNewX];

        // Cannot push box into a wall or another box
        if ((boxDestTile & Type::Wall) || (boxDestTile & Type::Box)) {
            return false;
        }

        // Move the box
        board_[boxNewY][boxNewX] = boxDestTile | Type::Box;
        if (boxDestTile & Type::Goal) {
            numBoxesOnGoal_++;
        }

        // Remove box from current position
        board_[newY][newX] = destTile & ~Type::Box;
        if ((destTile & Type::Goal) && (destTile & Type::Box)) {
            numBoxesOnGoal_--;
        }
    }

    // Move player
    board_[newY][newX] = board_[newY][newX] | Type::At;
    board_[playerY_][playerX_] = board_[playerY_][playerX_] & ~Type::At;

    // Update player position
    playerX_ = newX;
    playerY_ = newY;

    // Recount boxes and update game state
    countBoxes();
    updateGameState();

    return true;
}

void Game::update(double deltaTime) {
    // Any time-based updates would go here
    // For now, we'll just use this to update game state
    updateGameState();
}

void Game::render() const {
    // Clear screen
    std::cout << "\033[2J\033[1;1H";

    // Print game status
    std::cout << "Sokoban - ";
    switch (state_) {
    case GameState::MENU:
        std::cout << "Main Menu";
        break;
    case GameState::PLAYING:
        std::cout << "Playing";
        break;
    case GameState::PAUSED:
        std::cout << "Paused";
        break;
    case GameState::LEVEL_COMPLETE:
        std::cout << "Level Complete!";
        break;
    case GameState::GAME_OVER:
        std::cout << "Game Over";
        break;
    case GameState::QUIT:
        std::cout << "Quitting";
        break;
    }
    std::cout << std::endl;

    // Print board state
    std::cout << "Boxes on goal: " << numBoxesOnGoal_ << "/" << numBoxes_
              << std::endl;

    // Print the board
    board_.print();

    // Print controls
    std::cout << "Controls: WASD = Move, P = Pause, Q = Quit" << std::endl;
}

void Game::processInput() {
    // In a real implementation, this would handle keyboard input
    // For now, this is a placeholder that would be replaced with actual input
    // handling using a library like SDL or GLFW, or Qt input handling

    // Example of how we might process input when integrated with Qt or ncurses:
    // char key = getInputChar();
    // switch (key) {
    //     case 'w': movePlayer(Direction::UP); break;
    //     case 's': movePlayer(Direction::DOWN); break;
    //     case 'a': movePlayer(Direction::LEFT); break;
    //     case 'd': movePlayer(Direction::RIGHT); break;
    //     case 'p':
    //         if (state_ == GameState::PLAYING) pause();
    //         else if (state_ == GameState::PAUSED) resume();
    //         break;
    //     case 'q': quit(); break;
    // }
}

bool Game::tryMove(size_t fromX, size_t fromY, size_t toX, size_t toY) {
    // Check if destination is in bounds
    if (toX >= board_.width() || toY >= board_.height()) {
        return false;
    }

    // Cannot move into a wall
    if (board_[toY][toX] & Type::Wall) {
        return false;
    }

    return true;
}

void Game::findPlayer() {
    playerX_ = 0;
    playerY_ = 0;

    // Search the board for the player position
    for (size_t y = 0; y < board_.height(); ++y) {
        for (size_t x = 0; x < board_.width(); ++x) {
            if (board_[y][x] & Type::At) {
                playerX_ = x;
                playerY_ = y;
                return;
            }
        }
    }
}

void Game::countBoxes() {
    numBoxes_ = 0;
    numBoxesOnGoal_ = 0;

    // Count boxes and boxes on goals
    for (size_t y = 0; y < board_.height(); ++y) {
        for (size_t x = 0; x < board_.width(); ++x) {
            Flag tile = board_[y][x];
            if (tile & Type::Box) {
                numBoxes_++;
                if (tile & Type::Goal) {
                    numBoxesOnGoal_++;
                }
            }
        }
    }

    // Debug output can be enabled when needed
    // std::cout << "Boxes: " << numBoxes_ << ", Boxes on goal: " <<
    // numBoxesOnGoal_ << std::endl;
}

void Game::updateStateFromBoard() {
    // Just update player position and box counts without changing the board
    findPlayer();
    countBoxes();
    updateGameState();
}

void Game::updateGameState() {
    // Recount boxes to make sure our state is up to date
    countBoxes();

    // Update game state based on current conditions
    if (isLevelComplete()) {
        state_ = GameState::LEVEL_COMPLETE;
    }
}
