#include "client.hpp"


Client::Client(int port){
  constexpr int DEFAULT_PROTOCOL{0};
  this -> client_fd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
}


void Client::connect_server(const sockaddr_in& server_addr){
  connect(this -> client_fd, (sockaddr*)&server_addr, sizeof(server_addr));
  if (connect == 0){
    std::cerr << "Connect succesfully to server.\n";
  }
  else{
    std::cerr << "Error at connection.\n";
    exit(1);
  }
}