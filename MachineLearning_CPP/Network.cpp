#include <iostream>
#include <vector>
#include <cassert>
#include "Network.h"
#include "Neuron.h"
#include "Connection.h"


Network::Network()
{	
	unsigned input, hidden, output;

	input = 2;
	hidden = 5;
	output = 1;

	std::cout << "Creating Network...\n\n";

	addLayer("Input", input + 1);
	addLayer("Hidden", hidden + 1);
	addLayer("Output", output + 1);

	createConnections();
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
void Network::backProp(const std::vector<double> &targetVals)
{
	Layer* outputLayer = Layers.back();
	Error = 0.0;

	assert(targetVals.size() == outputLayer->size() - 1);

	// Loop through the neurons in the final layer (except bias), determining the error from the 
	// RMS difference between targetVals and the output
	for (int n = 0; n < outputLayer->size() - 1; n++)
	{
		double delta = targetVals[n] - outputLayer->neurons()[n]->output();
		Error += delta * delta;
	}

	Error /= outputLayer->size() - 1;
	Error = sqrt(Error); // RMS Error

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


Network::~Network()
{
}
