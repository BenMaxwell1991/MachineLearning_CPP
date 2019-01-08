#include <cmath>
#include "Layer.h"


Layer::Layer(std::string aName, int aSize)
{
	Name = aName;

	for (int i = 0; i < aSize; i++)
	{
		addNeuron();
	};

	// Sets the output of the bias neuron to 1.0
	Neurons.back()->setOutput(1.0);
}


void Layer::addNeuron()
{
	unsigned index;

	index = size();
	Neuron* newNeuron = new Neuron(index);
	Neurons.push_back(newNeuron);
}

// Loop through each neuron in this layer, connecting them to the neurons in the previous layer
void Layer::connectNeurons(Layer &prevLayer)
{
	// Connect all neurons except the Bias neuron to the previous layer (including bias)
	for (int n = 0; n < Neurons.size() - 1; n++)
	{
		for (int j = 0; j < prevLayer.neurons().size(); j++)
		{
			double myRand = 1.0 * rand() / RAND_MAX;

			Neurons[n]->addConnection(prevLayer.neurons()[j], myRand);
		}		
	}
}

void Layer::propForward()
{
	for (int i = 0; i < Neurons.size(); i++)
	{
		Neurons[i]->feedForward();
	}
}


std::string Layer::name()
{
	return Name;
}


std::vector<Neuron*> Layer::neurons()
{
	return Neurons;
}


int Layer::size()
{
	return Neurons.size();
}


Layer::~Layer()
{
}