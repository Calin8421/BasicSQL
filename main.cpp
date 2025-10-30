#include <iostream>
#include <string.h>

int DELETE()
{
	return 0;
}
int DISPLAY()
{
	return 0;
}
int SELECT()
{
	return 0;
}
int DROP()
{
	return 0;
}
int INSERT()
{
	return 0;
}
int UPDATE()
{
	return 0;
}
int CREATE()
{

	return 0;
}

int commander()
{

}

class row
{
	std::string name;
	std::string type;
	std::string size;
	std::string defaultValue;

};

class rowData
{
public:
	enum class dataTypes { TEXT, INTEGER, FLOAT };
private:
	std::string name;
	int capacity;
	int rowIndex;
	dataTypes type;

};



class Table
{
	std::string tableName;
	
};

void main()
{
	//std::cout << "SQL Engine here";


}