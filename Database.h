#pragma once
#include <iostream>

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
	rowData(int textCap, int integerCap, int floatCap);

	void setText(std::string data);
	void setInt(int data);
	void setFloat(float data);
};

class Table
{
public: 
	enum order {TEXT = 1, INTEGER = 2, FLOAT = 3};

private:
	std::string tableName = "";
	order* typesOrder = nullptr;
	std::string* attributeNames = nullptr;
	int totalCount = 0, textCount = 0, integerCount = 0, floatCount = 0;
	rowData* data = nullptr;
public:
	Table(std::string tableName);
	Table();

	std::string getTableName();
	void setTableName(std::string tableName);

	void operator=(const Table& other);
	bool operator==(Table other);

};

class DataBase
{
private:
	Table* tables = nullptr;
	int tablesNo = 0;

public:
	DataBase() = default;
	~DataBase();

	int getTablesNo();
	void setTablesNo(int tablesNo);

	void setTables(Table* tables);
	Table* getTables();

	void addTable(Table table);
	bool checkIfTableExists(std::string tableName);
};

extern DataBase db;