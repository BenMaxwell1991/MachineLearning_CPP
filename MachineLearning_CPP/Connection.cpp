#include "Connection.h"
#include "Neuron.h"


Connection::Connection()
{
}


double Connection::weight()
{
	return Weight;
}

double Connection::deltaWeight()
{
	return DeltaWeight;
}

Neuron* Connection::connectedTo()
{
	return OtherNeuron;
}


void Connection::setWeight(double value)
{
	Weight = value;
}

void Connection::setDeltaWeight(double value)
{
	DeltaWeight = value;
}

void Connection::setTarget(Neuron* value)
{
	OtherNeuron = value;
}


Connection::~Connection()
{
}
