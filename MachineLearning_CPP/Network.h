#pragma once
#include <vector>
#include <list>
#include "Layer.h"

class Network
{
private:
	std::vector<Layer*> Layers;
	std::list<double> Accuracy;
	double Range;
	double Error;
	double Confidence;
	unsigned AvgNum;

public:
	// Trains this network using a specific dataSet
	void train(std::vector<std::vector<int>>& dataSet, unsigned avgNum, unsigned iterations, unsigned printInterval);

	// Prints off the current structure of this Nework for the user
	void printStructure();

	// Creates the connections between a layer of neurons and the previous layer
	void createConnections();

	// Propagates forward through each layer
	void feedForward(const std::vector<double> &inputs);

	// Propagates backward through each layer, learning.
	void backProp(const std::vector<double> &targetVals, double range);

	// Finds the error values and confidence levels
	void calcErrors(const std::vector<double> &targetVals, double range);

	// Returns a reference to the values of the output layer
	void getResults(std::vector<double> &resultVals);

	// Adds a new layer of neurons to the Network
	void addLayer(std::string name, int size);

	double error();
	double confidence();

	Network(std::vector<unsigned> const topology);
	~Network();
};

