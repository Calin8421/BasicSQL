#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <cctype>

std::string scriptEnvFile = "scriptEnv.txt";

///FUCNTIONS FOR COMMANDER
std::string primeToken(std::string instruction)
{
	std::string primeTok;
	char* p = NULL;
	char* cstr = new char[instruction.length() + 1];
	std::strcpy(cstr, instruction.c_str());
	p = strtok(cstr, " ");
	if(p!=NULL) primeTok = p;
	delete[] cstr;
	return primeTok;
	
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

// UTILITY FUNCTIONS

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

bool isFileEmpty(std::string fileName)
{
	std::ifstream pFile(fileName);
	return pFile.tellg() == 0 && pFile.peek() == std::ifstream::traits_type::eof();
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
	std::string illegalCharacters = " ,;(){}[]<>!@#$%^&*+-=|\/?:.\"'";
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

// UTILITY FUNCTIONS

///DYNAMIC TABLE ALLOC
///DECONSTRUCT THIS
class rowData
{
private:
	int textIndex = 0;
	int integerIndex = 0;
	int floatIndex = 0;
	int textCap = 0;
	int integerCap = 0;
	int floatCap = 0;
	std::string* textData = nullptr;
	int* integerData = nullptr;
	float* floatData = nullptr;
public:
	void setText(std::string data)
	{
		if (textIndex < textCap)
		{
			textData[textIndex] = data;
			textIndex++;
		}
	}

	void setInt(int data)
	{
		if (integerIndex < integerCap)
		{
			integerData[integerIndex] = data;
			integerIndex++;
		}
	}

	void setFloat(float data)
	{
		if (floatIndex < floatCap)
		{
			floatData[floatIndex] = data;
			floatIndex++;
		}
	}

	rowData(int textCap, int integerCap, int floatCap)
	{
		this->textCap = textCap;
		this->integerCap = integerCap;
		this->floatCap = floatCap;
		if (this->textCap > 0) textData = new std::string[this->textCap];
		if (this->integerCap > 0) integerData = new int[this->integerCap];
		if (this->floatCap > 0) floatData = new float[this->floatCap];
	}


};

class Table
{
public:
	enum order { TEXT = 1, INTEGER = 2, FLOAT = 3 };

private:
	std::string tableName = "";
	order* typesOrder = nullptr;
	std::string* attributeNames = nullptr;
	int totalCount = 0, textCount = 0, integerCount = 0, floatCount = 0;
	rowData* data = nullptr;
public:
	Table(std::string tableName)
	{
		this->tableName = tableName;
	}
};
unsigned int tableCounter = 0;
Table* tables = nullptr;

///FUNCTIONS FOR COMMAND INTERPRETER
int INSERT(std::string instruction, int source = 0)
{
	std::string temporary = "";
	std::string columnAtributes[4] = { "-","-","-","-" };
	int attributesCounter = 0;
	const int expectedNoOfAtributes = 3;
	bool isTableValid = true;

	if (instruction == "")
	{
		std::cout << std::endl << "\033[31mInvalid format, type: empty instruction\033[0m" << std::endl;
		return 9; //WILL HANDLE ERROR HERE LATER
	}

	if (source == 0 && instruction[instruction.length() - 1] == ')' && instruction[0] == '(')
	{
		instruction = instruction.substr(0, instruction.length() - 1);
	}
	else if (source != 1)
	{
		std::cout << std::endl << "\033[31mInvalid format, type: there's an issue with the round brackets\033[0m" << std::endl;
		return 8; //WILL HANDLE ERROR HERE LATER
	}

	if (count(instruction, ',') == 3)
	{
		for (attributesCounter = 0; attributesCounter < expectedNoOfAtributes; attributesCounter++)
		{
			instruction = cut(instruction, 1);
			returnFirst(instruction, ",", temporary);
			instruction = cut(instruction, temporary.length());
			removeSpaces(temporary);
			if (temporary != "" && isValid(temporary))
			{
				columnAtributes[attributesCounter] = temporary;
			}
			else
			{
				std::cout << std::endl << "\033[31mInvalid format, type: one of the attributes is null or contains special characters\033[0m" << std::endl;
				return 1; //WILL HANDLE ERROR HERE LATER
			}
		}
		instruction = cut(instruction, 1);
		removeSpaces(instruction);
		if (isValid(instruction) && instruction != "")
		{
			columnAtributes[expectedNoOfAtributes] = instruction;
			instruction = "";
		}
		else
		{
			std::cout << std::endl << "\033[31mInvalid format, type: one of the attributes is null or contains special characters\033[0m" << std::endl;
			return 1; //WILL HANDLE ERROR HERE LATER
		}

	}
	else
	{
		std::cout << std::endl << "\033[31mInvalid format, type: one or more columns doesn't have the right number of attributes or there are empty spaces between the round brackets\033[0m" << std::endl;
		return 2; //WILL HANDLE ERROR HERE LATER
	}

	for (int i = 0; i < 4; i++)
	{
		std::cout << "\033[32m" << columnAtributes[i] << " \033[0m";
	}
	std::cout << std::endl;
	return 0;
}

int CREATE(std::string instruction)
{
	std::string originalInstruction = instruction;
	std::string result = "-", temp = "", name = "", type = "", size = "", default_value = "";
	std::string tableName = "";
	char delimiter = ' ';
	int insertReturnCode = 0, createCode = 1;
	int willNeverBeUsedAgain = -1;
	if (originalInstruction.empty())
	{
		std::cout << std::endl << "\033[31mInvalid format, type: empty instruction\033[0m" << std::endl;
		return 1; //WILL HANDLE ERROR HERE LATER
	}
	std::transform(originalInstruction.begin(), originalInstruction.end(),originalInstruction.begin(),
		[](unsigned char c) { return std::toupper(c); });

	removeSpaces(originalInstruction);
	if (originalInstruction.find("TABLE") != -1)
	{
		if (originalInstruction[sizeof("TABLE") - 1] != ' ')
		{
			std::cout << std::endl << "\033[31mInvalid format, type: no space between keyword TABLE and table name\033[0m" << std::endl;
			return 2; //WILL HANDLE ERROR HERE LATER
		}
		originalInstruction = cut(originalInstruction, sizeof("TABLE") - 1);
		returnFirst(originalInstruction, "(", result);
		returnFirst(originalInstruction, ")", temp);
		if (result == "-" || temp == "-")
		{
			std::cout << std::endl << "\033[31mInvalid format, type: no ((...))\033[0m" << std::endl;
			return 3; //WILL HANDLE ERROR HERE LATER
		}
		else
		{
			instruction = cut(instruction, result.length());
			originalInstruction = cut(originalInstruction, result.length());
			removeSpaces(result);
			tableName = result;
			if (!isValid(tableName))
			{
				std::cout << std::endl << "\033[31mInvalid format, type: special characters found in table name\033[0m" << std::endl;
				return 4; //WILL HANDLE ERROR HERE LATER
			}
			if (tableName == "")
			{
				std::cout << std::endl << "\033[31mInvalid format, type: table name is missing\033[0m" << std::endl;
				return 5; //WILL HANDLE ERROR HERE LATER
			}
		}
	}
	else
	{
		std::cout << std::endl << "\033[31mInvalid format, type: keyword TABLE not found\033[0m" << std::endl;
		return 5; //WILL HANDLE ERROR HERE LATER
	}


	//HANDLES CREATE TABLE NAME() ^^^^^

	originalInstruction = cut(originalInstruction, 1);
	originalInstruction = originalInstruction.substr(0, originalInstruction.length() - 1);

	if (count(originalInstruction, '(') != count(originalInstruction, ')') || (originalInstruction[0] != '(' || originalInstruction[originalInstruction.length() - 1] != ')'))
	{
		std::cout << std::endl << "\033[31mInvalid format, type: there's an issue with the round brackets\033[0m" << std::endl;
		return 5; //WILL HANDLE ERROR HERE LATER
	}
	result = "-";
	while (originalInstruction != "")
	{
		returnFirst(originalInstruction, "),(", result);
		if (result != "-")
		{
			originalInstruction = cut(originalInstruction, result.length() + 2);
			insertReturnCode = INSERT(result, createCode);
			if (insertReturnCode != 0)
			{
				std::cout << "\033[31mInvalid format, type: in the future the whole CREATE command will be cancelled, until then this message will show up\033[0m" << std::endl;
				return 6; //WILL HANDLE ERROR HERE LATER, MEANS THAT SOMETHING IS WRONG WITH THE ATTRIBUTES OF ONE COLUMN
			}
		}
		else
		{
			if (originalInstruction[originalInstruction.length() - 1] != ')')
			{
				std::cout << std::endl << "\033[31mInvalid format, type: there are more characters after the last ')'\033[" << std::endl;
				return 7; //WILL HANDLE ERROR HERE LATER
			}
			else
			{
				originalInstruction = originalInstruction.substr(0, originalInstruction.length() - 1);
				insertReturnCode = INSERT(originalInstruction, createCode);
				if (insertReturnCode != 0)
				{
					std::cout << "\033[31mInvalid format, type: in the future the whole CREATE command will be cancelled, until then this message will show up\033[0m" << std::endl;
					return 6; //WILL HANDLE ERROR HERE LATER, MEANS THAT SOMETHING IS WRONG WITH THE ATTRIBUTES OF ONE COLUMN
				}
				originalInstruction = "";
			}
		}
	}
	//HANDLES ((.,.,.,.),(.,.,.,.),..............,(.,.,.,.)) ^^^^^^^^
	return 0;
}


int UPDATE(std::string instruction)
{
	std::cout << "Table was updated!" << std::endl;
	std::cout << "Instructions are: " << instruction << std::endl;
	return 0;
}
int DROP(std::string instruction)
{
	std::cout << "Table was dropped" << std::endl;
	std::cout << "Instructions are: " << instruction << std::endl;
	return 0;
}
int DELETE(std::string instruction)
{
	std::cout << "Data deleted" << std::endl;
	std::cout << "Instructions are: " << instruction << std::endl;
	return 0;
}
int DISPLAY(std::string instruction)
{
	std::cout << "Data dsiplayed" << std::endl;
	std::cout << "Instructions are: " << instruction << std::endl;
	return 0;
}
int SELECT(std::string instruction)
{
	std::cout << "Data selected" << std::endl;
	std::cout << "Instructions are: " << instruction << std::endl;
	return 0;
}

void showCommands()
{
	std::cout << std::endl;
	std::cout << "<=================================== SQL COMMAND HELP ===================================>" << std::endl;
	std::cout << "COMMAND   | DESCRIPTION" << std::endl;
	std::cout << "---------------------------------------------------------------------------------" << std::endl;
	std::cout << "INSERT    | Adds new rows of data into a table." << std::endl;
	std::cout << "          | Example: INSERT INTO employees (name, salary)" << std::endl;
	std::cout << "          |           VALUES ('John', 5000);" << std::endl << std::endl;

	std::cout << "SELECT    | Retrieves data from one or more tables." << std::endl;
	std::cout << "          | Example: SELECT name, salary FROM employees" << std::endl;
	std::cout << "          |           WHERE salary > 3000;" << std::endl << std::endl;

	std::cout << "UPDATE    | Modifies existing rows in a table." << std::endl;
	std::cout << "          | Example: UPDATE employees SET salary = 6000" << std::endl;
	std::cout << "          |           WHERE name = 'John';" << std::endl << std::endl;

	std::cout << "DELETE    | Removes rows from a table." << std::endl;
	std::cout << "          | Example: DELETE FROM employees WHERE name = 'John';" << std::endl << std::endl;

	std::cout << "CREATE    | Creates a new database object (e.g., table)." << std::endl;
	std::cout << "          | Example: CREATE TABLE employees (id INT, name TEXT, salary FLOAT, DEFAULT_VAL);" << std::endl << std::endl;

	std::cout << "DROP      | Deletes a database object permanently." << std::endl;
	std::cout << "          | Example: DROP TABLE employees;" << std::endl << std::endl;

	std::cout << "DISPLAY   | Shows the content of the current database or table (custom command)." << std::endl;
	std::cout << "          | Example: DISPLAY employees;" << std::endl << std::endl;

	std::cout << "CLEAR     | Clears the screen or console output (custom shell command)." << std::endl;
	std::cout << "          | Example: CLEAR;" << std::endl << std::endl;

	std::cout << "HELP/INFO | Shows help information about available commands." << std::endl;
	std::cout << "          | Example: HELP;" << std::endl << std::endl;

	std::cout << "QUIT/EXIT | Closes the SQL console." << std::endl;
	std::cout << "          | Example: QUIT;" << std::endl << std::endl;

	std::cout << "EXIT      | Same as QUIT - exits the program." << std::endl;
	std::cout << "          | Example: EXIT;" << std::endl << std::endl;

	std::cout << "UNKNOWN   | Indicates an unrecognized or invalid command." << std::endl;
	std::cout << "          | Example: (displayed automatically for invalid input)" << std::endl;
	std::cout << "<========================================================================================>" << std::endl;
}


std::string commander(std::string inputCommand, std::string instruction, bool& quit)
{
	std::string command = inputCommand;
	std::transform(command.begin(), command.end(),command.begin(),
		[](unsigned char c) { return std::toupper(c); });


	if (command == "CREATE")
	{
		CREATE(instruction);
		return "CREATE";
	}
	else if (command == "INSERT")
	{
		INSERT(instruction);
		return "INSERT";
	}
	else if (command == "UPDATE")
	{
		UPDATE(instruction);
		return "UPDATE";
	}
	else if (command == "DROP")
	{
		DROP(instruction);
		return "DROP";
	}
	else if (command == "SELECT")
	{
		SELECT(instruction);
		return "SELECT";
	}
	else if (command == "DELETE")
	{
		DELETE(instruction);
		return "DELETE";
	}
	else if (command == "DISPLAY")
	{
		DISPLAY(instruction);
		return "DISPLAY";
	}
	else if (command == "QUIT" or command == "EXIT")
	{
		quit = true;
		return "QUIT";
	}
	else if (command == "INFO" or command == "HELP")
	{
		showCommands();
		return "INFO";
	}
	else if (command == "CLEAR")
	{
		system("cls");
		return "CLEAR";
	}
	std::cout << "UNKNOWN" << std::endl;
	return "UNKNOWN";
}


///SQL CONSOLE
int sqlQueryConsole()
{
	std::cout << "Listening for command: ";
	std::string userInput;
	std::string firstToken;
	std::string userInstruction;
	std::getline(std::cin, userInput);
	firstToken = primeToken(userInput);
	userInstruction = restOfInstruction(userInput);
	std::cout << std::endl;
	bool quit = false;
	commander(firstToken, userInstruction ,quit);
	if (!quit) sqlQueryConsole();

	return 0;
}

int scriptRunner()
{
	std::string line;
	std::ifstream scriptEnv;
	std::string firstToken;
	std::string scriptInstruction;
	bool f = false;
	std::string flag;
	int lineNr = 0;
	scriptEnv.open(scriptEnvFile);
	if (scriptEnv.is_open())
	{
		while (std::getline(scriptEnv, line))
		{
			if (!line.empty())
			{
				lineNr++;
				firstToken = primeToken(line);
				scriptInstruction = restOfInstruction(line);
				flag = commander(firstToken, scriptInstruction, f);
				if (flag == "UNKNOWN")
				{
					std::cout << "Unknown command on line " << lineNr << std::endl;
					std::cout << line << std::endl;
					return 0;
				}
				/*	std::cout << "Line: " << line << std::endl;
					std::cout << "First token: " << firstToken << std::endl;
					std::cout << "Instruction: " << scriptInstruction << std::endl;*/
			}

		}
		std::cout << "Reached end of script!" << std::endl;
	}
	else
		std::cout << "File not found or couldn't be open" << std::endl;///add existing checker;
	/*std::cout << "Printed: <script runner here>" << std::endl;
	scriptEnv << "script runner here";*/

	scriptEnv.close();
}

void overwriteScriptEnvContent()
{
	std::ofstream scriptEnv(scriptEnvFile);
	scriptEnv.close();
	std::cout << "Contents deleted!" << std::endl;
}

void scriptEnvironment()
{
	
	if (!checkExistenceOFile(scriptEnvFile))
	{
		std::ofstream scriptEnv(scriptEnvFile);
		if (scriptEnv.is_open())
		{
			std::cout << "Script file created!" << std::endl;
			scriptEnv.close();
		}
		else
		{
			std::cout << "\033[31mError: Could not create script file.\033[0m" << std::endl;
		}

	}
	if (checkExistenceOFile(scriptEnvFile) and isFileEmpty(scriptEnvFile))
	{
		std::ofstream writeInEnv;
		writeInEnv.open(scriptEnvFile);
		std::string line;
		std::vector<std::string> lines;
		std::cout << "\033[32mScript Environment (insert quit when you are done):\033[0m" << std::endl;
		while (std::getline(std::cin, line))
		{
			if (line == "QUIT" or line == "quit") break;
			writeInEnv << line << std::endl;
			
		}
		writeInEnv.close();
		if (!isFileEmpty(scriptEnvFile))
		{
			bool running = true;
			char c;
			while (running)
			{
				std::cout << "Run script? y/n:";
				std::cin >> c;
				switch (c)
				{
				case 'y':
				case 'Y':
					scriptRunner();
					running = false;
					break;
				case 'n':
				case 'N':
					running = false;
					break;
				default:
					system("cls");
					std::cout << "\033[31mUndefined. Try again.\033[0m" << std::endl;
					system("pause");
					system("cls");
					break;
				}
			}
		}
		
	}

}

void scriptRunnerMenu()
{
	if (checkExistenceOFile(scriptEnvFile) and !isFileEmpty(scriptEnvFile))
	{
		
		bool running = true;
		char c;
		while (running)
		{
			///IN THE FUTURE MAKE IT SO THE FILE WON'T SAVE ANYTHING AND WILL ONLY ACT AS A SCRIPTRUNNER
			std::cout << "Overwrite script runner contents? Y/n: ";
			std::cin >> c;
			switch (c)
			{
			case 'y':
			case 'Y':
				overwriteScriptEnvContent();
				scriptEnvironment();
				running = false;
				break;
			case 'n':
			case 'N':
				scriptRunner();
				running = false;
				break;
			default:
				system("cls");
				std::cout << "\033[31mUndefined. Try again.\033[0m" << std::endl;
				system("pause");
				system("cls");
				break;
			}
		}

	}
	else
		scriptEnvironment();
	


}

void saveScriptProg()
{
	
	bool running = true;
	char c;
	while (running)
	{
		std::cout << "Save contents of script runner? Y/n: ";
		std::cin >> c;
		switch (c)
		{
		case 'y':
		case 'Y':
			running = false;
			break;
		case 'n':
		case 'N':
			overwriteScriptEnvContent();
			running = false;
			break;
		default:
			system("cls");
			std::cout << "Undefined. Try again." << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}

}

///MENU FUNCTIONS
void startMenu(char& n)
{
	std::cout << "<=====  SQLite Engine  =====>" << std::endl;
	std::cout << "<======  Cheese Team  ======>" << std::endl;
	std::cout << "(1) Query console" << std::endl;
	std::cout << "(2) Import/Export files" << std::endl;
	std::cout << "(3) Script runner" << std::endl;
	std::cout << "(x) Quit program" << std::endl;
	std::cout << "<===========================>" << std::endl;
	std::cout << "Insert menu option number: ";
	std::cin >> n;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << std::endl;
}



///MAIN PROGRAM
int main()
{
	std::string fileName;
	char c;
	bool running = true;

	while (running) {

		startMenu(c);
		switch (c)
		{
		case '1':
			system("cls");
			std::cin.clear();
			sqlQueryConsole();
			system("cls");
			break;

		case '2':
			system("cls");
			std::cout << "to be continued. returning to menu..." << std::endl;
			system("pause");
			system("cls");
			break;
		case '3':
			system("cls");
			scriptRunnerMenu();
			system("pause");
			system("cls");
			break;
		case 'X':
		case 'x':
			if (checkExistenceOFile(scriptEnvFile) and !isFileEmpty(scriptEnvFile))
				saveScriptProg();
			running = false;
			break;

		default:
			system("cls");
			std::cout << "\033[31mUndefined. Try again.\033[0m" << std::endl;
			system("pause");
			system("cls");
			break;
		}

	}

	std::cout << "Exiting program. Project made by Gheorghe Calin and Grigore Mihaita Adelin" << std::endl;
	return 0;
}
