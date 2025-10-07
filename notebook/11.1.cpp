#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <iomanip> // for hex
#include <sstream>

uint32_t big_to_little(uint32_t big_endian){
  // big-endian is network by order, little endian is host by order
  return ntohl(big_endian); // l for long
}


uint32_t little_to_big(uint32_t little_endian){
  return htonl(little_endian);
}



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
    ss.str("");
    uint32_t host_value = big_to_little(output_address.s_addr);
    ss << std::hex << host_value;
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
    char buffer[INET_ADDRSTRLEN];

    uint32_t address_num = little_to_big(stol(hex, NULL, 16));
    in_addr address {address_num};
    if (inet_ntop(AF_INET, &address, buffer, sizeof(buffer)) != NULL){
      host_name_ip.push_back(buffer);
    }
    else{
      std::cout << "Cannot exchange value\n";
      exit(-2);
    }
  }
  return host_name_ip;
}



int main(){
  std::vector<std::string> hostname_list{
    "127.0.0.1",
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
  ip.insert(ip.begin(), hostname_list.begin(), hostname_list.end());
  hex.insert(hex.end(), hex_value.begin(), hex_value.end());
  if (hex.size() != ip.size()){
    std::cerr << "The size is not equal\n";
    exit(-1);
  }
  std::cout << "PRACTICE 11.1 ANSWER: \n";
  for (int i = 0; i < hex.size(); i++){
    std::cout << ip[i] << " - " << hex[i] << '\n';
  }


  
}