#include "config.h"


//Set the values associated with the operator
void opSet(operator *op, float modIndex, float modAmount, float detune){
	op->modIndex = modIndex;
	op->modAmount = modAmount;
	op->detune = detune;
}

//Calculate the output of the operator
void opTic(operator *op){
	float scaledCarrier = (op->modIndex * op->carrierInput);
	float scaledMod = (op->modInput * scaledCarrier);
	oscSetFreq(op->osc, scaledMod + scaledCarrier + op->detune);
	op->out = oscTic(op->osc) * envTic(op->env);
	op->out = op->out * op->modAmount;
}

