#include "md5.h"
#include "CreationSystem.h"
#include <iostream>
#include <fstream>
#include <random>

CreationSystem::CreationSystem(){}

std::string CreationSystem::getUsername(){return username;}

std::string CreationSystem::getPassword(){return password;}

int CreationSystem::getUserClearance(){return user_clearance;}

void CreationSystem::setUsername(std::string user_name){username = user_name;}

void CreationSystem::setPassword(std::string pass_word){password = pass_word;}

void CreationSystem::setUserClearance(int userclearance){user_clearance = userclearance;}

void CreationSystem::store_user(){

  bool digit_true;
  std::string user_name;
  std::string pass_word;
  std::string confirm_password;
  int userclearance = 0;
  int salt_random = 0;
  int counter = 0;
  std::string salt = "";
  char* salt_point;
  std::fstream salt_shadow;
  srand(time(0));

  std::cout << "Enter Username: " << std::endl;
  std::cin >> user_name;

  setUsername(user_name);

  std::cout << "Password Should Be Minimum 8 Characters Long, \nMix Of Digits And Letters,\nEnter A Password: " << std::endl;
  std::cin >> pass_word;

  for(char &character : pass_word){//check every character to see if at least one is a digit
    if(isdigit(character) != 0){
     digit_true = true;
     break;
   } else {
      digit_true = false;
   }
 }

  while(digit_true == false) {//if no digit, loop until password has digit in it

    std::cerr << "Password does not have any digits, Please Re-enter Password: " << std::endl;
    std::cin >> pass_word;

    for(char &character : pass_word){//if password has digit, break the loop
      if(isdigit(character) == true){
       digit_true = true;
       break;
     }
   }
  }


  if(pass_word.find('0') != std::string::npos ||
  pass_word.find('1') != std::string::npos ||
  pass_word.find('2') != std::string::npos ||
  pass_word.find('3') != std::string::npos ||
  pass_word.find('4') != std::string::npos ||
  pass_word.find('5') != std::string::npos ||
  pass_word.find('6') != std::string::npos ||
  pass_word.find('7') != std::string::npos ||
  pass_word.find('8') != std::string::npos ||
  pass_word.find('9') != std::string::npos) {

    std::cout << "Confirm Password: " << std::endl;
    std::cin >> confirm_password;

    while(pass_word != confirm_password){
      std::cout << "Password Mismatch, Re-enter Confirmation: " << std::endl;
      std::cin >> confirm_password;
    }

    if(pass_word == confirm_password){
      setPassword(confirm_password);
    }

   }

  std::cout << "Enter User Clearance (0 or 1 or 2 or 3): " << std::endl;
  std::cin >> userclearance;

  while(userclearance < 0 || userclearance > 3){
    std::cerr << "User Clearance Must Be Between 0 and 3 Inclusive" << std::endl;
    std::cin >> userclearance;
  }

  setUserClearance(userclearance);

  size_t salt_size = 8;

  for(int a = 0; a < 8; a++){
    if(salt.length() == salt_size){ //if salt length is 8, stop creating random numbers and adding to salt string.
      break;
    }
    salt_random = rand() % (10 + 1);
    salt += std::to_string(salt_random);
  }

  std::string pass_salt;
  pass_salt += getPassword(); //concat password into string
  pass_salt += salt; //concat salt into string

  salt_shadow.open("salt.txt", std::ios::app);

  salt_shadow << getUsername() << ":" << salt << std::endl;

  salt_shadow.close();

  MD5 md5;

  salt_point = &*pass_salt.begin(); //changing string to char* for hashing

  salt_shadow.open("shadow.txt", std::ios::app);

  salt_shadow << getUsername() << ":" << md5.digestString(salt_point) << ":" << getUserClearance() << std::endl; //Write to file username, hashed password and salt, and user clearance.

  salt_shadow.close();
}
