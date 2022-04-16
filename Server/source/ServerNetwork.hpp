#pragma once

#include <iostream>
#include <SFML/Network.hpp>

#include <thread>
#include <list>
#include <chrono>
#include <string>
#include <memory>

class ServerNetwork
{
    
public:
    ServerNetwork();
    ~ServerNetwork();

    [[nodiscard]]
    bool init(unsigned short port);
    void run();

private:
    void connectClient();
    void disconnectClient(sf::TcpSocket*, size_t);

    void receivePacket(sf::TcpSocket*, size_t);
    void sendOutPacket(sf::TcpSocket* sender, sf::Packet& packet);

    void managePackets();

    sf::TcpListener                           m_listener;
    std::list<std::unique_ptr<sf::TcpSocket>> m_clients;
};
