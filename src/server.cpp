#include "server.hpp"


Server::Server(const std::string& host_name , int port): server_fd(socket(AF_INET, SOCK_STREAM, 0)), connect_fd(-1), port(port), host_name(host_name){
  if (!this -> host_name.empty()){
    int rc{};
    in_addr temp_addr{};
    rc = inet_pton(AF_INET, reinterpret_cast<const char * >(&this -> host_name), &(temp_addr));
    if (rc < 0){
      std::cerr << "Cannot exchange host name to network address\n";
      exit(-1);
    }
    this -> server_addr.sin_addr.s_addr = temp_addr.s_addr;
  }
  else {
    this -> server_addr.sin_addr.s_addr = (INADDR_ANY);
  }
  this -> server_addr.sin_family = AF_INET;
  this -> server_addr.sin_port = htons(port);
  if (bind(this -> server_fd, reinterpret_cast <sockaddr*> (&this->server_addr), sizeof(this -> server_addr)) < 0){
    perror("bind");
    exit(-11);
  }
  this -> backlog = 3; // at most 3 client could connect
  std::cout << "Create socket for server successfully! The information of the server:\n";
  std::cout << "1. IP Address: " << this -> host_name << '\n';
  std::cout << "2. Port: " << this -> port << '\n';
}

void Server::listen_to_client() const{
  int rc{};
  rc = listen(this -> server_fd, this -> backlog);
  if (rc < 0) {
    std::cerr << "Cannot listen for request\n";
    exit(-3);
  }
  else if (rc == 0) {
    std::cout << "Bind success with backlog: " << this -> backlog << '\n';
  }
}

void Server::connect_to_client(){
  sockaddr_in  client_info{};
  socklen_t len = sizeof(client_info);
  const int conn_fd = accept(this -> server_fd, reinterpret_cast<sockaddr*>(&client_info), &len);
  if (conn_fd < 0){
    perror("accept");
    exit(-12);
  }
  this -> connect_fd = conn_fd;
  this -> list_client_info.push_back(client_info);

  char client_host[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &client_info, client_host, sizeof(client_host)) == NULL){
    std::cerr << "Cannot exchange client ip address to host name\n";
  }
  std::cerr << "Connect successfully to client, client info: \n"
    << "1. Client Address : " << client_host << '\n'
    << "2. Port: " << client_info.sin_port;
}

void Server::show_message() const {
  const int max_size = 50;
  std::vector <char> buffer(max_size, 0);
  while (true){
    ssize_t n = recv(this -> connect_fd, buffer.data(), max_size, 0);
    if (n > 0){
      std::cout << "\nMessage from client: ";
      std::cout << buffer.data() << '\n';
      if (strcmp(buffer.data(),"Exit Server") == 0){
        std::cout << "Client exited.\n";
        close(this -> connect_fd);
        break;
      }
      std::fill(buffer.begin(), buffer.end(), 0);
    }
  }
}

Server::~Server(){
  this -> host_name.clear();
  this -> host_name.shrink_to_fit();
  this -> backlog = 0;
  this -> list_client_info.clear(); // size become 0, remove elements
  this -> list_client_info.shrink_to_fit(); // Request memory allocation
}
