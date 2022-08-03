// clientTest.cpp
#include "gtest/gtest.h"
#include "iostream"
#include "../include/client.h"
#include "../include/params.h"

TEST(ClientHandler, sendParams)
{
         // The interaction mode of the test cannot be changed. Since the actual effect of the client is in the command line input parameters,
         // This is also the effect here
    //float** my_argv[2]={200,300};
    ClientHandler client{};
    EXPECT_EQ(true, client.sendParams(my_argc, my_argv));
}
