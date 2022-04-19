#include "ClientNetwork.hpp"

int main()
{
     ClientNetwork client_network;
     client_network.Connect("localHost", 2525);
     client_network.Run();

     return EXIT_SUCCESS;
}
