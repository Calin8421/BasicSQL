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

	~rowData()
	{
		delete[] textData;
		delete[] integerData;
		delete[] floatData;
		textData = nullptr;
		integerData = nullptr;
		floatData = nullptr;
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
public:
	
};

void main()
{
	//std::cout << "SQL Engine here";


}