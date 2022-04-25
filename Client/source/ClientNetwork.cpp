#include "clientnetwork.hpp"

ClientNetwork::ClientNetwork(): 
    m_isConnected(false)
{
     std::cout << "Chat Client Started\n";
}

bool ClientNetwork::connect(const sf::IpAddress& address, unsigned short port)
{
    if (m_socket.connect(address, port) != sf::Socket::Done)
        std::cout << "Could not connect to the server\n";            
     else
     {
          m_isConnected = true;
          std::cout << "Connected to the server\n";
     }

    return m_isConnected;
}

void ClientNetwork::run()
{
     std::thread reception(&ClientNetwork::receivePackets, this, &m_socket);

     while(true)
     {
          if(m_isConnected)
          {
               std::string user_input;
               std::getline(std::cin, user_input);

               sf::Packet reply_packet;
               reply_packet << user_input;

               sendPacket(reply_packet);
          }
     }
}

//                                                             Private section

void ClientNetwork::receivePackets(sf::TcpSocket* socket)
{
    while (true)
    {
        if (socket->receive(m_last_packet) == sf::Socket::Done)
        {
            std::string received_string;
            std::string sender_address;
            unsigned short sender_port;

            m_last_packet >> received_string >> sender_address >> sender_port;
            std::cout << "From (" << sender_address << ":" << sender_port << "): " << received_string << '\n';
        }

        std::this_thread::sleep_for((std::chrono::milliseconds)100);
    }
}

void ClientNetwork::sendPacket(sf::Packet& packet)
{
    if (packet.getDataSize() > 0 && m_socket.send(packet) != sf::Socket::Done)
    {
        std::cout << "Could not send packet\n";
    }
}