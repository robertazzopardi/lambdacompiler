#include "gtest/gtest.h"
#include "../src/FileHandler.h"

TEST(exampletest, test1)
{
    //arrange
    //act
    //assert

    EXPECT_EQ(fhandler::FileHandler::temp(1), 1);

}
