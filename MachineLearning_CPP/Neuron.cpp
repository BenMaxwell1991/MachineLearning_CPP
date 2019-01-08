#include <cmath>
#include "Layer.h"
#include "Neuron.h"
#include "Connection.h"


Neuron::Neuron(unsigned aIndex, double init_eta, double init_alpha)
{
	Index = aIndex;
	eta = init_eta;
	alpha = init_alpha;
}

void Neuron::addConnection(Neuron* prevNeuron, double aWeight)
{
	Connection newConnection;

	newConnection.setWeight(aWeight);
	newConnection.setTarget(prevNeuron);

	Connections.push_back(newConnection);
}

std::vector<Connection> Neuron::connections()
{
	return Connections;
}


double Neuron::sum()
{
	double total;

	total = 0;
	for (Connection& x : Connections)
	{
		total += (*(x.connectedTo())).output() * x.weight();
	}

	return total;
}

double Neuron::calcFunc(double x)
{
	return tanh(x);
}

double Neuron::calcFuncDiv(double x)
{
	return 1.0 - x * x;
}

double Neuron::sumDOW(Layer* nextLayer)
{
	double sum = 0.0;

	// Loop through the neurons in the next layer 
	// exclude bias neuron as it is not connected backwards
	for (int n = 0; n < nextLayer->size() - 1; n++)
	{
		double weight, errorGrad;
		Neuron* nextNeuron = nextLayer->neurons()[n];
		Connection connection = nextNeuron->connections()[Index];

		weight = connection.weight();
		errorGrad = nextNeuron->errorGradient();

		sum += weight * errorGrad;
	}

	return sum;
}

void Neuron::calcOutputGradients(double targetValue)
{
	double delta = targetValue - Output;
	ErrorGradient = delta * calcFuncDiv(Output);
}

void Neuron::calcHiddenGradients(Layer* nextLayer)
{
	double delta = sumDOW(nextLayer);
	ErrorGradient = delta * calcFuncDiv(Output);
}

void Neuron::updateConnectionWeights()
{
	for (Connection& aConnection : Connections)
	{
		Neuron* prevNeuron = aConnection.connectedTo();

		double prevDeltaWeight = aConnection.deltaWeight();
		double newDeltaWeight = (eta * prevNeuron->output() * ErrorGradient) + (alpha * prevDeltaWeight);

		aConnection.setDeltaWeight(newDeltaWeight);
		aConnection.setWeight(aConnection.weight() + newDeltaWeight);
	}
}

void Neuron::feedForward()
{
	double inputSum;

	inputSum = sum();

	setOutput(calcFunc(inputSum));
}

void Neuron::setOutput(double value)
{
	Output = value;
}

double Neuron::output()
{
	return Output;
}

double Neuron::errorGradient()
{
	return ErrorGradient;
}


Neuron::~Neuron()
{
}
