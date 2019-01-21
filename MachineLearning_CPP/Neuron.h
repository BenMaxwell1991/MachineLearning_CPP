#pragma once
#include <vector>

// Forward declaration
class Connection;

class Layer;

class Neuron
{
private:

	double calcFunc(double x);
	double calcFuncDiv(double x);
	double sumDOW(Layer* nextLayer);

	std::vector<Connection> Connections;
	double Input;
	double Value;
	double Output;
	double ErrorGradient;

	double eta; // Training Rate
	double alpha; // Learning Momentum

	unsigned Index;

public:

	// Calculate the error gradient of the output Neuron compared to the expected result
	void calcOutputGradients(double targetValue);

	// Calculate a Neuron within a hidden layer's contribution to the error of the next layer
	void calcHiddenGradients(Layer* nextLayer);

	// Update all of the connection weights between this Neuron and the previous layer, based on error contributions and learning momentum.
	void updateConnectionWeights();

	// Add a new connection to this Neuron, must specificy a target neuron to be connected to.
	void addConnection(Neuron* prevNeuron, double aWeight = 0.5);

	// Sums the value of each connection times it's weight.
	double sum();

	// This Neuron uses it's sum function, and bounds this input between -1 & 1 using 'tanh(x)', then uses this as an output
	void feedForward();


// ~~~~~~~~~~~~~~~ Getters & Setters ~~~~~~~~~~~~~~~
	void setOutput(double value);

	double output();
	double errorGradient();
	std::vector<Connection> connections();
// ~~~~~~~~~~~~~~~ Getters & Setters ~~~~~~~~~~~~~~~


	Neuron(unsigned aIndex, double init_eta = 0.2, double init_alpha = 0.5);
	~Neuron();
};

