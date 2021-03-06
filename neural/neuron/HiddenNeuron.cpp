/*
 * HiddenNeuron.cpp
 *
 *  Created on: 5 sept. 2018
 *      Author: ezhor
 */

#include "HiddenNeuron.h"
#include "../layer/AbstractLayer.h"
#include "InputNeuron.h"

namespace neural {

HiddenNeuron::HiddenNeuron(AbstractLayer* previousLayer, ActivationFunctionInterface* activationFunction, BiasNeuron* biasNeuron) {
	this->bias = bias;
	this->activationFunction = activationFunction;
	createSynapses(previousLayer, biasNeuron);
}

HiddenNeuron::~HiddenNeuron() {
	for (unsigned int i = 0; i < synapses.size(); i++) {
		delete synapses.at(i);
	}
	synapses.clear();
}

double HiddenNeuron::propagate(){
	double result = 0;
	for (unsigned int i = 0; i < this->synapses.size(); ++i) {
		result += this->synapses.at(i)->propagate();
	}
	return this->activationFunction->calculate(result);
}

void HiddenNeuron::createSynapses(AbstractLayer* previousLayer, BiasNeuron* biasNeuron){
	this->synapses = vector<Synapse*>(previousLayer->getSize()+1);
	for (unsigned int i = 0; i < previousLayer->getSize(); i++) {
		synapses.at(i) = new Synapse(previousLayer->getNeuron(i), randomWeight());
	}
	this->synapses.at(this->synapses.size()-1) = new Synapse(biasNeuron, randomWeight());
}

} /* namespace neural */
