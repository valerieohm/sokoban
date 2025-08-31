#include "game.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Test fixture for Game tests
class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Get a reference to the singleton Game instance
        game = &Game::instance();

        // Initialize with default settings
        game->initialize();
    }

    Game *game;
};

// Test game initialization
TEST_F(GameTest, Initialize) {
    // After initialization, the game should be in MENU state
    EXPECT_FALSE(game->isLevelComplete());
}

// Test player movement
TEST_F(GameTest, PlayerMovement) {
    // Test moving in all four directions
    EXPECT_TRUE(game->movePlayer(Direction::RIGHT));
    EXPECT_TRUE(game->movePlayer(Direction::DOWN));
    EXPECT_TRUE(game->movePlayer(Direction::LEFT));
    EXPECT_TRUE(game->movePlayer(Direction::UP));
}

// Test for level completion with manually placed box on goal
TEST_F(GameTest, ManualLevelCompletion) {
    // Create a custom board with a simple layout for testing
    Board &board = Board::instance();

    // Resize to a very small board
    board.resize(3, 3);

    // First clear the board
    for (size_t y = 0; y < board.height(); ++y) {
        for (size_t x = 0; x < board.width(); ++x) {
            board[y][x] = Type::Floor;
        }
    }

    // Put player at (0,0)
    board[0][0] = Type::Floor | Type::At;

    // Put a box on a goal at (1,1)
    board[1][1] = Type::Floor | Type::Box | Type::Goal;

    // Print the board before initialization
    std::cout << "Board before initialization:" << std::endl;
    board.print();

    // Update game state from board without changing the board
    game->updateStateFromBoard();

    std::cout << "Board after updating state:" << std::endl;
    board.print();

    // Debug: print detailed board state
    for (size_t y = 0; y < board.height(); ++y) {
        for (size_t x = 0; x < board.width(); ++x) {
            std::cout << "(" << x << "," << y
                      << "): " << Type::toString(board[y][x]) << std::endl;
        }
    }

    // Verify level completion
    EXPECT_TRUE(game->isLevelComplete());
}
