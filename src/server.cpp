#include "server.hpp"


Server::Server(std::string host_name , int port){
  this -> server_fd = socket(AF_INET, SOCK_STREAM, 0);
  int rc;
  if (host_name.size() > 0){
    this -> host_name = new char [host_name.size() + 1];
    strcpy(this -> host_name, host_name.c_str());
    in_addr temp_addr;
    rc = inet_pton(AF_INET, this -> host_name, &this -> server_addr);
    if (rc < 0){
      std::cerr << "Cannot exchange host name to network address\n";
      exit(-1);
    }
  }
  else{
    this -> server_addr->sin_addr.s_addr = (INADDR_ANY);
  }
  this -> server_addr -> sin_family = AF_INET;
  this -> server_addr -> sin_port = htons(port);
  rc = bind(this -> server_fd, (sockaddr *) &(this -> server_addr), sizeof(this -> server_addr));
  if (rc < 0){
    std::cerr << "Cannot bind the server address with server descriptor\n";
    exit(-2);
  }
  this -> backlog = 3; // at most 3 client could connect
  std::cout << "Create socket for server sucessfully! The information of the server:\n";
  std::cout << "1. IP Address: " << this -> host_name << '\n';
  std::cout << "2. Port: " << this -> port << '\n';
}

void Server::listen_to_client(){
  int rc;
  rc = listen(this -> server_fd, this -> backlog);
  if (rc < 0){
    std::cerr << "Cannot listen for request\n";
    exit(-3); 
  }
  else if (rc == 0){
    std::cout << "Bind success with backlog: " << this -> backlog << '\n';
  }
}

void Server::connect_to_client(){
  sockaddr_in  client_info{};
  int conn_fd = accept(this -> server_fd, (sockaddr*)&client_info, NULL);
  if (conn_fd < 0){
    std::cerr << "Cannot connect to client\n";
    exit(-4);
  }
  this -> connect_fd = conn_fd;
  this -> list_client_info.push_back(client_info);
  
  char client_host[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &client_info, client_host, sizeof(client_host)) == NULL){
    std::cerr << "Cannot exchange client ip address to host name\n";
  }
  std::cout << "Connect sucessfully to client, client info: \n" 
    << "1. Client Address : " << client_host << '\n'
    << "2. Port: " << client_info.sin_port;
}

Server::~Server(){
  delete this -> host_name;
  this -> backlog = 0;
  this -> list_client_info.clear(); // size become 0, remove elements
  this -> list_client_info.shrink_to_fit(); // Request memory allocation
}
