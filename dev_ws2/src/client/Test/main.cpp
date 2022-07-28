// main.cpp
#include <gtest/gtest.h> 
// #include <gmock/gmock.h>

int my_argc;
char** my_argv;

int main(int argc, char** argv) {
    // ::testing::InitGoogleMock(&argc, argv);
         // Note that it is gtest, not GMOCK
    ::testing::InitGoogleTest(&argc, argv); 
    // Runs all tests using Google Test.
    my_argc = argc;
    my_argv = argv;
    return RUN_ALL_TESTS();
}
