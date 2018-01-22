#include <iostream>
#include <boost/asio.hpp>
#include <oscpp/client.hpp>

using namespace boost::asio;

int main(){
  
  std::cout << "Hello!" << std::endl;
  
  io_service io_service;
  ip::udp::socket socket(io_service);
  ip::udp::endpoint remote_endpoint;

  socket.open(ip::udp::v4());
  
  remote_endpoint = ip::udp::endpoint(ip::address::from_string("192.168.0.102"), 11111);

  float data[] = {1.0};
  boost::system::error_code err;
  
  while(true){
    socket.send_to(buffer(data), remote_endpoint, 0, err);
  }

  socket.close();
  
  return 0;
}
