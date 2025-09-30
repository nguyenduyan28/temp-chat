#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <iomanip> // for hex
#include <sstream>

std::vector <std::string> decimal_to_hex(std::vector<std::string> hostname_list){
  in_addr output_address;
  std::stringstream ss;
  std::vector <std::string> list_ip_hex;
  std::string buffer;
  for (auto hostname : hostname_list){
    const char * c = hostname.c_str();
    int rc = inet_pton(AF_INET, c, &output_address);
    if (rc == 0){
      std::cerr << "Source is invalid dotted decimal" << '\n';
      exit(1);
    }
    else if (rc < 0){
      std::cerr << "Error in transform ip address" << '\n';
      exit(-1);
    }
    ss << std::hex << output_address.s_addr;
    buffer = ss.str();
    std::transform(buffer.begin(), buffer.end(), buffer.begin(),
    [](unsigned char c){
      return std::toupper(c);
    });
    list_ip_hex.push_back("0x" + buffer);
  }
  return list_ip_hex;
}


std::vector <std::string> hex_to_decimal(std::vector<std::string> hex_value){
  std::vector <std::string> host_name_ip;

  for (auto hex: hex_value){
    char * buffer;
    uint32_t address = stoi(hex);
    const char * c = inet_ntop(AF_INET, &address, buffer, sizeof(c));
    host_name_ip.push_back(buffer);
  }
  return host_name_ip;
}



int main(){
  std::vector<std::string> hostname_list{
    "107.212.122.205",
    "64.12.149.13",
    "107.212.96.29"
  };
  std::vector <std::string> hex_value{
    "0x00000080",
    "0xFFFFFF00",
    "0x0A010140"
  };
  
  std::vector<std::string> hex = decimal_to_hex(hostname_list);
  std::vector<std::string> ip = hex_to_decimal(hex_value);
  ip.insert(ip.end(), hostname_list.begin(), hostname_list.end());
  hex.insert(hex.begin(), hex_value.begin(), hex_value.end());
  if (hex.size() != ip.size()){
    std::cerr << "The size is not equal\n";
    exit(-1);
  }
  std::cout << "PRACTICE 11.1 ANSWER: \n";
  for (int i = 0; i < hex.size(); i++){
    std::cout << ip[i] << " - " << hex[i] << '\n';
  }


  
}