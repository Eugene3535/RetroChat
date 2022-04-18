#pragma once

#include <iostream>
#include <SFML/Network.hpp>

#include <thread>
#include <vector>
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
    void disconnectClient(sf::TcpSocket* socket, std::size_t position);

    void receivePacket(sf::TcpSocket* socket, std::size_t position);
    void sendOutPacket(sf::Packet& packet, sf::TcpSocket* socket);

    sf::TcpListener                             m_listener;
    std::vector<std::unique_ptr<sf::TcpSocket>> m_clients;
};
