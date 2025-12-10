#define _CRT_SECURE_NO_WARNINGS
#include "Commands.h"
#include "Utils.h"
#include "Database.h"
#include <iostream>


///DYNAMIC TABLE ALLOC
///DECONSTRUCT THIS


void errorHandler(int errorCode, std::string tableName = "")
{
	switch (errorCode)
	{
	case 1:
		std::cout << std::endl << "\033[31mInvalid format, type: empty instruction\033[0m" << std::endl;
		break;
	case 2:
		std::cout << std::endl << "\033[31mInvalid format, type: no space between keyword TABLE and table name\033[0m" << std::endl;
		break;
	case 3:
		std::cout << std::endl << "\033[31mInvalid format, type: no ((...))\033[0m" << std::endl;
		break;
	case 4:
		std::cout << std::endl << "\033[31mInvalid format, type: special characters found in table name or table name is missing\033[0m" << std::endl;
		break;
	case 5:
		std::cout << std::endl << "\033[31mInvalid format, type: there's an issue with the round brackets\033[0m" << std::endl;
		break;
	case 6:
		std::cout << std::endl << "\033[31mInvalid format, type: in the future the whole CREATE command will be cancelled, until then this message will show up\033[0m" << std::endl;
		break;
	case 7:
		std::cout << std::endl << "\033[31mInvalid table name, type: table name " << tableName << " is already used\033[0m" << std::endl;
		break;
	case 9:
		std::cout << std::endl << "\033[31mInvalid format, type: there are characters (including space) between IF NOT EXISTS and (\033[0m" << std::endl;
		break;
	case 10:
		std::cout << std::endl << "\033[31mInvalid format, type: there are more characters after the last ')'\033[0m" << std::endl;
		break;
	case 11:
		std::cout << std::endl << "\033[31mInvalid format, type: one of the attributes is null or contains special characters\033[0m" << std::endl;
		break;
	case 12:
		std::cout << std::endl << "\033[31mInvalid format, type: one or more columns doesn't have the right number of attributes or there are empty spaces between the round brackets\033[0m" << std::endl;
		break;
	case 13:
		std::cout << std::endl << "\033[31mInvalid format, type: more than one table name found or one of the table names contains illegal characters\033[0m" << std::endl;
		break;
	case 14:
		std::cout << std::endl << "\033[31mInvalid format, type: no table name found\033[0m" << std::endl;
		break;
	case 15:
		std::cout << std::endl << "\033[31mInvalid format, type: the table " << tableName << " doesn't exist\033[0m" << std::endl;
		break;
	case 16:
		std::cout << std::endl << "\033[31mInvalid format, type: one of the columns contains special characters" << std::endl << "In the future the whole SELECT command will be cancelled but for now this message will show up\033[0m" << std::endl;
		break;
	case 17:
		std::cout << std::endl << "\033[31mInvalid format, type: no columns were provided for the SELECT\033[0m" << std::endl;
		break;
	case 18:
		std::cout << std::endl << "\033[31mInvalid format, type: illegal characters found between the ')' and FROM , make sure that there are only empty spaces between the closing parenthesis and the keyword FROM including the ALL keyword since you the command will handle either some columns or ALL not both at the same time\033[0m" << std::endl;
		break;
	case 19:
		std::cout << std::endl << "\033[31mInvalid format, type: keyword FROM not found, make sure to type the word correctly and leave as space after it" << std::endl << "In the future the whole command will be cancelled but for now this message will show up\033[0m" << std::endl;
		break;
	case 20:
		std::cout << std::endl << "\033[31mInvalid format, type: keyword WHERE not found, make sure to type the word correctly and leave as space after it\033[0m" << std::endl;
		break;
	case 21:
		std::cout << std::endl << "\033[31mInvalid format, type: keyword SET not found, make sure to type the word correctly and leave as space after it\033[0m" << std::endl;
		break;
	case 22:
		std::cout << std::endl << "\033[31mInvalid format, type: keyword WHERE found before keyword SET\033[0m" << std::endl;
		break;
	case 23:
		std::cout << std::endl << "\033[31mInvalid format, type: column to be changed is missing\033[0m" << std::endl;
		break;
	case 24:
		std::cout << std::endl << "\033[31mInvalid format, type: WHERE condition is missing\033[0m" << std::endl;
		break;
	case 25:
		std::cout << std::endl << "\033[31mInvalid format, type: INTO keyword is missing, make sure to type the word correctly and leave as space after it\033[0m" << std::endl;
		break;
	case 26:
		std::cout << std::endl << "\033[31mInvalid format, type: VALUES keyword is missing, make sure to type the word correctly and leave as space after it\033[0m" << std::endl;
		break;
	case 27:
		std::cout << std::endl << "\033[31mInvalid format, type: no values were given\033[0m" << std::endl;
		break;
	case 28:
		std::cout << std::endl << "\033[31mInvalid format, type: one of the values is empty or two attributes were typed instead of one, the whole function will be cancelled, make sure no values are empty\033[0m" << std::endl;
		break;
	default:
		std::cout << std::endl << "\033[33mIf this message shows up it means that the error handler received an error code that doesn't exist yet, this code being " << errorCode << "\033[0m" << std::endl;
	}
}


int createColumn(std::string instruction, int source = 0)
{
	std::string temporary = "";
	std::string columnAtributes[4] = { "-","-","-","-" };
	int attributesCounter = 0;
	const int expectedNoOfAtributes = 3;
	bool isTableValid = true;
	removeSpaces(instruction);
	if (instruction == "")
	{
		/*std::cout << std::endl << "\033[31mInvalid format, type: empty instruction\033[0m" << std::endl;*/
		errorHandler(1);
		return 1; //WILL HANDLE ERROR HERE LATER
	}
	//std::cout << std::endl << "------------------" << instruction[instruction.length()-1]<<" "<<instruction[0] << "-----------------------" << std::endl;
	if (source == 0 && instruction[instruction.length() - 1] == ')' && instruction[0] == '(')
	{
		instruction = instruction.substr(1, instruction.length() - 1);
	}
	else if (source == 1 && instruction[0] == '(')
	{
		instruction = cut(instruction, 1);
	}
	else
	{
		/*std::cout << std::endl << "\033[31mInvalid format, type: there's an issue with the round brackets\033[0m" << std::endl;*/
		errorHandler(5);
		return 5; //WILL HANDLE ERROR HERE LATER
	}

	if (count(instruction, ',') == 3)
	{
		for (attributesCounter = 0; attributesCounter < expectedNoOfAtributes; attributesCounter++)
		{
			returnFirst(instruction, ",", temporary);
			instruction = cut(instruction, temporary.length() + 1);
			removeSpaces(temporary);
			if (temporary != "" && isValid(temporary))
			{
				columnAtributes[attributesCounter] = temporary;
			}
			else
			{
				/*std::cout << std::endl << "\033[31mInvalid format, type: one of the attributes is null or contains special characters\033[0m" << std::endl;*/
				errorHandler(11);
				return 11; //WILL HANDLE ERROR HERE LATER
			}
		}
		if (source == 0)
		{
			instruction = instruction.substr(0, instruction.length() - 1);
		}
		removeSpaces(instruction);
		if (isValid(instruction) && instruction != "")
		{
			columnAtributes[expectedNoOfAtributes] = instruction;
			instruction = "";
		}
		else
		{
			/*std::cout << std::endl << "\033[31mInvalid format, type: one of the attributes is null or contains special characters\033[0m" << std::endl;*/
			errorHandler(11);
			return 11; //WILL HANDLE ERROR HERE LATER
		}

	}
	else
	{
		/*std::cout << std::endl << "\033[31mInvalid format, type: one or more columns doesn't have the right number of attributes or there are empty spaces between the round brackets\033[0m" << std::endl;*/
		errorHandler(12);
		return 12; //WILL HANDLE ERROR HERE LATER
	}

	for (int i = 0; i < 4; i++)
	{
		std::cout << "\033[32m" << columnAtributes[i] << " \033[0m";
	}
	std::cout << std::endl;
	return 0;
}

///FUNCTIONS FOR COMMAND INTERPRETER
int INSERT(std::string instruction)
{
	const int intoSize = 4, valuesSize = 6;
	std::string temp = "";
	bool found = false;
	
	removeSpaces(instruction);
	if (instruction == "")
	{
		errorHandler(1);
		return 1;
	}
	if (instruction.substr(0, 5) != "INTO ")
	{
		errorHandler(25);
		return 25;
	}
	if (instruction.find(" VALUES ") == -1)
	{
		errorHandler(26);
		return 26;
	}

	instruction = cut(instruction, intoSize);
	returnFirst(instruction, "VALUES", temp);
	instruction = cut(instruction, temp.size());
	removeSpaces(temp);

	if (!isValid(temp) || temp == "")
	{
		errorHandler(4);
		return 4;
	}

	for (int i = 0; i < db.getTablesNo(); i++)
	{
		if (db.getTables()[i].getTableName() == temp)
		{
			found = true;
			std::cout << "Table: \033[32m" << temp << "\033[0m" << std::endl;
		}
	}
	if (found == false)
	{
		errorHandler(15, temp);
		return 15;
	}

	instruction = cut(instruction, valuesSize);

	removeSpaces(instruction);
	if (instruction[0] != '(' || instruction[instruction.size() - 1] != ')')
	{
		errorHandler(5);
		return 5;
	}
	instruction = instruction.substr(1, instruction.size() - 1);

	found = false;

	std::cout << "Values: \033[32m" << std::endl;

	returnFirst(instruction, ",", temp);
	while (temp != "-")
	{
		if (temp == "" || !isValidForInsert(temp))
		{
			errorHandler(28);
			return 28;
		}
		if (temp != "-")
		{
			found = true;
			instruction = cut(instruction, temp.size() + 1);
			removeSpaces(temp);
			std::cout << temp << " ";
			returnFirst(instruction, ",", temp);
		}
	}
	removeSpaces(instruction);
	if (instruction == ")" || !isValidForInsert(instruction.substr(0, instruction.length() - 2)))
	{
		errorHandler(28);
		return 28;
	}
	else
	{
		instruction = instruction.substr(0, instruction.size() - 1);
		removeSpaces(instruction);
		std::cout << instruction;
		found = true;
	}
	std::cout << "\033[0m" << std::endl;
	if (found == false)
	{
		errorHandler(27);
		return 27;
	}
	return 0;
}
int CREATE(std::string instruction)
{
	
	std::string tableWord = "TABLE", ifExists = "IF NOT EXISTS";
	std::string originalInstruction = instruction;
	std::string result = "-", temp = "", name = "", type = "", size = "", default_value = "";
	std::string tableName = "";
	bool ifExistsOption = false;
	char delimiter = ' ';
	int insertReturnCode = 0, createCode = 1, temporary = 0;
	int willNeverBeUsedAgain = -1;

	if (originalInstruction.empty())
	{
		/*std::cout << std::endl << "\033[31mInvalid format, type: empty instruction\033[0m" << std::endl;*/
		errorHandler(1);
		return 1; //WILL HANDLE ERROR HERE LATER
	}

	if (originalInstruction.find(tableWord) != -1)
	{
		if (originalInstruction[tableWord.length() + 1] != ' ')
		{
			/*std::cout << std::endl << "\033[31mInvalid format, type: no space between keyword TABLE and table name\033[0m" << std::endl;*/
			errorHandler(2);
			return 2; //WILL HANDLE ERROR HERE LATER
		}

		originalInstruction = cut(originalInstruction, tableWord.length() + 1);

		returnFirst(originalInstruction, "(", result);
		temporary = result.length();
		removeSpaces(result);

		if (result.find(ifExists) != -1)
		{
			size_t position = result.find(ifExists);
			if (position + ifExists.length() == result.length())
			{
				ifExistsOption = true;
				result = result.substr(0, position);
			}
			else
			{
				/*std::cout << std::endl << "\033[31mInvalid format, type: there are characters (including space) between IF NOT EXISTS and (\033[0m" << std::endl;*/
				errorHandler(9);
				return 9; //WILL HANDLE ERROR HERE LATER
			}
		}

		returnFirst(originalInstruction, ")", temp);
		if (result == "-" || temp == "-")
		{
			/*std::cout << std::endl << "\033[31mInvalid format, type: no ((...))\033[0m" << std::endl;*/
			errorHandler(3);
			return 3; //WILL HANDLE ERROR HERE LATER
		}
		else
		{
			instruction = cut(instruction, result.length());
			originalInstruction = cut(originalInstruction, temporary);
			//originalInstruction = cut(originalInstruction, result.length());
			removeSpaces(result);
			tableName = result;

			if (!isValid(tableName))
			{
				/*std::cout << std::endl << "\033[31mInvalid format, type: special characters found in table name or table name is missing\033[0m" << std::endl;*/
				errorHandler(4);
				return 4; //WILL HANDLE ERROR HERE LATER
			}
			if (tableName == "")
			{
				/*std::cout << std::endl << "\033[31mInvalid format, type: table name is missing\033[0m" << std::endl;*/
				errorHandler(4);
				return 4; //WILL HANDLE ERROR HERE LATER
			}
			if (ifExistsOption == true && db.checkIfTableExists(tableName))
			{
				/*std::cout << std::endl << "\033[31mInvalid table name, type: table name: "<<tableName <<" is already used\033[0m" << std::endl;*/
				errorHandler(7, tableName);
				return 7; //WILL HANDLE ERROR HERE LATER
			}
			else if (ifExistsOption == false && db.checkIfTableExists(tableName))
			{
				//errorHandler(8);
				return 8;
				//WILL HANDLE ERROR HERE LATER
			}
			else if (isValid(tableName) && tableName != "" && !db.checkIfTableExists(tableName));
			{
				Table temp(tableName);
				db.addTable(temp);
				std::cout << db.getTables()[db.getTablesNo() - 1].getTableName() << std::endl;
			}
		}
		//HANDLES CREATE TABLE NAME() ^^^^^

		//std::cout << tableName << std::endl;///DISPLAYED THE NAME TO SHOW IT WORKS
		originalInstruction = cut(originalInstruction, 1);
		originalInstruction = originalInstruction.substr(0, originalInstruction.length() - 1);

		if (count(originalInstruction, '(') != count(originalInstruction, ')') || (originalInstruction[0] != '(' || originalInstruction[originalInstruction.length() - 1] != ')'))
		{
			/*std::cout << std::endl << "\033[31mInvalid format, type: there's an issue with the round brackets\033[0m" << std::endl;*/
			errorHandler(5);
			return 5; //WILL HANDLE ERROR HERE LATER
		}
		result = "-";
		while (originalInstruction != "")
		{
			returnFirst(originalInstruction, "), (", result);
			if (result != "-")
			{
				originalInstruction = cut(originalInstruction, result.length() + 2);

				insertReturnCode = createColumn(result, createCode);
				if (insertReturnCode != 0)
				{
					/*std::cout << "\033[31mInvalid format, type: in the future the whole CREATE command will be cancelled, until then this message will show up\033[0m" << std::endl;*/
					errorHandler(6);
					return 6; //WILL HANDLE ERROR HERE LATER, MEANS THAT SOMETHING IS WRONG WITH THE ATTRIBUTES OF ONE COLUMN
				}
			}
			else
			{
				if (originalInstruction[originalInstruction.length() - 1] != ')')
				{
					/*std::cout << std::endl << "\033[31mInvalid format, type: there are more characters after the last ')'\033[0m" << std::endl;*/
					errorHandler(10);
					return 10; //WILL HANDLE ERROR HERE LATER
				}
				else
				{
					originalInstruction = originalInstruction.substr(0, originalInstruction.length() - 1);
					insertReturnCode = createColumn(originalInstruction, createCode);
					if (insertReturnCode != 0)
					{
						/*std::cout << "\033[31mInvalid format, type: in the future the whole CREATE command will be cancelled, until then this message will show up\033[0m" << std::endl;*/
						errorHandler(6);
						return 6; //WILL HANDLE ERROR HERE LATER, MEANS THAT SOMETHING IS WRONG WITH THE ATTRIBUTES OF ONE COLUMN
					}
					originalInstruction = "";
				}
			}
		}
	}
	else if (2 == 1)
	{
		//CREATING INDEX CASE
	}
	else
	{
		std::cout << std::endl << "\033[31mInvalid format, type: keyword TABLE not found\033[0m" << std::endl;
		return 4; //WILL HANDLE ERROR HERE LATER
		//NO KEYWORD FOUND CASE
	}
}
int UPDATE(std::string instruction)
{
	std::string temp = "";
	const int setSize = 3, whereSize = 5;
	bool found = false;

	removeSpaces(instruction);
	if (instruction == "")
	{
		errorHandler(1);
		return 1;
	}
	if (instruction.find(" SET ") == -1)
	{
		errorHandler(21);
		return 21;
	}
	if (instruction.find(" WHERE ") == -1)
	{
		errorHandler(20);
		return 20;
	}
	if (instruction.find(" SET ") > instruction.find(" WHERE "))
	{
		errorHandler(22);
		return 22;
	}
	returnFirst(instruction, "SET", temp);
	instruction = cut(instruction, temp.size());
	removeSpaces(temp);
	if (!isValid(temp) || temp == "")
	{
		errorHandler(4);
		return 4;
	}
	else
	{
		for (int i = 0; i < db.getTablesNo(); i++)
		{
			if (db.getTables()[i].getTableName() == temp)
			{
				found = true;
				std::cout << "Table: \033[32m" << temp << "\033[0m" << std::endl;
			}
		}
		if (found == false)
		{
			errorHandler(15, temp);
			return 15;
		}
	}
	instruction = cut(instruction, setSize);
	returnFirst(instruction, "WHERE", temp);
	instruction = cut(instruction, temp.size());
	removeSpaces(temp);
	if (temp == "")
	{
		errorHandler(23);
		return 23;
	}
	else
	{
		std::cout << "Column: \033[32m" << temp << "\033[0m" << std::endl;
	}
	instruction = cut(instruction, whereSize);
	removeSpaces(instruction);
	if (instruction == "")
	{
		errorHandler(24);
		return 24;
	}
	else
	{
		std::cout << "The condition is:\033[32m " << instruction << std::endl << "\033[33mJust to mention this, any conditions are not verified yet therefor they will only be display for now, the program will not return an error even if the condition is wrong/there are more than 1/etc, this WILL be changed in the future\033[0m" "\033[0m" << std::endl;
	}
	return 0;
}
int DROP(std::string instruction)
{
	std::string tableWord = "TABLE";
	std::string temp = "", copy = "";
	int tableWordSize = 5;
	bool found = false;

	removeSpaces(instruction);
	if (instruction == "")
	{
		errorHandler(1);
		return 1;
	}
	if (instruction.find(tableWord) == -1)
	{
		errorHandler(4);
		return 4;
	}
	copy = instruction;
	temp = cut(copy, tableWordSize);
	removeSpaces(temp);
	if (temp == "")
	{
		errorHandler(14);
		return 14;
	}
	if (instruction[tableWordSize] != ' ')
	{
		errorHandler(2);
		return 2;
	}
	instruction = cut(instruction, tableWordSize);
	removeSpaces(instruction);
	if (isValid(instruction) != true)
	{
		errorHandler(13, instruction);
		return 13;
	}
	else
	{
		for (int i = 0; i < db.getTablesNo(); i++)
		{
			if (db.getTables()[i].getTableName() == instruction)
			{
				found = true;
			}
		}
		if (found == true)
		{
			std::cout << "\033[32mTable: " << instruction << " will be deleted\033[0m" << std::endl;
		}
		else
		{
			errorHandler(15, instruction);
			return 15;
		}
	}
	return 0;
}
int DELETE(std::string instruction)
{
	std::string temp = "";
	bool isWhere = false, found = false;
	const int fromSize = 4, whereSize = 5;

	removeSpaces(instruction);
	if (instruction == "")
	{
		errorHandler(1);
		return 1;
	}
	if (instruction.substr(0, 4) != "FROM")
	{
		errorHandler(19);
		return 19;
	}
	else
	{
		instruction = cut(instruction, 4);
		if (instruction.find("WHERE ") != -1)
		{
			isWhere = true;
		}
		else
		{
			errorHandler(20);
			return 20;
		}

		returnFirst(instruction, "WHERE", temp);
		instruction = cut(instruction, temp.size());
		removeSpaces(temp);
		if (temp == "")
		{
			errorHandler(14);
			return 14;
		}
		if (!isValid(temp))
		{
			errorHandler(4);
			return 4;
		}
		for (int i = 0; i < db.getTablesNo(); i++)
		{
			if (db.getTables()[i].getTableName() == temp)
			{
				found = true;
				std::cout << "Table: \033[32m" << temp << "\033[0m" << std::endl;
			}
		}
		if (found == false)
		{
			errorHandler(15, temp);
			return 15;
		}
		instruction = cut(instruction, whereSize);
		removeSpaces(instruction);
		std::cout << "The condition is: \033[32m" << instruction << std::endl << "\033[33mJust to mention this, any conditions are not verified yet therefor they will only be display for now, the program will not return an error even if the condition is wrong/there are more than 1/etc, this WILL be changed in the future\033[0m" << std::endl;
	}
	return 0;
}
int DISPLAY(std::string instruction)
{
	std::string tableWord = "TABLE";
	std::string temp = "", copy = "";
	int tableWordSize = 5;
	bool found = false;

	removeSpaces(instruction);
	if (instruction == "")
	{
		errorHandler(1);
		return 1;
	}
	if (instruction.find(tableWord) == -1)
	{
		errorHandler(4);
		return 4;
	}
	copy = instruction;
	temp = cut(copy, tableWordSize);
	removeSpaces(temp);
	if (temp == "")
	{
		errorHandler(14);
		return 14;
	}
	if (instruction[tableWordSize] != ' ')
	{
		errorHandler(2);
		return 2;
	}
	instruction = cut(instruction, tableWordSize);
	removeSpaces(instruction);
	if (isValid(instruction) != true)
	{
		errorHandler(13, instruction);
		return 13;
	}
	else
	{
		for (int i = 0; i < db.getTablesNo(); i++)
		{
			if (db.getTables()[i].getTableName() == instruction)
			{
				found = true;
				std::cout << "Table: \033[32m" << instruction << "\033[0m" << std::endl;
			}
		}
		if (found == false)
		{
			errorHandler(15, instruction);
			return 15;
		}
	}
	return 0;
}
int SELECT(std::string instruction)
{
	removeSpaces(instruction);
	bool isAll = false, isWhere = false, found = false;
	int columnCount = 0;
	std::string temp = "", column = "";
	const int whereSize = 5;

	if (instruction == "")
	{
		errorHandler(1);
		return 1;
	}

	returnFirst(instruction, "ALL", temp);
	if (temp != "-")
	{
		isAll = true;
	}
	if (instruction.find('(') == 0 && instruction.find(")") != -1 && isAll == false)
	{
		instruction = cut(instruction, 1);
		returnFirst(instruction, ")", temp);
		instruction = cut(instruction, temp.size() + 1);
		removeSpaces(temp);
		while (!temp.empty() && temp.find(',') != -1)
		{
			if (temp[0] == ',')
			{
				temp = cut(temp, 1);
			}
			removeSpaces(temp);
			returnFirst(temp, ",", column);
			temp = cut(temp, column.size());
			if (temp[0] = ',')
			{
				temp = cut(temp, 1);
			}
			removeSpaces(column);
			if (isValid(column))
			{
				std::cout << "\033[32m" << column << " \033[0m" << std::endl;
				columnCount++;
			}
			else
			{
				errorHandler(16);
				return 16;
			}

			removeSpaces(temp);
		}
		if (!temp.empty())
		{
			removeSpaces(temp);
			if (isValid(temp))
			{
				std::cout << "\033[32m" << temp << " \033[0m" << std::endl;
				columnCount++;
			}
			else
			{
				errorHandler(16);
				return 16;
			}
		}
	}
	else if (isAll == false)
	{
		errorHandler(5);
		return 5;
	}

	if (isAll == false && columnCount == 0)
	{
		errorHandler(17);
		return 17;
	}

	if (isAll == true)
	{
		std::cout << "\033[32mIf this shows up it means that the ALL option is selected and all columns will be selected from the specified table \033[0m" << std::endl;
	}

	returnFirst(instruction, "FROM", temp);
	instruction = cut(instruction, temp.size());
	removeSpaces(temp);

	if (temp == "-")
	{
		errorHandler(19);
		return 19;
	}
	else if (!isValid(temp))
	{
		errorHandler(18);
		return 18;
	}
	removeSpaces(instruction);
	instruction = cut(instruction, 4);
	removeSpaces(instruction);
	if (instruction.find("WHERE") != -1)
	{
		isWhere = true;
	}
	if (isWhere == true)
	{
		returnFirst(instruction, "WHERE", temp);
	}
	else
	{
		temp = instruction;
	}
	instruction = cut(instruction, temp.size());
	removeSpaces(temp);
	if (isValid(temp) && temp != "-")
	{
		for (int i = 0; i < db.getTablesNo(); i++)
		{
			if (db.getTables()[i].getTableName() == temp)
			{
				found = true;
			}
		}
		if (found == true)
		{
			std::cout << "From the table:\033[32m" << temp << "\033[0m" << std::endl;
		}
		else
		{
			errorHandler(15, temp);
			return 15;
		}
	}
	else
	{
		errorHandler(4);
		return 4;
	}
	if (isWhere == true)
	{
		instruction = cut(instruction, whereSize);
		removeSpaces(instruction);
		std::cout << "The condition is:\033[32m " << instruction << std::endl << "\033[33mJust to mention this, any conditions are not verified yet therefor they will only be display for now, the program will not return an error even if the condition is wrong/there are more than 1/etc, this WILL be changed in the future\033[0m" "\033[0m" << std::endl;
	}

	return 0;
}