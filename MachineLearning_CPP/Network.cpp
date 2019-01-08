#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "Network.h"
#include "Neuron.h"
#include "Connection.h"


Network::Network(std::vector<unsigned> const topology)
{	
	std::cout << "Creating Network...\n\n";

	// Add the first layer as the Input layer
	addLayer("Input", topology[0] + 1);

	// Loop through all layers between the first and last, adding them as hidden layers
	for (unsigned L = 1; L < topology.size() - 1; L++)
	{
		addLayer("Hidden", topology[L] + 1);
	}
	
	// Add the final layer as the Output layer
	addLayer("Output", topology.back() + 1);

	createConnections();
}

void Network::train(std::vector<std::vector<int>>& dataSet, unsigned avgNum, unsigned iterations, unsigned printInterval)
{
	std::vector<double> inputVals, targetVals, resultVals;
	double range;

	AvgNum = avgNum;

	for (unsigned i = 0; i < iterations; i++)
	{
		inputVals.clear();
		inputVals.push_back(dataSet[i][0]);
		inputVals.push_back(dataSet[i][1]);

		targetVals.clear();
		targetVals.push_back(dataSet[i][2]);

		range = dataSet[i][3];

		// One training cycle
		feedForward(inputVals);
		backProp(targetVals, range);
		getResults(resultVals);

		// Prints results
		if (i % printInterval == 0)
		{
			std::cout << "Iteration " << i << ":\n";
			std::cout << "Inputs: " << inputVals[0] << " " << inputVals[1] << "\n";
			std::cout << "Outputs: " << resultVals[0] << "\n";
			std::cout << "Targets: " << targetVals[0] << "\n";
			std::cout << "RMS Error: " << error() << "\n";
			std::cout << avgNum << "-Point Recent Confidence Level: " << confidence() << "%\n\n";
		}
	}
	system("pause");
}

void Network::printStructure()
{
	int connections;

	std::cout << "Printing Network Setup:\n\n";

	for (int i = 0; i < Layers.size(); i++)
	{
		std::cout << "Layer " << i << ":\n" << "Name = " << Layers[i]->name().c_str() << "\nSize = " << Layers[i]->size() << "\n";

		// Finds the number of connections between this Layer[i] and the previous layer
		connections = 0;
		for (int j = 0; j < (*Layers[i]).neurons().size(); j++)
		{
			connections += (*((*Layers[i]).neurons()[j])).connections().size();
		}
		std::cout << "Total Connections = " << connections << "\n\n";		
	}
	system("pause");
}

void Network::createConnections()
{
	// Start at layer 1, Input layer has no previous connections
	for (int i = 1; i < Layers.size(); i++)
	{
		Layers[i]->connectNeurons(*Layers[i - 1]);
	}
}

void Network::feedForward(const std::vector<double> &inputs)
{
	// Size of inputs vector must match size of input layer (without bias neuron)
	assert(inputs.size() == Layers[0]->size() - 1);

	// Sets the output of the input neurons to the input values
	for (int i = 0; i < inputs.size(); i++)
	{
		Layers[0]->neurons()[i]->setOutput(inputs[i]);
	}

	// Propagets forward through the network using the connection weights
	for (int layerNum = 1; layerNum < Layers.size(); layerNum++)
	{
		Layers[layerNum]->propForward();
	}
}

// Propagate backwards through the neural net, adjusting weights based upon improvement from the previous iteration
void Network::backProp(const std::vector<double> &targetVals, double range)
{
	Layer* outputLayer = Layers.back();
	assert(targetVals.size() == outputLayer->size() - 1);

	// Calculates the errors based on the most recent iteration, and tracks the level of confidence
	calcErrors(targetVals, range);

	// Loop through the neurons in the final layer (except bias)
	//calculating and setting their error gradients
	for (int n = 0; n < outputLayer->size() - 1; n++)
	{
		outputLayer->neurons()[n]->calcOutputGradients(targetVals[n]);
	}

	// Loop through all neurons within hidden layers, calculating their error gradients
	// This is based upon their contribution to the next layers error
	for (int L = Layers.size() - 2; L > 0; L--)
	{
		Layer* hiddenLayer = Layers[L];
		Layer* nextLayer = Layers[L + 1];

		for (int n = 0; n < hiddenLayer->size(); n++)
		{
			hiddenLayer->neurons()[n]->calcHiddenGradients(nextLayer);
		}
	}

	// Loop through each layer (except the first layer) updating connection weights
	for (int L = Layers.size() - 1; L > 0; L--)
	{
		Layer* layer = Layers[L];
		Layer* prevLayer = Layers[L - 1];

		// Loop through each neuron in the layer 
		// (except bias as it has no previous connections)
		for (int n = 0; n < layer->size() - 1; n++)
		{
			layer->neurons()[n]->updateConnectionWeights();
		}
	}
}

void Network::calcErrors(const std::vector<double> &targetVals, double range)
{
	Layer* outputLayer = Layers.back();
	double thisAccuracy;
	thisAccuracy = 0.0;
	Error = 0.0;
	Confidence = 0.0;

	// Loop through the neurons in the final layer (except bias), determining the error from the 
	// RMS difference between targetVals and the output
	for (int n = 0; n < outputLayer->size() - 1; n++)
	{
		double delta = targetVals[n] - outputLayer->neurons()[n]->output();
		Error += delta * delta;

		// sum of percentage accuracy of each output
		thisAccuracy += 100.0 * (range - abs(delta) / range);
	}

	Error /= outputLayer->size() - 1;
	Error = sqrt(Error); // RMS Error

	// average percentage accurancy
	thisAccuracy /= outputLayer->size() - 1;

	// Add this accuracy to a list of previous accuracies
	Accuracy.push_front(thisAccuracy);
	if (Accuracy.size() > AvgNum) { Accuracy.pop_back(); }

	for (double &acc : Accuracy)
	{
		Confidence += acc;
	}

	Confidence /= Accuracy.size();
}

void Network::getResults(std::vector<double> &resultVals)
{
	resultVals.clear();

	for (int n = 0; n < Layers.back()->neurons().size() - 1; n++)
	{
		Neuron* neuron = Layers.back()->neurons()[n];
		resultVals.push_back(neuron->output());
	}
}

void Network::addLayer(std::string aName, int aSize)
{
	Layer* newLayer = new Layer(aName, aSize);
	this->Layers.push_back(newLayer);
}

double Network::error()
{
	return Error;
}

double Network::confidence()
{
	return Confidence;
}


Network::~Network()
{
}
