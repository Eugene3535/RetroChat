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
     void run();

private:
    void receivePackets(sf::TcpSocket* socket);
    void sendPacket(sf::Packet& packet);

    sf::TcpSocket m_socket;
    sf::Packet    m_last_packet;

    bool m_isConnected;
};
