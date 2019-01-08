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

	void calcOutputGradients(double targetValue);
	void calcHiddenGradients(Layer* nextLayer);
	void updateConnectionWeights();

	void addConnection(Neuron* prevNeuron, double aWeight = 0.5);
	std::vector<Connection> connections();
	
	double sum();
	void feedForward();

	void setOutput(double value);
	double output();
	double errorGradient();

	Neuron(unsigned aIndex, double init_eta = 0.2, double init_alpha = 0.5);
	~Neuron();
};

