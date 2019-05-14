#include "VoxManager.h"
#include "config.h"

extern envelope 			envs[OPERATORS];
extern operator        ops[OPERATORS];
extern oscillator 		oscs[OPERATORS];

extern algSound vox;


//Resets a given voice
void voxReset(int n){ 
	
	for (int i = n*(OPSPERVOX - 1); i < ((n+1)*OPSPERVOX); i ++){
		//Only recalculate the envelope when the voice is reset
		attackSet(&envs[i]);
		decaySet(&envs[i]);
		releaseSet(&envs[i]);
		envCalc(&envs[i]);
		envs[i].Count = 0;
		envs[i].Out = 0;
	}
	
}

//Update the operators ascossiated each voice
void voxTicker(int voxNumber, int trigger){
	int n = voxNumber;
		
	for (int i = n*(OPSPERVOX - 1); i < ((n+1)*OPSPERVOX); i ++){
			envState(ops[i].env, trigger);
		}
}

//This function 
void setCarrierForVoice(int voxNumber, int note){
	int n = voxNumber;
	float carrier = noteToFreq(note); //Change
	for (int i = n*(OPSPERVOX - 1); i < ((n+1)*OPSPERVOX); i ++){
		ops[i].carrierInput = carrier;
	}
}

//Copy relevant parameters from vox one an all other voices
void linkVoxParamaters(void){
	for (int i = 0; i < NUMOFVOXS; i ++){
		ops[i+4].modIndex = ops[i].modIndex;
		ops[i+4].detune = ops[i].modIndex;
		envs[i+4].aTime = envs[i].aTime;
		envs[i+4].dTime = envs[i].aTime;
		envs[i+4].sLevel = envs[i].aTime;
		envs[i+4].rTime = envs[i].aTime;
	}
}
