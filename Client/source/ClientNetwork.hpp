#pragma once

#include <SFML/Network.hpp>

#include <iostream>
#include <thread>
#include <chrono>

class ClientNetwork
{    
public:
     ClientNetwork();

     bool connect(const sf::IpAddress& address, unsigned short port);
     void receivePackets(sf::TcpSocket *);
     void sendPacket(sf::Packet &);
     void run();

private:
    sf::TcpSocket socket;
    sf::Packet last_packet;

    bool isConnected = false;
};
