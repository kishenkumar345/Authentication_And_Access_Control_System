#ifndef CREATION_SYSTEM
#define CREATION_SYSTEM
#pragma once

#include<string>

class CreationSystem {
 public:
   CreationSystem();
   void store_user();
   std::string getUsername();
   void setUsername(std::string);
   std::string getPassword();
   void setPassword(std::string);
   int getUserClearance();
   void setUserClearance(int);
 private:
   std::string username;
   std::string password;
   int user_clearance = 0;
};

#endif /* end of include guard:  */
