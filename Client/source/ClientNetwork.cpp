#include "clientnetwork.hpp"

ClientNetwork::ClientNetwork(): 
    isConnected(false)
{
     std::cout << "Chat Client Started\n";
}

bool ClientNetwork::connect(const sf::IpAddress& address, unsigned short port)
{
    if (socket.connect(address, port) != sf::Socket::Done)  
        std::cout << "Could not connect to the server\n";            
     else
     {
          isConnected = true;
          std::cout << "Connected to the server\n";
     }

    return isConnected;
}

void ClientNetwork::receivePackets(sf::TcpSocket * socket)
{
     while(true)
     {
          if(socket->receive(last_packet) == sf::Socket::Done)
          {
               std::string received_string; 
               std::string sender_address; 
               unsigned short sender_port;

               last_packet >> received_string >> sender_address >> sender_port;
               std::cout << "From (" << sender_address << ":" << sender_port << "): " << received_string << '\n';
          }
          
          std::this_thread::sleep_for((std::chrono::milliseconds)100);
     }
}

void ClientNetwork::sendPacket(sf::Packet& packet)
{
     if(packet.getDataSize() > 0 && socket.send(packet) != sf::Socket::Done)
     {
         std::cout << "Could not send packet\n";
     }
}

void ClientNetwork::run()
{
     std::thread reception(&ClientNetwork::receivePackets, this, &socket);

     while(true)
     {
          if(isConnected)
          {
               std::string user_input;
               std::getline(std::cin, user_input);

               sf::Packet reply_packet;
               reply_packet << user_input;

               sendPacket(reply_packet);
          }
     }
}
