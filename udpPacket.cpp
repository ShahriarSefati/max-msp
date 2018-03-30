#include "udpPacket.h"
#include <oscpp/client.hpp>

//using namespace boost::asio;
using boost::asio::ip::udp;

udpPacket::udpPacket():
	socket(io_service, udp::endpoint(udp::v4(), 0)),
	resolver(io_service),
	query(boost::asio::ip::udp::v4(), HOST, PORT),
	msg("/test")	// create a OSC message
{
	iterator = resolver.resolve(query);
}

udpPacket::~udpPacket() {
	socket.close();
}

void udpPacket::sendMessage(float i) {
	msg.append(i);
	std::cout << i << std::endl;
	// send the message 
	socket.send_to(boost::asio::buffer(msg.data(), msg.size()), *iterator);

	Sleep(500);
	msg.clearData();
}
