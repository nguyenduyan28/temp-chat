#include "utils/server.hpp"


Server::Server(int port){
  const int DEFAULT_PROTOCOL{0};
  const int DEFAULT_BACKLOG {3}; // at most 3 clients could wait to connect
  this -> server_fd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
  sockaddr_in server_addr{
    AF_INET, // sin_family
    htons(port), // port value
    INADDR_LOOPBACK, // ipv4 value
  };
  bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr));
  listen(server_fd, DEFAULT_BACKLOG);
}