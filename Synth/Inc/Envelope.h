#ifndef __envelope_H
#define __envelope_H

typedef struct
{
	float 	aTime;	
	float 	dTime;	
	float 	sLevel;
	float 	rTime;
	float aSamples;
	float dSamples;
	float rSamples;
	float coeff[3];
	int 	point[3];
	float 	Count;
	char 		State;
	float   Out;
	int trigger;
	//Change to have a trigger here
} envelope;

void envInit(envelope *env);

void envSet(envelope *env, float aTime, float dTime, float sLevel, float rTime);

void envState(envelope *env, int trigger);

void envCalc(envelope *env);

void attackSet(envelope *env);

void decaySet(envelope *env);

void releaseSet(envelope *env);

float envTic(envelope *env);


#endif

