#include <iostream>
#include <string.h>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>
#include <vector>
#include <fstream>



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

///STRING OPERATION FUNCTION
void returnFirst(std::string instruction, const char delimiter, std::string& result)
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

///DYNAMIC TABLE ALLOC
class rowData
{
private:
	int textIndex = 0;
	int integerIndex = 0;
	int floatIndex = 0;
	int textCap = 0;
	int integerCap = 0;
	int floatCap = 0;
	std::string* textData=nullptr;
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

	rowData(int textCap,int integerCap,int floatCap)
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
	std::string tableName="";
	order* typesOrder = nullptr;
	std::string* attributeNames = nullptr;
	int totalCount = 0, textCount = 0, integerCount = 0, floatCount = 0;
	rowData* data = nullptr;

};
unsigned int tableCounter=0;
Table* tables = nullptr;





///FUNCTIONS FOR COMMAND INTERPRETER
int CREATE(std::string instruction)
{
	//std::string originalInstruction = instruction;
	//std::string result = "", name = "", type = "", size = "", default_value = "";
	//std::string tableName = "";
	//char delimiter = ' ';
	//int willNeverBeUsedAgain = -1;
	//std::transform(originalInstruction.begin(), originalInstruction.end(), originalInstruction.begin(), ::toupper);///USE TRANSFORM 
	////instruction = originalInstruction; WORKING originalInstruction instead of instruction
	//willNeverBeUsedAgain = originalInstruction.find("table") + sizeof("table") + 1;
	//originalInstruction = cut(originalInstruction, willNeverBeUsedAgain);
	//returnFirst(originalInstruction, '(', result);
	//tableName = result;
	//result = removeCharacters(result, 'N');
	//originalInstruction = cut(originalInstruction, result.length());
	//std::cout << tableName << std::endl;
	//while (originalInstruction != ")")
	//{
	//	returnFirst(originalInstruction, ')', result);
	//	originalInstruction = cut(originalInstruction, result.length() + 1);

	//	result = cut(result, 1);
	//	returnFirst(result, ',', name);
	//	result = cut(result, name.length());
	//	name = removeCharacters(name, '(');
	//	name = removeCharacters(name, ' ');

	//	result = cut(result, 1);
	//	returnFirst(result, ',', type);
	//	result = cut(result, type.length() + 1);
	//	type = removeCharacters(type, ',');
	//	type = removeCharacters(type, ' ');

	//	returnFirst(result, ',', size);
	//	result = cut(result, size.length());
	//	size = removeCharacters(size, ',');
	//	size = removeCharacters(size, ' ');

	//	returnFirst(result, ')', default_value);
	//	result = cut(result, default_value.length());
	//	default_value = removeCharacters(default_value, ')');
	//	default_value = removeCharacters(default_value, ' ');

	//	std::cout << name << "||" << type << "||" << size << "||" << result << "||" << std::endl;
	//	//WE HAVE TO SEND EACH DETAIL ABOUT THE ATTRIBUTE INTO THE INSERT FUNCTION TO CREATE A NEW 
	//	////PROCESS THIS IN INDEX. CREATE TABLE + NAME HERE. MAKE ATRIBUTES IN INDEX!!!!!!!
	//	
	//	
	//}
	
	std::cout << "Table was created" << std::endl;
	std::cout << "Instructions are: " << instruction << std::endl;
	return 0;
}
int INSERT(std::string instruction)
{
	
	std::cout << "Table was inserted" << std::endl;
	std::cout << "Instructions are: " << instruction << std::endl;

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
	std::cout << "<=================================== SQL COMMAND HELP ===================================>"<<std::endl;
    std::cout << "COMMAND   | DESCRIPTION"<<std::endl;
    std::cout << "---------------------------------------------------------------------------------"<<std::endl;
    std::cout << "INSERT    | Adds new rows of data into a table."<<std::endl;
    std::cout << "          | Example: INSERT INTO employees (name, salary)"<<std::endl;
	std::cout << "          |           VALUES ('John', 5000);" << std::endl << std::endl;

	std::cout << "SELECT    | Retrieves data from one or more tables." << std::endl;
    std::cout << "          | Example: SELECT name, salary FROM employees" << std::endl;
    std::cout << "          |           WHERE salary > 3000;"<<std::endl << std::endl;

    std::cout << "UPDATE    | Modifies existing rows in a table."<<std::endl;
    std::cout << "          | Example: UPDATE employees SET salary = 6000"<<std::endl;
    std::cout << "          |           WHERE name = 'John';"<<std::endl << std::endl;

    std::cout << "DELETE    | Removes rows from a table."<<std::endl;
	std::cout << "          | Example: DELETE FROM employees WHERE name = 'John';" << std::endl << std::endl;

	std::cout << "CREATE    | Creates a new database object (e.g., table)." << std::endl;
	std::cout << "          | Example: CREATE TABLE employees (id INT, name TEXT, salary FLOAT);" << std::endl << std::endl;

	std::cout << "DROP      | Deletes a database object permanently." << std::endl;
	std::cout << "          | Example: DROP TABLE employees;" << std::endl << std::endl;

	std::cout << "DISPLAY   | Shows the content of the current database or table (custom command)." << std::endl;
    std::cout << "          | Example: DISPLAY employees;" <<std::endl << std::endl;

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


enum class SqlOperation {INSERT, SELECT, UPDATE, DELETE, UNKNOWN, CREATE, DROP, DISPLAY, QUIT, EXIT, CLEAR, HELP, INFO};

SqlOperation getSqlOperation(const std::string& command)
{
	static const std::unordered_map<std::string, SqlOperation> dispatch = {
		{"INSERT", SqlOperation::INSERT},
		{"SELECT", SqlOperation::SELECT},
		{"DROP", SqlOperation::DROP},
		{"CREATE", SqlOperation::CREATE},
		{"UPDATE", SqlOperation::UPDATE},
		{"DELETE", SqlOperation::DELETE},
		{"DISPLAY", SqlOperation::DISPLAY},
		{"QUIT", SqlOperation::QUIT},
		{"EXIT", SqlOperation::EXIT},
		{"CLEAR", SqlOperation::CLEAR},
		{"HELP", SqlOperation::HELP},
		{"INFO", SqlOperation::INFO}

	};

	std::string primeToken = command;
	std::transform(primeToken.begin(), primeToken.end(), primeToken.begin(), ::toupper);

	for (const auto& pair : dispatch)
	{
		if (pair.first == primeToken)
		{
			return pair.second;
		}
	}
	return SqlOperation::UNKNOWN;
}



std::string getSqlOpString(const SqlOperation& op, std::string& instruction, bool& quit)
{
	switch (op)
	{
	case SqlOperation::INSERT:
		INSERT(instruction);
		return "INSERT";
	case SqlOperation::UPDATE:
		UPDATE(instruction);
		return "UPDATE";
	case SqlOperation::SELECT:
		SELECT(instruction);
		return "SELECT";
	case SqlOperation::DELETE:
		DELETE(instruction);
		return "DELETE";
	case SqlOperation::DROP:
		DROP(instruction);
		return "DROP";
	case SqlOperation::CREATE:
		CREATE(instruction);
		return "CREATE";
	case SqlOperation::DISPLAY:
		DISPLAY(instruction);
		return "DISPLAY";
	case SqlOperation::QUIT:
	case SqlOperation::EXIT:
		quit = true;
		return "QUIT";
	case SqlOperation::CLEAR:
		system("cls");
		return "CLEAR";
	case SqlOperation::HELP:
	case SqlOperation::INFO:
		showCommands();
		return "INFO";
	default:
		std::cout << "UNKNOWN"<<std::endl;
		return "UNKNOWN";
	}
}


///SQL CONSOLE
int sqlQueryConsole()
{
		std::cout << "Listening for command: ";
		std::string userInput;
		std::string firstToken;
		std::string userInstruction;
		std::getline(std::cin, userInput);
		std::istringstream iss(userInput);
		iss >> firstToken;
		//std::getline(iss, userInstruction);
		std::getline(iss >> std::ws, userInstruction);///ignores the spaces after the first word
		std::cout << std::endl;
		bool quit = false;
		getSqlOpString(getSqlOperation(firstToken), userInstruction, quit);
		if (!quit) sqlQueryConsole();
	
	return 0;
}

void overwriteScriptEnvContent()
{
	std::ofstream scriptEnv("scriptEnv.txt");
	scriptEnv.close();
	std::cout << "Contents deleted!"<<std::endl;
}


void scriptEnvironment()
{
	std::cout << "Script Environment not finished" << std::endl;
	std::cout << "Please write manually in the file and SAVE!" << std::endl;
}


int scriptRunner()
{
	std::string line;
	std::ifstream scriptEnv;
	std::string firstToken;
	std::string scriptInstruction;
	bool f = false;
	std::string flag;
	int lineNr=0;
	scriptEnv.open("scriptEnv.txt");
	if (scriptEnv.is_open())
	{
		std::cout << "File created or found!" << std::endl;///add existing checker;
		/*std::cout << "Printed: <script runner here>" << std::endl;
		scriptEnv << "script runner here";*/
	
		while (std::getline(scriptEnv, line))
		{
			if (!line.empty())
			{
				lineNr++;
				std::istringstream iss(line);
				iss >> firstToken;
				std::getline(iss >> std::ws, scriptInstruction);
				flag = getSqlOpString(getSqlOperation(firstToken), scriptInstruction, f);
				if (flag == "UNKNOWN")
				{
					std::cout << "Unknown command on line " <<lineNr << std::endl;
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
	
	scriptEnv.close();
}



void scriptRunnerMenu()
{
	if (checkExistenceOFile("scriptEnv.txt") and !isFileEmpty("scriptEnv.txt"))
	{
		std::cout << "" << std::endl;
		std::cout << "Overwrite script runner contents? Y/n: ";
		bool running = true;
		char c;
		while (running)
		{
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
				std::cout << "Undefined. Try again." << std::endl;
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
	std::cout << "Save contents of script runner? Y/n: ";
	bool running = true;
	char c;
	while (running)
	{
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
void main()
{
	std::string fileName;
	char c;
	bool running = true;
	
	while(running){
		
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
		case 'x':
			if(checkExistenceOFile("scriptEnv.txt") and !isFileEmpty("scriptEnv.txt"))
			saveScriptProg();
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

	std::cout << "Exiting program. Project made by Gheorghe Calin and Grigore Mihaita Adelin" << std::endl;

}
