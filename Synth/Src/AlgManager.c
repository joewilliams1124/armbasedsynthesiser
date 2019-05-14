#include "AlgManager.h"


//This file 'tics' all the oscillators, envelopes and operators 
//and defines how they interconnect.//

//Allow access to all envelopes, operators, oscillators & create an instance of the typedef
operator         ops[OPERATORS];
envelope 				envs[OPERATORS];
oscillator 			oscs[OPERATORS];
algSound vox;

static float sig[12];

//Read this webpage if you're not familiar with arrays of functions//
//https://cboard.cprogramming.com/c-programming/128162-array-functions.html
 
//Define an array of pointers to functions that return a float
float (*algs[11])();

//Trigger the correct algorithm based on the user defined variable vox.alg//
float algTic(){
	float out = algs[vox.alg]();
	return out;
}

//Ascociate operators with corresponding envelopes and oscillators
void opConnect(){
int n;
	for (n = 0; n < OPERATORS; n ++){
	ops[n].env = &envs[n];
	ops[n].osc = &oscs[n];
	}
}

//Initialise the Operator and the associated envelope and oscillator
void opInit(int n){
	ops[n].out = 0;
	envInit(ops[n].env);
	oscInit(ops[n].osc);
}

//Function to pass mod value to specified operator
float opTicker(float mod, operator *op){
	op->modInput = mod;
	opTic(op);
	return op->out;
}

//Defines how the operators interconnect to generate sound (the synthesis algorithm)//
float alg1(void){
	
	float out = 0;
	
	vox.noOfCarriers = 4;
	
	for (int i = 0; i < NUMOFVOXS * OPSPERVOX; i = i + OPSPERVOX){
		
		sig[i + 0] = opTicker( 0, &ops[i + 0] );
		sig[i + 1] = opTicker( 0, &ops[i + 1] );
		sig[i + 2] = opTicker( 0, &ops[i + 2] );
	  sig[i + 3] = opTicker( 0, &ops[i + 3] );
  
		out = (sig[i + 0] + sig[i + 1] + sig[i + 2] + sig[i + 3] + out);
	}

	return out;
}

float alg2(void){
	
	float out = 0;
	
	vox.noOfCarriers = 3;
	
	for (int i = 0; i < NUMOFVOXS * OPSPERVOX; i = i + OPSPERVOX){
		
		sig[i + 0] = opTicker( 0, &ops[i + 0] );
		sig[i + 1] = opTicker( sig[i + 0], &ops[i + 1] );
		sig[i + 2] = opTicker( 0, &ops[i + 2] );
		sig[i + 3] = opTicker( 0, &ops[i + 3] );
  
		out = (sig[i + 1] + sig[i + 2] + sig[i + 3] + out);
	}

	return out;

}

float alg3(void){
	
	float out = 0; 
	
	vox.noOfCarriers = 2;
	
	for (int i = 0; i < NUMOFVOXS * OPSPERVOX; i = i + OPSPERVOX){
		
		sig[i + 0] = opTicker( 0, &ops[i + 0] );
		sig[i + 1] = opTicker( sig[i + 0], &ops[i + 1] );
		sig[i + 2] = opTicker( 0, &ops[i + 2] );
		sig[i + 3] = opTicker( sig[i + 2], &ops[i + 3] );
  
		out = (sig[i + 1] + sig[i + 3] + out);
	}

	return out;
}

float alg4(void){
	
	float out = 0;
	
	vox.noOfCarriers = 2;
	
	for (int i = 0; i < NUMOFVOXS * OPSPERVOX; i = i + OPSPERVOX){
		
		sig[i + 0] = opTicker( 0, &ops[i + 0] );
		sig[i + 1] = opTicker( sig[i + 0], &ops[i + 1] );
		sig[i + 2] = opTicker( sig[i + 1], &ops[i + 2] );
		sig[i + 3] = opTicker( 0, &ops[i + 3] );
  
		out = (sig[i + 2] + sig[i + 3] + out);
	}

	return out;
}

float alg5(void){
	
	float out = 0;
	
	vox.noOfCarriers = 1;
	
	for (int i = 0; i < NUMOFVOXS * OPSPERVOX; i = i + OPSPERVOX){
		
		sig[i + 0] = opTicker( 0, &ops[i + 0] );
		sig[i + 1] = opTicker( sig[i + 0], &ops[i + 1] );
		sig[i + 2] = opTicker( sig[i + 1], &ops[i + 2] );
		sig[i + 3] = opTicker( sig[i + 2], &ops[i + 3] );
  
		out = (sig[i + 3] + out);
	}

	return out;
}

//This function writes pointers to each function into the array
void algsConnect(void){
	
	algs[1] = &alg1;
	algs[2] = &alg2;
	algs[3] = &alg3;
	algs[4] = &alg4;
	algs[5] = &alg5;

}
