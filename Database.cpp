///PHASE 1
#include "Database.h"
#include "Utils.h"
#include "Commands.h"
#include <iostream>

// ============ rowData method definitions ============

rowData::rowData(int textCap, int integerCap, int floatCap)
{
    this->textCap = textCap;
    this->integerCap = integerCap;
    this->floatCap = floatCap;
    if (this->textCap > 0)    textData = new std::string[this->textCap];
    if (this->integerCap > 0) integerData = new int[this->integerCap];
    if (this->floatCap > 0)   floatData = new float[this->floatCap];
}

void rowData::setText(std::string data)
{
    if (textIndex < textCap)
    {
        textData[textIndex] = data;
        textIndex++;
    }
}

void rowData::setInt(int data)
{
    if (integerIndex < integerCap)
    {
        integerData[integerIndex] = data;
        integerIndex++;
    }
}

void rowData::setFloat(float data)
{
    if (floatIndex < floatCap)
    {
        floatData[floatIndex] = data;
        floatIndex++;
    }
}


// ============ Table method definitions ============

Table::Table(std::string tableName)
{
    this->tableName = tableName;
}

Table::Table() {}

std::string Table::getTableName()
{
    return this->tableName;
}

void Table::setTableName(std::string tableName)
{
    this->tableName = tableName;
}

void Table::operator=(const Table& other)
{
    this->tableName = other.tableName;

    // Copy all primitive types
    this->totalCount = other.totalCount;
    this->textCount = other.textCount;
    this->integerCount = other.integerCount;
    this->floatCount = other.floatCount;

    // For pointers - set to nullptr for now (you'll handle properly later)
    this->typesOrder = nullptr;
    this->attributeNames = nullptr;
    this->data = nullptr;

    // TODO: Properly copy dynamic arrays in Phase 2
}

bool Table::operator==(Table other)
{
    return this->getTableName() == other.getTableName();
}


// ============ DataBase method definitions ============

int DataBase::getTablesNo()
{
    return this->tablesNo;
}

void DataBase::setTablesNo(int tablesNo)
{
    this->tablesNo = tablesNo;
}

void DataBase::setTables(Table* tables)
{
    if (tablesNo > 0)
    {
        if (this->tables != nullptr)
        {
            delete[] this->tables;
        }
        this->tables = new Table[tablesNo];
        for (int i = 0; i < tablesNo; i++)
        {
            this->tables[i] = tables[i];
        }
    }
}

Table* DataBase::getTables()
{
    return this->tables;
}

void DataBase::addTable(Table table)
{
    if (tablesNo == 0)
    {
        tablesNo++;
        tables = new Table[tablesNo];
        tables[0] = table;
    }
    else if (tablesNo > 0)
    {
        Table* newTables = new Table[tablesNo + 1];

        for (int i = 0; i < tablesNo; i++)
        {
            newTables[i] = tables[i];
        }

        newTables[tablesNo] = table;

        delete[] tables;
        tables = newTables;
        tablesNo++;
    }
}

bool DataBase::checkIfTableExists(std::string tableName)
{
    for (int i = 0; i < tablesNo; i++)
    {
        if (this->tables[i].getTableName() == tableName)
        {
            return true;
        }
    }
    return false;
}

DataBase::~DataBase()
{
    if (tables != nullptr)
    {
        delete[] tables;
        tables = nullptr;
    }
}

// ====== global instance definition ======
DataBase db;
