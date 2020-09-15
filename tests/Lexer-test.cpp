#include "gtest/gtest.h"
#include "../src/Lexer.h"

TEST(exampletestLexer, test1)
{
    //arrange
    //act
    //assert

    EXPECT_EQ(lexer::Lexer::isBracket('('), false);
}