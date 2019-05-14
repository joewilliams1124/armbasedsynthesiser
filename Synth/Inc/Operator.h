#ifndef __operator_H
#define __operator_H

#include <math.h>
#include "oscillator.h"
#include "envelope.h"

typedef struct
{
	float   modInput;
	float   carrierInput;
	float 	modIndex;	// should be <= 1 for normal sound output
	float	  modAmount;	// Hertz
	float   detune;
	float 	out;	// output sample
	oscillator *osc;
	envelope *env;
} operator;

void opConnect(void);

//void voxConnect(void);

void opInit(int n);
	
void opTic(operator *op);

void opSet(operator *op, float modIndex, float modAmount, float detune);

float opTicker(float mod, operator *op );

#endif


