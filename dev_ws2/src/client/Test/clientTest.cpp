// clientTest.cpp
#include "gtest/gtest.h"

#include "../include/client.h"
#include "../include/params.h"

TEST(ClientHandler, sendParams)
{
         // The interaction mode of the test cannot be changed. Since the actual effect of the client is in the command line input parameters,
         // This is also the effect here
    ClientHandler client{};
    EXPECT_EQ(true, client.sendParams(my_argc, my_argv));
}
