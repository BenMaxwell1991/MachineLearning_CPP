#pragma once

// Forward declaration
class Neuron;

class Connection
{
private:
	Neuron* OtherNeuron;
	double Weight;
	double DeltaWeight;

public:

// ~~~~~~~~~~~~~~~ Getters & Setters ~~~~~~~~~~~~~~~
	double weight();
	double deltaWeight();
	Neuron* connectedTo();

	void setWeight(double value);
	void setDeltaWeight(double value);
	void setTarget(Neuron* value);
// ~~~~~~~~~~~~~~~ Getters & Setters ~~~~~~~~~~~~~~~

	Connection();
	~Connection();
};

