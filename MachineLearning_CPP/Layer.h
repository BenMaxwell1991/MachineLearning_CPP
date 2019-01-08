#pragma once
#include <vector>
#include <string>
#include "Neuron.h"

class Layer
{
private:
	std::string Name;
	std::vector<Neuron*> Neurons;

public:

	void addNeuron();
	void connectNeurons(Layer &prevLayer);
	void propForward();

	std::string name();
	std::vector<Neuron*> neurons();
	int size();

	Layer(std::string aName = "", int aSize = 1);
	~Layer();
};