#include "oscillator.h"
#include "config.h"

float SineTable[SINELOOKUPSIZE];

//Initialize an oscillator 
void oscInit(oscillator *osc){
	osc->amp = 1; 
	//osc->freq = 261.6;
	osc->phase = 0;
	osc->out = 0;
	osc->phaseInc = 1;
	oscSetPhaseInc(osc);
}

//set the frequency, then compute the corresponding increment needed in the phase table
void oscSetFreq(oscillator *osc, float f){
	osc->freq = f;
	oscSetPhaseInc(osc);
}

//Work out the phase increment needed for the frequency specified
void oscSetPhaseInc(oscillator *osc){
	osc->phaseInc = SINELOOKUPSIZE * osc->freq / 44100;
}

//Add the phase increment and output the corresponding value in the LUT
float oscTic(oscillator *osc){
	osc->phase += osc->phaseInc; //Add the phase increment to the accumulating phase
	if (osc->phase > SINELOOKUPSIZE) osc->phase -= SINELOOKUPSIZE; //Ensure the phase is within the LUTSize
	osc->out = SineTable[(uint16_t)(osc->phase)] * osc->amp;  //Quantize to the nearest integer, use this to index the sinetable
	return osc->out;
}

//// Set up the sine look-up table:
void generateSineTable(){
	for (int i = 0; i <= SINELOOKUPSIZE; i++) {
		float q = sin(i * 2.0 * PI / SINELOOKUPSIZE);
		SineTable[i] = q;
	}
}
