// main.cpp
#include "../include/client.h"

int main(int argc, char **argv){
         // Note Here: The C ++ compiler puts the constructor of the non-parameters to prioritize the declaration of a function declaration.
    ClientHandler client{};
    client.sendParams(argc, argv);
}
