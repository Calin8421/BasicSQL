///PHASE 1
#include "Commands.h"
#include "Utils.h"
#include "Database.h"
#include <iostream>


///DYNAMIC TABLE ALLOC
///DECONSTRUCT THIS

void showCommands()
{
	std::cout << std::endl;
	std::cout << "<=================================== SQL COMMAND HELP ===================================>" << std::endl;
	std::cout << "COMMAND   | DESCRIPTION" << std::endl;
	std::cout << "---------------------------------------------------------------------------------" << std::endl;
	std::cout << "INSERT    | Adds new rows of data into a table." << std::endl;
	std::cout << "          | Example: INSERT INTO employees " << std::endl;
	std::cout << "          |           VALUES (id INT,name TEXT,salary FLOAT,DEFAULT_VALUE);" << std::endl << std::endl;

	std::cout << "SELECT    | Retrieves data from one or more tables." << std::endl;
	std::cout << "          | Example: SELECT name, salary FROM employees" << std::endl;
	std::cout << "          |           WHERE salary > 3000;" << std::endl << std::endl;

	std::cout << "UPDATE    | Modifies existing rows in a table." << std::endl;
	std::cout << "          | Example: UPDATE employees SET salary = 6000" << std::endl;
	std::cout << "          |           WHERE name = 'John';" << std::endl << std::endl;

	std::cout << "DELETE    | Removes rows from a table." << std::endl;
	std::cout << "          | Example: DELETE FROM employees WHERE name = 'John';" << std::endl << std::endl;

	std::cout << "CREATE    | Creates a new database object (e.g., table)." << std::endl;
	std::cout << "          | Example: CREATE TABLE employees ((id INT,name TEXT,salary FLOAT,DEFAULT_VAL));" << std::endl << std::endl;

	std::cout << "DROP      | Deletes a database object permanently." << std::endl;
	std::cout << "          | Example: DROP TABLE employees;" << std::endl << std::endl;

	std::cout << "DISPLAY   | Shows the content of the current database or table (custom command)." << std::endl;
	std::cout << "          | Example: DISPLAY employees;" << std::endl << std::endl;

	std::cout << "ALTER     | " << std::endl;
	std::cout << "          | "<< std::endl << std::endl;

	std::cout << "CLEAR     | Clears the screen or console output (custom shell command)." << std::endl;
	std::cout << "          | Example: CLEAR;" << std::endl << std::endl;

	std::cout << "HELP/INFO | Shows help information about available commands." << std::endl;
	std::cout << "          | Example: HELP;" << std::endl << std::endl;

	std::cout << "QUIT/EXIT | Closes the SQL console." << std::endl;
	std::cout << "          | Example: QUIT;" << std::endl << std::endl;

	std::cout << "<========================================================================================>" << std::endl;
}

///FIX THIS (XYY FORMAT - (X -> 1=CREATEM, 2=INSERT... ; YY -> PROBLEM INDEX))
void errorHandler(int errorCode, std::string tableName = "")
{
	
}



///FUNCTIONS FOR COMMAND INTERPRETER
//ORDER:
//1.FROM
//2.WHERE
//3 GROUP BY
//4 HAVING
//5 SELECT
//6 DISTINCT  
//7 ORDER BY


int SELECT(std::string instruction)
{
	std::cout << instruction<< std::endl;
	return 0;
}
int DROP(std::string instruction)
{
	std::cout << instruction << std::endl;
	return 0;
}
int INSERT(std::string instruction)
{
	std::cout << instruction << std::endl;
	return 0;
}
int CREATE(std::string instruction)
{
	std::cout << instruction << std::endl;
	return 0;
}
int UPDATE(std::string instruction)
{
	std::cout << instruction << std::endl;
	return 0;
}
int DELETE(std::string instruction)
{
	std::cout << instruction << std::endl;
	return 0;
}
int DISPLAY(std::string instruction)
{
	std::cout << instruction << std::endl;
	return 0;
}
int ALTER(std::string instruction)
{
	std::cout << instruction << std::endl;
	return 0;
}


///make this in to a int to return the error codes from the sql functions
std::string commander(const std::string token, std::string inputCommand, bool& quit)
{
	///toUpper(command);
	if (token == "CREATE")
	{
		CREATE(inputCommand);
		return "CREATE";
		///ex: return CREATE(instruction);
	}
	else if (token == "INSERT")
	{
		INSERT(inputCommand);
		return "INSERT";
	}
	else if (token == "UPDATE")
	{
		UPDATE(inputCommand);
		return "UPDATE";
	}
	else if (token == "DROP")
	{
		DROP(inputCommand);
		return "DROP";
	}
	else if (token == "SELECT")
	{
		SELECT(inputCommand);
		return "SELECT";
	}
	else if (token == "DELETE")
	{
		DELETE(inputCommand);
		return "DELETE";
	}
	else if (token == "DISPLAY")
	{
		DISPLAY(inputCommand);
		return "DISPLAY";
	}
	else if (token == "ALTER")
	{
		ALTER(inputCommand);
		return "ALTER";
	}
	else if (token == "QUIT" or token == "EXIT")
	{
		quit = true;
		return "QUIT";
	}
	else if (token == "INFO" or token == "HELP")
	{
		showCommands();
		return "INFO";
	}
	else if (token == "CLEAR")
	{
		system("cls");
		return "CLEAR";
	}
	std::cout << "UNKNOWN. Try inserting <HELP> for command manual!" << std::endl << std::endl;
	return "UNKNOWN";
}