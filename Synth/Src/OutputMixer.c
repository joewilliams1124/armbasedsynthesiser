#include <math.h>
#include "OutputMixer.h"
#include "AlgManager.h"

Mixer 		Mixer1;
extern algSound vox;

//Scale the output of the operator down from 0 -1 then cast to correct type for audio buffer

uint16_t castOutput(float value, Mixer * Mixer1){
	value = value * Mixer1->volume1 * Mixer1->volume2; //Scale the volume based on a user controlled parameter
	value = value * 32767 / vox.noOfCarriers; // Multiply value to fill 16 bit depth (4 operators maximum amp 1 on input)
	Mixer1->outpt = (uint16_t)((int32_t)(value)); //Cast the value data type for audio driver
	int16_t a = Mixer1->outpt;
	return a;
}

//Write a compressor


// Equaliser?

// Low pass filter??
