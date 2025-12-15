///PHASE 1
#include <iostream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <cctype>
#include "Commands.h"
#include "Utils.h"
#include "Database.h"


///SCRIPT RUNNER FILE
std::string scriptEnvFile = "scriptEnv.txt";


//DYNAMIC TABLE ALLOC
//DECONSTRUCT THIS
//class rowData
//{
//private:
//	int textIndex = 0;
//	int integerIndex = 0;
//	int floatIndex = 0;
//	int textCap = 0;
//	int integerCap = 0;
//	int floatCap = 0;
//	std::string* textData = nullptr;
//	int* integerData = nullptr;
//	float* floatData = nullptr;
//public:
//	void setText(std::string data)
//	{
//		if (textIndex < textCap)
//		{
//			textData[textIndex] = data;
//			textIndex++;
//		}
//	}
//
//	void setInt(int data)
//	{
//		if (integerIndex < integerCap)
//		{
//			integerData[integerIndex] = data;
//			integerIndex++;
//		}
//	}
//
//	void setFloat(float data)
//	{
//		if (floatIndex < floatCap)
//		{
//			floatData[floatIndex] = data;
//			floatIndex++;
//		}
//	}
//
//	rowData(int textCap, int integerCap, int floatCap)
//	{
//		this->textCap = textCap;
//		this->integerCap = integerCap;
//		this->floatCap = floatCap;
//		if (this->textCap > 0) textData = new std::string[this->textCap];
//		if (this->integerCap > 0) integerData = new int[this->integerCap];
//		if (this->floatCap > 0) floatData = new float[this->floatCap];
//	}
//
//
//};
//
//class Table
//{
//public:
//	enum order { TEXT = 1, INTEGER = 2, FLOAT = 3 };
//
//private:
//	std::string tableName = "";
//	order* typesOrder = nullptr;
//	std::string* attributeNames = nullptr;
//	int totalCount = 0, textCount = 0, integerCount = 0, floatCount = 0;
//	rowData* data = nullptr;
//public:
//	Table(std::string tableName)
//	{
//		this->tableName = tableName;
//	}
//
//	Table() {};
//
//	std::string getTableName()
//	{
//		return this->tableName;
//	}
//
//	void setTableName(std::string tableName)
//	{
//		this->tableName = tableName;
//	}
//
//	void operator= (const Table& other) {
//		this->tableName = other.tableName;
//
//		// Copy all primitive types
//		this->totalCount = other.totalCount;
//		this->textCount = other.textCount;
//		this->integerCount = other.integerCount;
//		this->floatCount = other.floatCount;
//
//		// For pointers - set to nullptr for now (you'll handle properly later)
//		this->typesOrder = nullptr;
//		this->attributeNames = nullptr;
//		this->data = nullptr;
//
//		// TODO: Properly copy dynamic arrays in Phase 2
//	}
//
//	bool operator== (Table other)
//	{
//		return this->getTableName() == other.getTableName();
//	}
//};
//
//class DataBase
//{
//	Table* tables = nullptr;
//	int tablesNo = 0;
//public:
//	int getTablesNo()
//	{
//		return this->tablesNo;
//	}
//
//	void setTablesNo(int tablesNo)
//	{
//		this->tablesNo = tablesNo;
//	}
//
//	void setTables(Table* tables)
//	{
//		if (tablesNo > 0)
//		{
//			if (this->tables != nullptr)
//			{
//				delete[] this->tables;
//			}
//			this->tables = new Table[tablesNo];
//			for (int i = 0; i < tablesNo; i++)
//			{
//				this->tables[i] = tables[i];
//			}
//		}
//	}
//
//	Table* getTables()
//	{
//		return this->tables;
//	}
//
//	void addTable(Table table)
//	{
//		if (tablesNo == 0)
//		{
//			tablesNo++;
//			tables = new Table[tablesNo];
//			tables[0] = table;
//		}
//		else if (tablesNo > 0)
//		{
//			Table* newTables = new Table[tablesNo + 1];
//
//			for (int i = 0; i < tablesNo; i++)
//			{
//				newTables[i] = tables[i];
//			}
//
//			newTables[tablesNo] = table;
//
//			delete[] tables;
//			tables = newTables;
//			tablesNo++;
//		}
//	}
//
//	bool checkIfTableExists(std::string tableName)
//	{
//		for (int i = 0; i < tablesNo; i++)
//		{
//			if (this->tables[i].getTableName() == tableName)
//			{
//				return true;
//			}
//		}
//		return false;
//	}
//
//	~DataBase()
//	{
//		if (tables != nullptr)
//		{
//			delete[] tables;
//			tables = nullptr;
//		}
//
//	}
//};
//
//DataBase db;


///SQL CONSOLE
int sqlQueryConsole()
{
	std::cout << "Listening for command: ";
	std::string userInput;
	std::string firstToken;
	std::string userInstruction;
	std::getline(std::cin, userInput);
	///:(
	toUpper(userInput);
	///toUpper
	firstToken = primeToken(userInput);
	userInstruction = restOfInstruction(userInput);
	std::cout << std::endl;
	bool quit = false;
	commander(firstToken, userInstruction ,quit);
	if (!quit) sqlQueryConsole();

	return 0;
}

///STILL WORK IN PROGRESS BUT WORKS
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
					scriptEnv.close();
					return 0;
				}
			}
		}
		std::cout << "Reached end of script!" << std::endl;
	}
	else
		std::cout << "File not found or couldn't be open" << std::endl;///add existing checker;
	

	scriptEnv.close();
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
			if (line.empty())
				continue; 

			toUpper(line);
			if (primeToken(line) == "QUIT" || primeToken(line) == "EXIT")
			{
				std::cout << "Exiting script environment." << std::endl;
				break;
			}
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
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (c)
			{
			case 'y':
			case 'Y':
				if (overwriteFile(scriptEnvFile))
				{
					scriptEnvironment();
				}
				else
					std::cout << "couldn't delete file" << std::endl;
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
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (c)
		{
		case 'y':
		case 'Y':
			running = false;
			break;
		case 'n':
		case 'N':
			overwriteFile(scriptEnvFile);
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
	char c[1];
	bool running = true;

	while (running) {

		startMenu(c[0]);
		switch (c[0])
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
