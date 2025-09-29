#include "server.hpp"


Server::Server(int port){
  constexpr int DEFAULT_PROTOCOL{0};
  constexpr int DEFAULT_BACKLOG {3}; // at most 3 clients could wait to connect
  this -> server_fd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
  sockaddr_in server_addr{
    AF_INET, // sin_family
    static_cast<sa_family_t> (INADDR_LOOPBACK), // ipv4 value
    static_cast<in_port_t> (htons(port)), // port value
  };
  bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr));
  listen(server_fd, DEFAULT_BACKLOG);
  std::cout << "Listening at: " << server_fd << "\n";
}


void Server::handle_client(const sockaddr_in& client_addr){
  while(true){
    int connected_fd = connect(this -> server_fd, (sockaddr*)&client_addr, sizeof(client_addr));
    if (connected_fd == -1){
      std::cerr << "Error when connecting..";
      exit(1);
    }
    else{
      std::cerr << "Connecting successfully, file descriptor is: " << connected_fd << '\n';
    }
  }
}

std::ostream& operator <<(std::ostream& out, const Server& server){
  out << "THIS IS THE INFORMATION OF THE SERVER: \n";
  out << "1. SERVER_FD: " << server.server_fd << '\n';
  return out;
}