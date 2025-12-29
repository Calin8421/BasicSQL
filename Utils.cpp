///PHASE 1
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>



// UTILITY FUNCTIONS
std::string primeToken(std::string instruction)
{
	std::string primeTok;
	char* p = NULL;
	char* cstr = new char[instruction.length() + 1];
	std::strcpy(cstr, instruction.c_str());
	p = strtok(cstr, " ");
	if (p != NULL) primeTok = p;
	delete[] cstr;
	return primeTok;

}

std::string tokenWithInstruction(const std::string instruction, const std::string firstToken, const std::string lastToken)
{
	std::string key;
	char* p = NULL;
	char* cstr = new char[instruction.length() + 1];
	char* first_token_string = new char[firstToken.length() + 1];
	char* last_token_string = new char[lastToken.length() + 1];
	std::strcpy(cstr, instruction.c_str());
	p = strtok(cstr, " ");
	if (p != NULL)
	{
		
	}
	delete[] cstr;
	delete[] first_token_string;
	delete[] last_token_string;
	
}

std::string restOfInstruction(std::string instruction) {
	std::string instruct;
	char* p = NULL;
	int i = 0;
	char* cstr = new char[instruction.length() + 1];
	std::strcpy(cstr, instruction.c_str());
	p = strtok(cstr, " ");
	while (p != NULL)
	{
		if (i > 0) instruct = instruct + " " + p;
		p = strtok(NULL, " ");
		i++;
	}

	delete[] cstr;
	return instruct;
}

std::string toUpper(std::string& givenString)
{
	std::transform(givenString.begin(), givenString.end(), givenString.begin(),
		[](unsigned char c) { return std::toupper(c); });
	return givenString;
}

bool checkExistenceOFile(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		file.close();
		return true;
	}
	return false;
}

bool isFileEmpty(const std::string& fileName)
{
	std::ifstream pFile(fileName, std::ios::ate | std::ios::binary);
	if (!pFile.is_open())
		return true;

	return pFile.tellg() == 0;
}


bool overwriteFile(const std::string& fileName)
{
	// open and truncate
	std::ofstream scriptEnv(fileName, std::ios::out | std::ios::trunc);
	if (!scriptEnv.is_open())
	{
		std::cout << "Error: could not open file for overwrite\n";
		return false;
	}

	std::cout << "\033[31mContents deleted!\033[0m" << std::endl;
	return true;        // file is empty at this point
}

//Stores std::string::find result(a size_t) into an int(int i = instruction.find(delimiter);).
//When not found, find returns npos; converting to int is implementation - defined and can become - 1 or overflow.
//You then compare to - 1. This is not reliable.

void returnFirst(std::string instruction, const std::string delimiter, std::string& result)
{
	int i = instruction.find(delimiter);
	if (i != -1)
	{
		result = instruction.substr(0, i);
	}
	else result = "-";
}


std::string cut(std::string& instruction, int n)
{
	return instruction.substr(n);
}

std::string removeCharacters(std::string instruction, char character)
{
	std::string result = "";
	for (int i = 0; i < instruction.length(); i++)
	{
		if (instruction[i] != character)
		{
			result += instruction[i];
		}
	}
	return result;
}

int count(std::string instruction, char character)
{
	int counter = 0;
	for (int i = 0; i < instruction.length(); i++)
	{
		if (instruction[i] == character) counter++;
	}
	return counter;
}

bool isValid(std::string instruction)
{
	std::string illegalCharacters = " ,;(){}[]<>!@#$%^&*+-=|\/?:\".";
	int lenghtIllegal = illegalCharacters.length(), lenghtInstruction = instruction.length(), i, j;
	for (i = 0; i < lenghtIllegal; i++)
		for (j = 0; j < lenghtInstruction; j++)
		{
			if (illegalCharacters[i] == instruction[j]) return false;
		}
	return true;
}

bool isValidForInsert(std::string instruction)
{
	std::string illegalCharacters = " ;(){}[]<>!@#$%^&*+-=|\/?:";
	int lenghtIllegal = illegalCharacters.length(), lenghtInstruction = instruction.length(), i, j;
	for (i = 0; i < lenghtIllegal; i++)
		for (j = 0; j < lenghtInstruction; j++)
		{
			if (illegalCharacters[i] == instruction[j]) return false;
		}
	return true;
}


//Uses int i = instruction.length() - 1; .
//When instruction is empty, length() is 0 and 0 - 1 underflows to a negative value and
//the index access that follows would be out - of - bounds if the loop condition didn’t short - circuit exactly as intended.
//It “works” due to the i >= 0 check, but the expression used to compute the starting index is still a foot - gun.

void removeSpaces(std::string& instruction)
{
	int i = 0, spacesCount = 0;;

	while (i < instruction.length() && instruction[i] == ' ')
	{
		i++;
	}

	instruction.erase(0, i);

	i = instruction.length() - 1;
	while (i >= 0 && instruction[i] == ' ')
	{
		spacesCount++;
		i--;
	}

	instruction.erase(instruction.length() - spacesCount, spacesCount);
}
