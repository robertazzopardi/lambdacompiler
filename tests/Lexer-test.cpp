#include "gtest/gtest.h"
#include "../src/Lexer.h"

TEST(isBracketTest, test1)
{
    //arrange
    //act
    //assert

    EXPECT_EQ(lexer::Lexer::isBracket('('), true);
    EXPECT_EQ(lexer::Lexer::isBracket(')'), true);

    EXPECT_EQ(lexer::Lexer::isBracket('A'), false);
    EXPECT_EQ(lexer::Lexer::isBracket('0'), false);
}