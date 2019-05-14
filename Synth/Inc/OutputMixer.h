#ifndef __OutputMixer_H
#define __OutputMixer_H

#include "stm32f4xx_hal.h"
#include <math.h>
#include "OutputMixer.h"

typedef struct
{
	uint16_t outpt;
	float volume1;
	float volume2;
}Mixer;

uint16_t castOutput(float value, Mixer * Mixer1);

#endif
