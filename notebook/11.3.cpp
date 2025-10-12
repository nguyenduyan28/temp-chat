#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <sstream>


std::string network_to_hex(const std::string& nw){
  // from string to int
  try{
    auto hex_value = static_cast<uint16_t> (std::stoi(nw, nullptr, 10));
    uint16_t nw_value = (hex_value);
    std::stringstream ss;
    ss << std::hex << nw_value;
    return "0x" + ss.str();
  }
  catch (const std::exception& e){
    std::cerr << "Invalid number" << nw << '\n';
    return "-1";
  }
}


int main(int argc, char ** argv){
  if (argc < 2){
    std::cerr << "The input argument is empty, please input the valid hex value\n";
    exit(-1);
  }
  std::string hex_string {argv[1]};
  std::cout << network_to_hex(hex_string);
  return 0;
}