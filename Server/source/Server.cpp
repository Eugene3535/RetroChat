#include "servernetwork.hpp"

#include <iostream>

int main()
{
     ServerNetwork server;

     if(!server.init(2525))
         return EXIT_FAILURE;

     server.run(); 

     return EXIT_SUCCESS;
}
