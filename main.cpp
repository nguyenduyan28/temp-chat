#include "server.hpp"
#include "client.hpp"


int main(){
  Server server(80);
  Client client(80);
  sockaddr_in address{};
  server.handle_client()
}