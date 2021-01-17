#ifndef LOGIN_SYSTEM
#define LOGIN_SYSTEM
#pragma once

#include <fstream>

class LoginSystem {
 public:
   LoginSystem();
   int retrieve_info();
   void options_menu();
   int getUserClearance();
   void setUserClearance(int);
   std::string getUsername();
   void setUsername(std::string);
 private:
   int user_clearance;
   std::string username;
};

#endif /* end of include guard:  */
