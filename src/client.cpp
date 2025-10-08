#include "client.hpp"

Client::Client(){
  this -> client_fd = socket(AF_INET, SOCK_STREAM, 0);
}

void Client::connect_to_server(const char * host_name, int port){
  sockaddr_in server_addr;
  if (strlen(host_name) == 0){
    server_addr.sin_addr.s_addr = INADDR_ANY;
  }
  else{
    inet_pton(AF_INET, host_name, &server_addr.sin_addr);
  }
  server_addr.sin_port = htons(port);
  server_addr.sin_family = AF_INET;
  int rc = connect(this -> client_fd, (sockaddr*)&server_addr, sizeof(server_addr));
  if (rc == 0){
    std::cout << "Connect to server sucessfully!\n"; 
  }
  else{
    perror("connect");
    std::cerr << "Cannot connect to server...\n"; 
    exit(-1);
  }
}

void Client::send_message(){
  std::string message{};
  while (true){
    std::cerr << "\nInput the message: ";
    std::getline(std::cin, message);
    ssize_t byte_send = send(this -> client_fd, message.data(), message.length(), 0);
    if (message == "Exit Server"){
      close(this -> client_fd);
      break;
    }
    message.clear();
  }
}