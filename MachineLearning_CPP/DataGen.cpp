#include <iostream>
#include <vector>
#include "DataGen.h"


DataGen::DataGen()
{
}

void DataGen::createXOR(int aSize)
{
	std::vector<int> dataSet;
	int a, b, result;

	// Wipe previous dataset
	XOR.clear();

	for (int i = 0; i < aSize; i++)
	{
		dataSet.clear();
		a = std::rand() % 2;
		b = std::rand() % 2;

		if (a == b)
		{
			result = 0;
		}
		else
		{
			result = 1;
		}

		// Creates one set of data
		dataSet.push_back(a);
		dataSet.push_back(b);
		dataSet.push_back(result);

		// Add data to XOR collection
		XOR.push_back(dataSet);
	}	
}

void DataGen::printXOR()
{
	for (std::vector<int> dataSet : XOR)
	{
		std::cout << "In: " << dataSet[0] << " " << dataSet[1] << "\n";
		std::cout << "Out: " << dataSet[2] << "\n\n";
	}
}

std::vector<std::vector<int>>* DataGen::getXOR()
{
	return &XOR;
}

DataGen::~DataGen()
{
}
