#include <iostream>
#include <string.h>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>
#include<vector>

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
Table* tables = nullptr;

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
int DROP(std::string instruction)
{
	std::cout << "Table was dropped" << std::endl;
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
int CREATE(std::string instruction)
{
	std::string originalInstruction=instruction;
	std::string result = "", name = "", type = "", size = "", default_value = "";
	std::string tableName = "";
	char delimiter = ' ';
	int willNeverBeUsedAgain = -1;
	for (char& c : originalInstruction)
	{
		c = std::toupper(c);
	}
	instruction = originalInstruction;
	willNeverBeUsedAgain = instruction.find("table") + sizeof("table") + 1;
	instruction = cut(instruction, willNeverBeUsedAgain);
	returnFirst(instruction, '(', result);
	tableName = result;
	result = removeCharacters(result, 'N');
	instruction = cut(instruction, result.length());
	std::cout << tableName << std::endl;
	while (instruction != ")")
	{
		returnFirst(instruction, ')', result);
		instruction = cut(instruction, result.length() + 1);
		result = cut(result, 1);
		returnFirst(result, ',', name);
		result = cut(result, name.length());
		name = removeCharacters(name, '(');
		name = removeCharacters(name, ' ');
		result = cut(result, 1);
		returnFirst(result, ',', type);
		result = cut(result, type.length() + 1);
		type = removeCharacters(type, ',');
		type = removeCharacters(type, ' ');
		returnFirst(result, ',', size);
		result = cut(result, size.length());
		size = removeCharacters(size, ',');
		size = removeCharacters(size, ' ');
		returnFirst(result, ')', default_value);
		result = cut(result, default_value.length());
		default_value = removeCharacters(default_value, ')');
		default_value = removeCharacters(default_value, ' ');
		std::cout << name << "||" << type << "||" << size << "||" << result << "||" << std::endl;
		//WE HAVE TO SEND EACH DETAIL ABOUT THE ATTRIBUTE INTO THE INSERT FUNCTION TO CREATE A NEW COLUMN
	}
	return 0;
}


enum class SqlOperation {INSERT, SELECT, UPDATE, DELETE, UNKNOWN, CREATE, DROP, DISPLAY};

SqlOperation getSqlOperation(const std::string& command)
{
	static const std::unordered_map<std::string, SqlOperation> dispatch = {
		{"INSERT", SqlOperation::INSERT},
		{"SELECT", SqlOperation::SELECT},
		{"DROP", SqlOperation::DROP},
		{"CREATE", SqlOperation::CREATE},
		{"UPDATE", SqlOperation::UPDATE},
		{"DELETE", SqlOperation::DELETE},
		{"DISPLAY", SqlOperation::DISPLAY}

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

std::string getSqlOpString(const SqlOperation& op, std::string& instruction)
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
	default:
		std::cout << "UNKNOWN"<<std::endl;
		return "UNKNOWN";
	}
}



int commander()
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
	if (getSqlOpString(getSqlOperation(firstToken), userInstruction) == "UNKNOWN") commander();

	
	
	return 0;
}

void main()
{
	commander();

}