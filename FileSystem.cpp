#include <iostream>
#include "md5.h"
#include "CreationSystem.h"
#include "LoginSystem.h"

int main(int argc, char *argv[]){

  MD5 test_md5;
  std::cout << "Test MD5: " << test_md5.digestString("This is a test") << std::endl;

  int retrieve_func_int = 0;

  if(argc > 1){
    std::string start_creation(argv[1]);
    if(start_creation == "-i"){
      std::cout << "Argument Valid" << std::endl;
      CreationSystem create_user;
      create_user.store_user();
    } else {
      std::cerr << "Incorrect Arguments" << std::endl;
    }
  } else {
    LoginSystem retrieve_user;
    retrieve_func_int = retrieve_user.retrieve_info();
    if(retrieve_func_int == -1){
      return 0;
    }
    retrieve_user.options_menu();
  }

  return 0;
}
