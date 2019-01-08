#pragma once
#include <vector>

class DataGen
{
private:
	std::vector<std::vector<int>> XOR;

public:
	void createXOR(int aSize);
	void printXOR();

	std::vector<std::vector<int>>* getXOR();

	DataGen();
	~DataGen();
};

