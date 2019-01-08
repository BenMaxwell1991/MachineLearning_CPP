#include <iostream>
#include <vector>
#include "Network.h"
#include "DataGen.h"

bool PRINT_DEBUG = false;

int main()
{
	int iterations, printInterval;
	Network myNetwork;
	DataGen myData;

	std::vector<double> inputVals, targetVals, resultVals;

	myNetwork.printStructure();

	system("pause");

	iterations = 5000;

	myData.createXOR(iterations);

	if (PRINT_DEBUG)
	{
		myData.printXOR();
		system("pause");
	}
	

	for (int i = 0; i < iterations; i++)
	{
		int a, b, target;
		std::vector<std::vector<int>> myXOR;

		myXOR = *(myData.getXOR());
		a = myXOR[i][0];
		b = myXOR[i][1];
		target = myXOR[i][2];

		inputVals.clear();
		inputVals.push_back(a);
		inputVals.push_back(b);

		targetVals.clear();
		targetVals.push_back(target);

		// One training cycle
		myNetwork.feedForward(inputVals);
		myNetwork.backProp(targetVals);
		myNetwork.getResults(resultVals);

		// Prints results
		if (PRINT_DEBUG) { printInterval = 1; } else { printInterval = 100; }		

		if (i % printInterval == 0)
		{
			std::cout << "Iteration " << i << ":\n";
			std::cout << "Inputs: " << inputVals[0] << " " << inputVals[1] << "\n";
			std::cout << "Outputs: " << resultVals[0] << "\n";
			std::cout << "Targets: " << targetVals[0] << "\n";			
			std::cout << "RMS Error: " << myNetwork.error() << "\n\n";
		}		
	}
	system("pause");
}