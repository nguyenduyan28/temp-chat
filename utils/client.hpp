#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <unistd.h>
#include <sstream>


class Client{
  int client_fd;

public: 
  Client();
  void connect_to_server(const char * host_name, int port) const;
  void send_message() const;

};