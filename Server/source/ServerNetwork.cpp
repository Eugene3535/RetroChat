#include "servernetwork.hpp"

ServerNetwork::ServerNetwork() 
{  
}

ServerNetwork::~ServerNetwork()
{
    m_clients.clear();
}

bool ServerNetwork::init(unsigned short port)
{
    std::cout << ("Chat Server Started\n");

    if (m_listener.listen(port) != sf::Socket::Done)
    {
        std::cout << ("Could not listen\n");
        return false;
    }

    return true;
}

void ServerNetwork::run()
{
    std::thread connection(&ServerNetwork::connectClient, this);
    managePackets();
}

//                                                                          Private section

void ServerNetwork::connectClient()
{
    while (true) 
    {
        auto new_client = std::make_unique<sf::TcpSocket>();

        if (m_listener.accept(*new_client) == sf::Socket::Done) 
        {
            new_client->setBlocking(false);
            std::cout << "Added client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort() << " on slot " << m_clients.size() << '\n';
            m_clients.push_back(std::move(new_client));           
        }
        else
        {
            std::cout << "Server m_listener error, restart the server\n";
            break;
        }
    }
}

void ServerNetwork::disconnectClient(sf::TcpSocket* socket_pointer, size_t position)
{
    std::cout << "Client " << socket_pointer->getRemoteAddress() << ":" << socket_pointer->getRemotePort() << " disconnected\n";
    socket_pointer->disconnect();

    auto it = m_clients.begin();
    std::advance(it, position);

    m_clients.erase(it);
}

void ServerNetwork::sendOutPacket(sf::TcpSocket* sender, sf::Packet& packet)
{
    for (auto& c : m_clients) 
    {
        sf::TcpSocket* client = c.get();

        if (client != sender)
        {
            if (client->send(packet) != sf::Socket::Done)
            {
                std::cout << "Could not send packet in chat\n";
            }
        }
    }
}

void ServerNetwork::receivePacket(sf::TcpSocket* client, size_t iterator) 
{
    sf::Packet packet;

    if (client->receive(packet) == sf::Socket::Disconnected)
    {
        disconnectClient(client, iterator);
    }
    else 
    {
        if (packet.getDataSize() > 0) 
        {
            // std::string received_message;
            // packet >> received_message;
            // packet.clear();
            // packet << received_message << client->getRemoteAddress().toString() << client->getRemotePort();

            packet << client->getRemoteAddress().toString() << client->getRemotePort();

            sendOutPacket(client, packet);
            // std::cout << client->getRemoteAddress().toString() << ":" << client->getRemotePort() << " '" << received_message << "'\n"; !!! -> For server console only
        }
    }
}

void ServerNetwork::managePackets() 
{
    while (true)
    {
        size_t iterator = 0;

        for (auto& client : m_clients) 
        {
            receivePacket(client.get(), iterator);
            iterator++;
        }

        std::this_thread::sleep_for((std::chrono::milliseconds)100);
    }
}


