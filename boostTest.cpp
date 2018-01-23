#include <iostream>
#include <boost/asio.hpp>
#include <oscpp/client.hpp>
#include "tnyosc.hpp"

#define HOST ("192.168.0.102")
#define PORT ("11111")

using namespace boost::asio;

size_t makePacket(void* buffer, size_t size)
{
	// Construct a packet
	OSCPP::Client::Packet packet(buffer, size);
	packet
		// Open a bundle with a timetag
		.openBundle(1234ULL)
		// Add a message with two arguments and an array with 6 elements;
		// for efficiency this needs to be known in advance.
		.openMessage("/s_new", 2 + OSCPP::Tags::array(6))
		// Write the arguments
		.string("sinesweep")
		.int32(2)
		.openArray()
		.string("start-freq")
		.float32(330)
		.string("end-freq")
		.float32(990)
		.string("amp")
		.float32(0.4)
		.closeArray()
		// Every `open` needs a corresponding `close`
		.closeMessage()
		// Add another message with one argument
		.openMessage("/n_free", 1)
		.int32(1)
		.closeMessage()
		// And nother one
		.openMessage("/n_set", 3)
		.int32(1)
		.string("wobble")
		// Numeric arguments are converted automatically
		// (see below)
		.int32(31)
		.closeMessage()
		.closeBundle();
	return packet.size();
}

int main(){
  
  std::cout << "Hello!" << std::endl;
  /*
  io_service io_service;
  ip::udp::socket socket(io_service);
  ip::udp::endpoint remote_endpoint;

  socket.open(ip::udp::v4());
  
  remote_endpoint = ip::udp::endpoint(ip::address::from_string("192.168.0.102"), 11111);
  boost::system::error_code err;

  float data[] = {1.0};
  void *buffer = 0;
  size_t bufferSize = 20;
  makePacket(buffer, bufferSize);
  */

  // boost::asio library for sending UDP packets
  boost::asio::io_service io_service;
  ip::udp::socket socket(io_service, ip::udp::endpoint(ip::udp::v4(), 0));
  ip::udp::resolver resolver(io_service);
  ip::udp::resolver::query query(ip::udp::v4(), HOST, PORT);
  ip::udp::resolver::iterator iterator = resolver.resolve(query);

  // create a OSC message
  tnyosc::Message msg("/test");


float i = 0; 

  while(true){
    //socket.send_to(buffer(data), remote_endpoint, 0, err);
	//socket.send_to(buffer, remote_endpoint, 0, err);
	  
	  //msg.set_address("/test");
	  // create message
	  i = 127 * ((float)rand() / (RAND_MAX));
	  
	  std::cout << i << std::endl;
	  msg.append(i);

	// send the message 
	  socket.send_to(boost::asio::buffer(msg.data(), msg.size()), *iterator);
	  
	  Sleep(500);  
	  msg.clearData();
  }

  socket.close();
  
  return 0;
}
