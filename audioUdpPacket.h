#ifndef _AUDIO_UDP_PACKET_H
#define _AUDIO_UDP_PACKET_H

#include <iostream>
#include <boost/asio.hpp>
#include "tnyosc.hpp"

using boost::asio::ip::udp;

//#define HOST ("192.168.0.102")
#define HOST ("10.194.102.78")
#define PORT ("11111")

class AudioUdpPacket
{
public:
	AudioUdpPacket();
	~AudioUdpPacket();

	void sendMessage(float i);

private:
	tnyosc::Message msg;
	
	boost::asio::io_service io_service;
	udp::socket socket;
	udp::resolver resolver;
	udp::resolver::query query;
	udp::resolver::iterator iterator;


};

#endif _AUDIO_UDP_PACKET_H
