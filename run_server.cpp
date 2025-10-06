#include "server.hpp"

int main(){
  std::string host_name{};
  int port{};
  std::cout << "Input the server host (e.g 127.0.0.1): ";
  std::cin >> host_name;
  std::cout << "Input the server port (e.g 80): ";
  std::cin >> port;
  Server server(host_name, port);
  server.listen_to_client();
  server.connect_to_client();
}