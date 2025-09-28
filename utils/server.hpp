#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include <thread>

class Server{
  int server_fd;
  std::vector <std::thread> client_thread;
public:
  Server(){};
  Server(int port);
};
