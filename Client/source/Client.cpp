#include "ClientNetwork.hpp"

int main()
{
     ClientNetwork client_network;
     client_network.connect("localHost", 2525);
     client_network.run();

     return EXIT_SUCCESS;
}
