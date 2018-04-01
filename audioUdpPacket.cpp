#include "audioUdpPacket.h"
#include <oscpp/client.hpp>

//using namespace boost::asio;
using boost::asio::ip::udp;

AudioUdpPacket::AudioUdpPacket():
	socket(io_service, udp::endpoint(udp::v4(), 0)),
	resolver(io_service),
	query(boost::asio::ip::udp::v4(), HOST, PORT),
	msg("/test")	// create a OSC message
{
	iterator = resolver.resolve(query);
}

AudioUdpPacket::~AudioUdpPacket() {
	socket.close();
}

void AudioUdpPacket::sendMessage(float i) {
	msg.append(i);
	std::cout << i << std::endl;
	// send the message 
	socket.send_to(boost::asio::buffer(msg.data(), msg.size()), *iterator);

	Sleep(500);
	msg.clearData();
}
