// client.h
#ifndef CLIENT_H
#define CLIENT_H

class ClientHandler
{
    public:
        ClientHandler();
        ~ClientHandler();
        bool sendParams(int argc, char **argv);
};
#endif
