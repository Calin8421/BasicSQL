#pragma once
#include <iostream>

void showCommands();
int INSERT(std::string);
int CREATE(std::string);
int UPDATE(std::string);
int DROP(std::string);
int DELETE(std::string);
int DISPLAY(std::string);
int SELECT(std::string);
std::string commander(std::string, std::string, bool&);