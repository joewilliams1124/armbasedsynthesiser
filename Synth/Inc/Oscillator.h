#ifndef __oscillator_H
#define __oscillator_H

#include "stm32f4xx_hal.h"
#include <math.h>

typedef struct
{
	float 	amp;	// Max of 1
	float	  freq;	// Hertz
	float   phase;	// radians
	float 	out;	// output sample
	float 	phaseInc;
	//Add Wavetype//
} oscillator;

void oscInit(oscillator * osc);

void oscSetFreq(oscillator * osc, float freq);

void oscSetPhaseInc(oscillator * osc);

float oscTic(oscillator * osc);

void generateSineTable(void);


#endif
