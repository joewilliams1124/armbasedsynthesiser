#include "envelope.h"
#include <math.h>
#include "stm32f4xx_hal.h"
#include "config.h"

//Change trigger to be part of typedef
int trigger = 0;

void envInit(envelope *env){
	env->aTime = 1;
	env->dTime = 1;
	env->sLevel = 1;
	env->rTime = 1;
	env->State = 'a';
	env->Count = 0;
	env->Out = 0;
}

//Function for setting ADSR more easily
void envSet(envelope *env, float aTime, float dTime, float sLevel, float rTime){
	env->aTime = aTime;
	env->dTime = dTime;
	env->sLevel = sLevel;
	env->rTime = rTime;
	attackSet(env); 
	decaySet(env);
	releaseSet(env);
	envCalc(env);
}

//Convert from seconds to samples. +5 to prevent dividing by 0. 
void attackSet(envelope *env){
	env->aSamples = (env->aTime * 44100) + 5;
	env->coeff[0] = 1 /env->aSamples;
}
void decaySet(envelope *env){
	env->dSamples = (env->dTime * 44100) + 5;
	env->coeff[1] = (env->sLevel - 1) / env->dSamples;
}
void releaseSet(envelope *env){
	env->rSamples = (env->rTime * 44100) + 5;
	env->coeff[2] = (env->sLevel / env->rSamples) * - 1;
}

//Calculate the transition points in relation to the start of the envelope
void envCalc(envelope *env){
	env->point[0] = env->aSamples;
	env->point[1] = env->aSamples + env->dSamples;
	env->point[2] = env->aSamples + env->dSamples + env->rSamples;
}

//Calculate the state of the envelope based on the trigger and counter//
void envState(envelope *env, int trigger){
	
	env->trigger = trigger;
	
if (env->Count < env->point[0]){
		env->State = 'a';
		//Attack//
	}
	if (env->Count >= env->point[0]){
		env->State = 'd';
		//Decay//
	}
	if ((env->Count >= env->point[1]) && (env->trigger == 1)){
		env->Count = env->Count - 1;
		env->State = 's';
		//Sustain//
	}
	if ((env->Count >= env->point[1]) && (env->trigger == 0)){
		env->State = 'r';	
		//Release//
	}
	if (env->Count >= env->point[2]){
		env->Count = env->Count - 1; //So the counter doesn't keep going//
		env->Out = 0;
		env->State = 's';
		//Hold off//
	}
}

//Calculate the output of the envelope based on the state//
float envTic(envelope *env){
	
	switch (env->State){
		case 'a': 
			env->Out = env->Out + env->coeff[0];
		break;
		
		case 'd':
			env->Out = env->Out + env->coeff[1];
		break;
		
		case 's':
			//This is the hold state the output stays the same//
		break;
		
		case 'r':
			env->Out = env->Out + env->coeff[2];
		break;
	}
	
	env->Count = env->Count + 1;
	
	return env->Out;
}



