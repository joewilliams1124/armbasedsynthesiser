#include "Control.h"
#include "config.h"
#include "synth.h"
#include "VoxManager.h"

//Allow access to all envelopes, operators
extern envelope 	envs[OPERATORS];
extern operator   ops[OPERATORS];

//Allow acess to values from various typedefs
extern MIDImessage    MIDI;
extern Mixer 		Mixer1;
extern algSound vox;


int i = 1; 

//This function is used locally to convert values ranging from 0 - 127 to a user defined range
float scale127(int MIDIvalue, float max){
	float scaling =  max / 127;
	float value = (float) MIDIvalue * scaling;
	return value;
}

//Idealy the button reading process would be in an interupt handler
//void EXTI0_IRQHandler(){
//	btnCount();
//}

//This reads the button input, allows the user to toggle through 
//presets and displays the preset num on the LCDs//
void btnCount(){	
	if (BTN_Get() == 1){
		Mixer1.volume1 = 0;
			if (i > 4){
				i = 1;
				  BSP_LED_Off(0);
					BSP_LED_Off(1);
					BSP_LED_Off(2);
					BSP_LED_Off(3);
			} else {
	      	i ++;
	    }
		HAL_Delay(500);
	  selectSound(i);
	  BSP_LED_On(i -2);
	}
}

//This function maps the CCData recieved by the MIDI driver to paramaters within the synth model
void ControlCC(void){
		
		switch (MIDI.dataByte[0]){
		
		case 1: envs[2].aTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 2: envs[2].dTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 3: envs[2].sLevel = scale127(MIDI.ccData[1],1);
						releaseSet(&envs[2]);
			break;
		case 4: envs[2].rTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 5: envs[3].aTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 6: envs[3].dTime = scale127(MIDI.ccData[1],6.35);
			break;
			case 7: envs[3].sLevel = scale127(MIDI.ccData[1],1);
							releaseSet(&envs[3]);
			break;
		case 8: envs[3].rTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 9: Mixer1.volume2 = scale127(MIDI.ccData[9],1);
			break;		
		
		case 10 :ops[0].modIndex = scale127(MIDI.ccData[10],12.7);
			break;
		case 11 :ops[1].modIndex = scale127(MIDI.ccData[11],12.7);
			break;
		case 12 :ops[2].modIndex = scale127(MIDI.ccData[12],12.7);
			break;
		case 13 :ops[3].modIndex = scale127(MIDI.ccData[13],12.7);
			break;
		case 14: ops[0].modAmount = scale127(MIDI.ccData[14], 1);
			break;
		case 15: ops[1].modAmount = scale127(MIDI.ccData[15], 1);
			break;
		case 16: ops[2].modAmount = scale127(MIDI.ccData[16], 1);
			break;
		case 17: ops[3].modAmount = scale127(MIDI.ccData[17], 1);
			break;
		case 18: ops[0].detune = scale127(MIDI.ccData[18], 12.7);
			break;
		case 19: ops[1].detune = scale127(MIDI.ccData[19], 12.7);
			break;
		case 20: ops[2].detune = scale127(MIDI.ccData[20], 12.7);
			break;
		case 21: ops[3].detune = scale127(MIDI.ccData[21], 12.7);
			break;
	
	
		case 22: envs[0].aTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 23: envs[0].dTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 24: envs[0].sLevel = scale127(MIDI.ccData[1],1);
						 releaseSet(&envs[0]);
			break;
		case 25: envs[0].rTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 26: envs[1].aTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 27: envs[1].dTime = scale127(MIDI.ccData[1],6.35);
			break;
		case 28: envs[1].sLevel = scale127(MIDI.ccData[1],1);
						 releaseSet(&envs[0]);
			break;
		case 29: envs[1].rTime = scale127(MIDI.ccData[1],6.35);
			break;
		}
	
		//This function copies all the necessary parameters between voices
		linkVoxParamaters();
}

//float calcPitchBend(void){
	//	float n = MIDI.pitchBend * 0.00024414062; // ranges 0 to 4
	//	n = n - 2; // range -2 to + 2
	//  float pitchBendVal = pow(1.05946, n - 49);
	//	float pitchBendVal = n * 10;
	//  return pitchBendVal;
//}


void VelocityConnect(void){
		Mixer1.volume1 = scale127(MIDI.velocity, 0.9) + 0.1;
}


