#include "include/types.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <vector>

// Test Type::toChar function for all valid flag combinations and invalid ones
TEST(TypesTest, ToCharReturnsCorrectCharForAllFlags) {
    // Test single flags
    EXPECT_EQ(' ', Type::toChar(Type::Empty));
    EXPECT_EQ('.', Type::toChar(Type::Floor));
    EXPECT_EQ('X', Type::toChar(Type::Wall));
    EXPECT_EQ('s', Type::toChar(Type::Start));
    EXPECT_EQ('g', Type::toChar(Type::Goal));
    EXPECT_EQ('@', Type::toChar(Type::At));
    EXPECT_EQ('O', Type::toChar(Type::Box));

    // Test combined flags (using the priority rules in toChar)

    // Wall has priority over other flags
    EXPECT_EQ('X', Type::toChar(Type::Wall | Type::Floor));
    EXPECT_EQ('X', Type::toChar(Type::Wall | Type::Start));
    EXPECT_EQ('X', Type::toChar(Type::Wall | Type::Goal));
    EXPECT_EQ('X', Type::toChar(Type::Wall | Type::At));
    EXPECT_EQ('X', Type::toChar(Type::Wall | Type::Box));
    EXPECT_EQ(
        'X', Type::toChar(Type::Wall | Type::Floor | Type::Start | Type::Goal));

    // Special Sokoban combinations
    EXPECT_EQ('*', Type::toChar(Type::Box | Type::Goal)); // Box on goal
    EXPECT_EQ('*', Type::toChar(Type::Box | Type::Goal |
                                Type::Floor)); // Box on goal with floor
    EXPECT_EQ('+', Type::toChar(Type::At | Type::Goal)); // Player on goal
    EXPECT_EQ('+', Type::toChar(Type::At | Type::Goal |
                                Type::Floor)); // Player on goal with floor

    // Box has next priority (when not on goal)
    EXPECT_EQ('O', Type::toChar(Type::Box | Type::Floor));
    EXPECT_EQ('O', Type::toChar(Type::Box | Type::Start));
    EXPECT_EQ('O', Type::toChar(Type::Box | Type::Floor | Type::Start));

    // At has next priority (when not on goal)
    EXPECT_EQ('@', Type::toChar(Type::At | Type::Floor));
    EXPECT_EQ('@', Type::toChar(Type::At | Type::Start));
    EXPECT_EQ('@', Type::toChar(Type::At | Type::Floor | Type::Start));

    // Start has next priority
    EXPECT_EQ('s', Type::toChar(Type::Start | Type::Floor));
    EXPECT_EQ('s', Type::toChar(Type::Start | Type::Goal | Type::Floor));

    // Goal has next priority
    EXPECT_EQ('g', Type::toChar(Type::Goal | Type::Floor));

    // Floor is lowest priority
    EXPECT_EQ('.', Type::toChar(Type::Floor));

    // Test invalid flags (any bit pattern not covered above)
    // Create an invalid flag pattern - 0x40 is not defined in Type::Flag
    Type::Flag invalidFlag = 0x40;
    EXPECT_EQ('?', Type::toChar(invalidFlag));

    // Test another invalid flag - 0x80
    invalidFlag = 0x80;
    EXPECT_EQ('?', Type::toChar(invalidFlag));

    // Test a combination of valid and invalid flags
    EXPECT_EQ('X', Type::toChar(Type::Wall |
                                0x40)); // Wall should still have priority

    // Test for all possible bit combinations outside defined flags
    for (Type::Flag i = 0x40; i != 0; i <<= 1) {
        EXPECT_EQ('?', Type::toChar(i));
    }
}
