#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include <thread>
#include <iostream>

class Server{
  int server_fd;
  std::vector <std::thread> client_thread;
public:
  Server(){};
  Server(int port);
  void run();
  void handle_client(const sockaddr_in& client_addr);
  friend std::ostream& operator <<(std::ostream& out, const Server& server);
};

#endif