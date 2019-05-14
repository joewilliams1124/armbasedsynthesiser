#include "Presets.h"

//Allow access to all envelopes, operators, oscillators & the parameters associated with the algorithm
extern envelope 			envs[OPERATORS];
extern operator        ops[OPERATORS];
extern oscillator 		oscs[OPERATORS];
extern algSound vox;

//Read this webpage if you're not familiar with arrays of functions//
//https://cboard.cprogramming.com/c-programming/128162-array-functions.html
 
//Define an array of pointers to functions that return a float
void  (*presets[6])();

//Take a value and use it to load the assosciated preset + algorithm
void selectSound(int n){
	vox.preset = n;
	vox.alg = n;
	presets[vox.preset]();
	linkVoxParamaters(); //Copy the values over to the other voices
}

//Define all the envelope and operator values for the preset. 
//When these functions are called, the values are loaded.

void preset1(void){
		
		opSet(&ops[0],1,1,1);
		opSet(&ops[1],0.5,0.1, 0);
		opSet(&ops[2],0.75,0.1, 0);
		opSet(&ops[3],2,0.1,0);
	
		envSet(&envs[0],0.01,0.03,1,0.2);
		envSet(&envs[1],0.1,0.01,0.1,0.3);
		envSet(&envs[2],0.1,0.02,0.2,0.1);
		envSet(&envs[3],0.1,1,1,0.3);	
}

void preset2(void){	
		
		opSet(&ops[0],1,1,0);
		opSet(&ops[1],2,0.5, 0);
		opSet(&ops[2],3,0.7, 0);
		opSet(&ops[3],1.2,0.2,0);
	
		envSet(&envs[0],0.01,0.03,1,0.2);
		envSet(&envs[1],0.1,0.01,0.1,0.3);
		envSet(&envs[2],0.1,0.02,0.2,0.1);
		envSet(&envs[3],0.1,1,1,0.3);	
}

void preset3(void){
		
		opSet(&ops[0],1,1,0);
		opSet(&ops[1],2,0.5, 0);
		opSet(&ops[2],3,0.7, 0);
		opSet(&ops[3],1.2,0.2,0);
	
		envSet(&envs[0],0.01,0.03,1,0.2);
		envSet(&envs[1],0.1,0.01,0.1,0.3);
		envSet(&envs[2],0.1,0.02,0.2,0.1);
		envSet(&envs[3],0.1,1,1,0.3);	
}

void preset4(void){
		
		opSet(&ops[0],1,1,0);
		opSet(&ops[1],2,0.5, 0);
		opSet(&ops[2],3,0.7, 0);
		opSet(&ops[3],1.2,0.2,0);
	
		envSet(&envs[0],0.01,0.03,1,0.2);
		envSet(&envs[1],0.1,0.01,0.1,0.3);
		envSet(&envs[2],0.1,0.02,0.2,0.1);
		envSet(&envs[3],0.1,1,1,0.3);	
}

void preset5(void){
		
		opSet(&ops[0],1,1,0);
		opSet(&ops[1],2,0.5, 0);
		opSet(&ops[2],3,0.7, 0);
		opSet(&ops[3],1.2,0.2,0);
	
		envSet(&envs[0],0.01,0.03,1,0.2);
		envSet(&envs[1],0.1,0.01,0.1,0.3);
		envSet(&envs[2],0.1,0.02,0.2,0.1);
		envSet(&envs[3],0.1,1,1,0.3);	
}

void presetsConnect(void){
	presets[1] = &preset1;
	presets[2] = &preset2;
	presets[3] = &preset3;
	presets[4] = &preset4;
	presets[5] = &preset5;
}
