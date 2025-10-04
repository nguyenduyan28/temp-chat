#include <arpa/inet.h>
#include <string>
#include <iostream>


uint16_t hex_to_network(std::string hex_string){
  // from string to int
  try{
    uint16_t hex_value = static_cast<uint16_t> (std::stoi(hex_string, NULL, 0));
    return htons(hex_value);
  }
  catch (const std::exception& e){
    std::cerr << "Invalid number" << hex_string << '\n';
    return 0;
  }
}


int main(int argc, char ** argv){
  if (argc < 2){
    std::cerr << "The input argument is empty, please input the valid hex value\n";
    exit(-1);
  }
  std::string hex_string {argv[1]};
  std::cout << hex_to_network(hex_string);
  return 0;
}
