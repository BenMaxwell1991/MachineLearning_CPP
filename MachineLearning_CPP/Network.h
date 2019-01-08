#pragma once
#include <vector>
#include "Layer.h"

class Network
{
private:
	std::vector<Layer*> Layers;
	double Error;

public:
	// Prints off the current structure of this Nework for the user
	void printStructure();

	// Creates the connections between a layer of neurons and the previous layer
	void createConnections();

	// Propagates forward through each layer
	void feedForward(const std::vector<double> &inputs);

	// Propagates backward through each layer, learning.
	void backProp(const std::vector<double> &targetVals);

	// Returns a reference to the values of the output layer
	void getResults(std::vector<double> &resultVals);

	// Adds a new layer of neurons to the Network
	void addLayer(std::string name, int size);

	double error();

	Network();
	~Network();
};

