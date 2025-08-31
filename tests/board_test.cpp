#include "board.hpp"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Test fixture for Board tests
class BoardTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Get a reference to the singleton Board instance
        board = &Board::instance();

        // Reset the board to a known state for each test
        board->resize(5, 5);

        // Fill board with empty tiles
        for (size_t y = 0; y < board->height(); ++y) {
            for (size_t x = 0; x < board->width(); ++x) {
                (*board)[y][x] = Type::Empty;
            }
        }
    }

    Board *board;
};

// Test board initialization
TEST_F(BoardTest, Initialize) {
    EXPECT_EQ(board->width(), 5);
    EXPECT_EQ(board->height(), 5);

    // Check that all cells are initialized to Empty
    for (size_t y = 0; y < board->height(); ++y) {
        for (size_t x = 0; x < board->width(); ++x) {
            EXPECT_EQ((*board)[y][x], Type::Empty);
        }
    }
}

// Test board resizing
TEST_F(BoardTest, Resize) {
    board->resize(10, 8);

    EXPECT_EQ(board->width(), 10);
    EXPECT_EQ(board->height(), 8);

    // Check that all cells are initialized to Empty
    for (size_t y = 0; y < board->height(); ++y) {
        for (size_t x = 0; x < board->width(); ++x) {
            EXPECT_EQ((*board)[y][x], Type::Empty);
        }
    }
}

// Test setting and getting board cells
TEST_F(BoardTest, SetAndGetCells) {
    // Set some cells to different types
    (*board)[0][0] = Type::Wall;
    (*board)[1][1] = Type::Floor;
    (*board)[2][2] = Type::Box;
    (*board)[3][3] = Type::Goal;
    (*board)[4][4] = Type::At;

    // Verify cell values
    EXPECT_EQ((*board)[0][0], Type::Wall);
    EXPECT_EQ((*board)[1][1], Type::Floor);
    EXPECT_EQ((*board)[2][2], Type::Box);
    EXPECT_EQ((*board)[3][3], Type::Goal);
    EXPECT_EQ((*board)[4][4], Type::At);
}

// Test save and load functionality
TEST_F(BoardTest, SaveAndLoad) {
    // Create a test board with recognizable pattern
    board->resize(3, 3);
    (*board)[0][0] = Type::Wall;
    (*board)[0][1] = Type::Floor;
    (*board)[0][2] = Type::Box;
    (*board)[1][0] = Type::Goal;
    (*board)[1][1] = Type::At;
    (*board)[1][2] = Type::Start;
    (*board)[2][0] = Type::Wall | Type::Goal;
    (*board)[2][1] = Type::Box | Type::Goal;
    (*board)[2][2] = Type::Empty;

    // Create a temporary file for testing
    std::string tempFile = "board_test.bin";

    // Save board to file
    EXPECT_TRUE(board->saveToFile(tempFile));

    // Reset board
    board->resize(1, 1);
    (*board)[0][0] = Type::Empty;

    // Load board from file
    EXPECT_TRUE(board->loadFromFile(tempFile));

    // Verify board dimensions
    EXPECT_EQ(board->width(), 3);
    EXPECT_EQ(board->height(), 3);

    // Verify cell values
    EXPECT_EQ((*board)[0][0], Type::Wall);
    EXPECT_EQ((*board)[0][1], Type::Floor);
    EXPECT_EQ((*board)[0][2], Type::Box);
    EXPECT_EQ((*board)[1][0], Type::Goal);
    EXPECT_EQ((*board)[1][1], Type::At);
    EXPECT_EQ((*board)[1][2], Type::Start);
    EXPECT_EQ((*board)[2][0], Type::Wall | Type::Goal);
    EXPECT_EQ((*board)[2][1], Type::Box | Type::Goal);
    EXPECT_EQ((*board)[2][2], Type::Empty);

    // Clean up temporary file
    std::filesystem::remove(tempFile);
}

// Test print functionality by capturing stdout
TEST_F(BoardTest, Print) {
    // Create a test board with recognizable pattern
    board->resize(3, 3);
    (*board)[0][0] = Type::Wall;
    (*board)[0][1] = Type::Floor;
    (*board)[0][2] = Type::Box;
    (*board)[1][0] = Type::Goal;
    (*board)[1][1] = Type::At;
    (*board)[1][2] = Type::Start;
    (*board)[2][0] = Type::Empty;
    (*board)[2][1] = Type::Empty;
    (*board)[2][2] = Type::Empty;

    // Redirect cout to our stringstream
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    // Call print method
    board->print();

    // Restore cout
    std::cout.rdbuf(old);

    // Get the output
    std::string output = buffer.str();

    // Check output (will depend on your toChar implementation)
    std::string expected = "X.O\ng@s\n   \n";
    EXPECT_EQ(output, expected);
}
