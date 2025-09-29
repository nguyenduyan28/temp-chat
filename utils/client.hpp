#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>


class Client{
  int client_fd{};
  int port{};

  public:
  Client(){};
  Client(int port);
  void connect_server(const sockaddr_in& server_addr);


};