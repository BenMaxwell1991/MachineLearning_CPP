#pragma once
#include <vector>

class DataGen
{
private:
	std::vector<std::vector<int>> XOR;

public:
	// Creates a set of XOR data of aSize. Format: [Input_1, Input_2, Output, OutputRange]
	void createXOR(int aSize);

	// Prints the XOR dataset to the std out
	void printXOR();

	// Returns a pointer to the XOR data object
	std::vector<std::vector<int>>* getXOR();

	DataGen();
	~DataGen();
};

