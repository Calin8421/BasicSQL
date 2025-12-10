#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

std::string primeToken(std::string);
std::string restOfInstruction(std::string);
std::string toUpper(std::string&);
bool checkExistenceOFile(std::string);
bool isFileEmpty(const std::string&);
bool overwriteFile(const std::string&);
void returnFirst(std::string, const std::string, std::string&);
std::string cut(std::string&, int );
std::string removeCharacters(std::string, char);
int count(std::string, char);
bool isValid(std::string);
bool isValidForInsert(std::string);
void removeSpaces(std::string&);
