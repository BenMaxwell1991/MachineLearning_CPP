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

	// Adds a new Neuron to this layer
	void addNeuron();

	// given a target 'prevLayer' generates neuron connections between the two layers
	void connectNeurons(Layer &prevLayer);

	// Loop through each Neuron within this Layer, calculating their outputs from their inputs
	void propForward();


// ~~~~~~~~~~~~~~~ Getters & Setters ~~~~~~~~~~~~~~~
	std::string name();
	std::vector<Neuron*> neurons();
	int size();
// ~~~~~~~~~~~~~~~ Getters & Setters ~~~~~~~~~~~~~~~

	Layer(std::string aName = "", int aSize = 1);
	~Layer();
};