#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <iostream>
#include <unistd.h>

class Server{
  int server_fd;
  int connect_fd;
  char * host_name;
  int port;
  int backlog;
  sockaddr_in server_addr;
  std::vector <sockaddr_in> list_client_info;
public:
  Server(){};
  Server(std::string host_name, int port);
  void listen_to_client();
  void connect_to_client();
  void show_message();
  ~Server();
};

#endif