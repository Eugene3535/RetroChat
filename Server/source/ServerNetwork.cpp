#include "servernetwork.hpp"

ServerNetwork::ServerNetwork() 
{  
    m_clients.reserve(25);
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

    while (true)
    {
        for (std::size_t position = 0; auto & client : m_clients)
        {
            receivePacket(client.get(), position);
            position++;
        }
        std::this_thread::sleep_for((std::chrono::milliseconds)100);
    }
}

//                                                                      Private section

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

void ServerNetwork::disconnectClient(sf::TcpSocket* socket, size_t position)
{
    std::cout << "Client " << socket->getRemoteAddress() << ":" << socket->getRemotePort() << " disconnected\n";
    socket->disconnect();

    if (position < m_clients.size())
    {
        m_clients[position] = std::move(m_clients.back());
        m_clients.pop_back();
    }
}

void ServerNetwork::sendOutPacket(sf::Packet& packet, sf::TcpSocket* socket)
{
    for (auto& client : m_clients) 
    {
        if (client.get() != socket) 
        {
            if (client->send(packet) != sf::Socket::Done) 
                std::cout << "Could not send packet in chat\n";           
        }
    }
}

void ServerNetwork::receivePacket(sf::TcpSocket* socket, std::size_t position) 
{
    sf::Packet packet;

    if (socket->receive(packet) == sf::Socket::Disconnected)   
        disconnectClient(socket, position);   
    else    
        if (packet.getDataSize() > 0) 
        {
            packet << socket->getRemoteAddress().toString() << socket->getRemotePort();

            sendOutPacket(packet, socket);
        }   
}
