#include "md5.h"
#include "LoginSystem.h"
#include <fstream>
#include <string>
#include <iostream>

LoginSystem::LoginSystem(){}

int LoginSystem::getUserClearance(){return user_clearance;}
void LoginSystem::setUserClearance(int userclearance){user_clearance = userclearance;}
std::string LoginSystem::getUsername(){return username;}
void LoginSystem::setUsername(std::string user_name){username = user_name;}

int LoginSystem::retrieve_info(){

  std::fstream load_file;
  std::string user_name;
  std::string pass_word;
  std::string file_user;
  std::string file_salt;
  std::string shadow_file_user;
  std::string shadow_file_hash;
  std::string shadow_file_clearance;
  MD5 md5;
  char* hash;
  bool user_name_confirm = false;
  bool shadow_user_name_confirm = false;

  load_file.open("salt.txt");

  std::cout << "Enter Username: " << std::endl;
  std::cin >> user_name;

  std::cout << "Enter Password: " << std::endl;
  std::cin >> pass_word;

  while(std::getline(load_file, file_user, ':')){
    std::getline(load_file, file_salt);
    if(user_name == file_user){ //if the user is found in the salt.txt file, send message and break the loop
      user_name_confirm = true;
      std::cout << user_name << " found in salt.txt\n" << "salt retrieved: " << file_salt << std::endl;
      break;
    }
  }

  if(user_name_confirm == false){//if the user is not found, send error and return -1
    load_file.close();
    std::cerr << "The Username Does Not Exist, Please Create User.\nExiting System...." << std::endl;
    return -1;
  }


  load_file.close();
  load_file.open("shadow.txt");

  while(std::getline(load_file, shadow_file_user, ':')){
    std::getline(load_file, shadow_file_hash, ':');
    std::getline(load_file, shadow_file_clearance);
    if(user_name == shadow_file_user){ //if username is found in the shadow file, start password hashing.
      shadow_user_name_confirm = true;
      std::cout << "Hashing..." << std::endl;
      pass_word += file_salt;
      hash = &*pass_word.begin();

      if(md5.digestString(hash) == shadow_file_hash){ //if the hash of the password enterd matches with hashed password in shadow file, then user is authenticated
        std::cout << "Authentication For User " << user_name << " Complete.\n" << "The Clearance for " <<
        user_name << " is " << shadow_file_clearance << std::endl;
        setUsername(user_name);
        setUserClearance(std::stoi(shadow_file_clearance));
        break;
      } else { //if hash doesn't match with hash in shadow file, send error
        load_file.close();
        std::cerr << "Password Mismatch. Exiting System..." << std::endl;
        return -1;
      }
    }
  }

  if(shadow_user_name_confirm == false){ //if the username was not found in the shadowfile, send error and return -1
    load_file.close();
    std::cerr << "The Username Does Not Exist, Please Create User.\nExiting System...." << std::endl;
    return -1;
  }

  load_file.close();
}

void LoginSystem::options_menu(){

  std::ifstream files_store;
  std::ofstream files_store_input;
  char option;
  char shutdown;
  std::string filename;
  std::string file_store_user;
  std::string files_store_filename;
  std::string files_store_classification;
  std::string filename_storage[20];
  int file_counter = 0;
  bool login_system_exit = false;
  bool file_exist = false;
  bool correct_option = false;
  bool shutdown_option = false;

  do {
    files_store.open("Files.store");
    files_store_input.open("Files.store",std::ios::app);


    if(!files_store){//if Files.store doesn't exist for input, send error
      std::cerr << "Files.txt doesn't exit" << std::endl;
    }

    if(!files_store_input){//if Files.store doesn't exist for output, send error
      std::cerr << "Files.txt doesn't exit" << std::endl;
    }

  std::cout << "Options: (C)reate, (A)ppend, (R)ead, (W)rite, (L)ist, (S)ave, (E)xit." << std::endl;
  std::cin >> option;

  if(option == 'C'){//if correct option input, set correct option to true
    correct_option = true;
  } else if(option == 'A'){
    correct_option = true;
  } else if(option == 'R'){
    correct_option = true;
  } else if(option == 'W'){
    correct_option = true;
  } else if(option == 'L'){
    correct_option = true;
  } else if(option == 'S'){
    correct_option = true;
  } else if(option == 'E'){
    correct_option = true;
  }

  while(correct_option == false){ //if correct option not input, loop till correct option is input.

    std::cerr << "Only Options Are: C, A, R, W, L, S, E\nOptions: (C)reate, (A)ppend, (R)ead, (W)rite, (L)ist, (S)ave, (E)xit." << std::endl;
    std::cin >> option;

    if(option == 'C'){
      correct_option = true;
    } else if(option == 'A'){
      correct_option = true;
    } else if(option == 'R'){
      correct_option = true;
    } else if(option == 'W'){
      correct_option = true;
    } else if(option == 'L'){
      correct_option = true;
    } else if(option == 'S'){
      correct_option = true;
    } else if(option == 'E'){
      correct_option = true;
    }

  }

  if(option == 'C'){//Create file

    std::cout << "Enter Filename: " << std::endl;
    std::cin >> filename;

    while(std::getline(files_store, files_store_filename, ':')){
      std::getline(files_store, file_store_user, ':');
      std::getline(files_store, files_store_classification);

      if(filename == files_store_filename){//if the filename already exist then go back to menu(1)
        file_exist = true;
        std::cerr << "This File Name Already Exists." << std::endl;
      }
    }

    if(file_exist == false){//if the file name doesn't exist, send message regarding filename, file owner and classification.
      std::cout << "File: " << filename << "\nOwner: " << getUsername() << "\nClassification: " << getUserClearance() <<
      "\nPlease use the save option to store your created file."<< std::endl;
      filename_storage[file_counter] = filename; //store file name in string array at position file_counter, for saving later
      file_counter++;
    }

    } else if(option == 'A'){

      std::cout << "Enter Filename: " << std::endl;
      std::cin >> filename;

      while(std::getline(files_store, files_store_filename, ':')){
        std::getline(files_store, file_store_user, ':');
        std::getline(files_store, files_store_classification);

        if(filename == files_store_filename){
          file_exist = true;
          break;
        }
      }

     if(file_exist == true){//if file exists, check user clearance. Write up and read down principle.
       std::cout << "This File Exists." << std::endl;

      if(getUserClearance() <= std::stoi(files_store_classification)){
        if(getUserClearance() == 0){//clearance of 0 can't do anything except create files.
          std::cerr << "Failure Writing To File. Clearance is 0." << std::endl;
        } else {
          std::cout << "Success Appending From File. Correct Clearance" << std::endl;
        }
      } else {
        std::cerr << "Failure Appending From File. Lower Clearance Required." << std::endl;
      }
     }

      if(file_exist == false){
        std::cout << "File Does Not Exist." <<  std::endl;
      }

    } else if(option == 'R'){

      std::cout << "Enter Filename: " << std::endl;
      std::cin >> filename;

      while(std::getline(files_store, files_store_filename, ':')){
        std::getline(files_store, file_store_user, ':');
        std::getline(files_store, files_store_classification);

        if(filename == files_store_filename){
          file_exist = true;
          break;
        }
      }

     if(file_exist == true){
       std::cout << "This File Exists." << std::endl;

      if(getUserClearance() >= std::stoi(files_store_classification)){//if file exists, check user clearance. Write up and read down principle.
        if(getUserClearance() == 0){
          std::cerr << "Failure Writing To File. Clearance is 0." << std::endl;
        }else{
          std::cout << "Success Reading From File. Correct Clearance" << std::endl;
        }
      } else {
        std::cerr << "Failure Reading From File. Higher Clearance Required." << std::endl;
      }
     }

      if(file_exist == false){
        std::cerr << "File Does Not Exist." <<  std::endl;
      }

    } else if(option == 'W'){

      std::cout << "Enter Filename: " << std::endl;
      std::cin >> filename;

      while(std::getline(files_store, files_store_filename, ':')){
        std::getline(files_store, file_store_user, ':');
        std::getline(files_store, files_store_classification);

        if(filename == files_store_filename){
          file_exist = true;
          break;
        }
      }

     if(file_exist == true){
       std::cout << "This File Exists." << std::endl;

      if(getUserClearance() == std::stoi(files_store_classification)){//if file exists, check user clearance. Write up and read down principle.
        if(getUserClearance() == 0){
          std::cerr << "Failure Writing To File. Clearance is 0." << std::endl;
        } else {
          std::cout << "Success Writing To File. Correct Clearance" << std::endl;
        }
      } else {
        std::cerr << "Failure Writing To File. Clearance & Classification Not Equal." << std::endl;
      }
    }

      if(file_exist == false){
        std::cerr << "File Does Not Exist." <<  std::endl;
      }

    } else if(option == 'L'){//Show data from Files.store file.

      while(std::getline(files_store, files_store_filename, ':')){
        std::getline(files_store, file_store_user, ':');
        std::getline(files_store, files_store_classification);

        std::cout << files_store_filename << std::endl;
      }

    } else if(option == 'S'){//Save all created files to Files.store.

      for(int i = 0; i < file_counter; i++){
        files_store_input << filename_storage[i] << ":" << getUsername() << ":" << getUserClearance() << std::endl;
        std::cout << filename_storage[i] << " File Saved." << std::endl;
      }


    } else if(option == 'E'){//Exit option

      std::cout << "Shut Down The FileSystem? (Y)es (N)o" << std::endl;
      std::cin >> shutdown;

      if(shutdown == 'Y'){ //check if correct option picked and if so set login_system_exit to true.
        shutdown_option = true;
        login_system_exit = true;

      } else if (shutdown == 'N'){//check if correct option picked and if so set login_system_exit to false.
        shutdown_option = true;
        login_system_exit = false;

      }

      while(shutdown_option == false){ //if correct option not inputed, loop until correct option inputted.

        std::cout << "Only Options Are: Y, N\nShut Down The FileSystem? (Y)es (N)o" << std::endl;
        std::cin >> shutdown;

        if(shutdown == 'Y'){
          shutdown_option = true;
          login_system_exit = true;

        } else if (shutdown == 'N'){
          shutdown_option = true;
          login_system_exit = false;

        }

      }

    }

    files_store_input.close();
    files_store.close();
  } while(login_system_exit == false);

  std::cout << "Exiting System..." << std::endl;
}
