#include "client.hpp"


int main(){
  Client client;
  std::string host_name{};
  int port{};
  std::cout << "Input the server host (e.g 127.0.0.1): ";
  std::cin >> host_name;
  std::cout << "Input the server port (e.g 80): ";
  std::cin >> port;
  client.connect_to_server(host_name.c_str(), port);
}