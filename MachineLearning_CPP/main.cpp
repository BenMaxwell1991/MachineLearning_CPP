#include <iostream>
#include <vector>
#include "Network.h"
#include "DataGen.h"

// ~~~~~~~~~~~ Global Variables ~~~~~~~~~~~
// TODO: accept these as arguments for main()
bool PRINT_DEBUG = false;
unsigned PRINT_INTERVAL = 500;
unsigned ITERATIONS = 50000; 


// Creates a neural network, Creates an XOR dataset, Trains network using the dataset.
int main()
{
	// This defines the structure of the network: 
	// number of layers and number of neurons per layer
	std::vector<unsigned> topology;
	topology.push_back(2);
	topology.push_back(4);
	topology.push_back(3);
	topology.push_back(1);

	// Create network and data objects
	Network *myNetwork = new Network(topology);
	DataGen myData;

	// Create XOR dataSet 'myXOR'
	myData.createXOR(ITERATIONS);
	std::vector<std::vector<int>>& myXOR = *(myData.getXOR());

	// Debug Only: Print network structure
	if (PRINT_DEBUG) { myNetwork->printStructure(); }

	// Train network using XOR data
	myNetwork->train(myXOR, 50, ITERATIONS, PRINT_INTERVAL);
}