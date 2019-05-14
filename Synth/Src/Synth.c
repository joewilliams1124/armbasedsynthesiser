//THIS WILL HAVE A FUNCTION WHICH OUTPUTS THE CORRECT SYNTH AUDIO//
//IT'LL ALSO HAVE SOME ERROR HANDLING AND BOOT UP PROTOCOL//
//IT'LL CALL THE FUNCTIONS FROM PRESET MANAGER + OUTPUT MIXER//
#include "OutputMixer.h"
#include "MIDI.h"
#include "Control.h"
#include "config.h"

extern Mixer	        Mixer1;
extern MIDImessage		MIDI;

//Top level controls for model//

void synthInit(){
	generateSineTable();
	opConnect();
	algsConnect();
	presetsConnect();
	for (int i = 0; i < OPERATORS; i ++){
		opInit(i);
	}	
	selectSound(1);
}


float synthTic(){
	
	setCarrierForVoice(0, MIDI.noteNum[0]);
	voxTicker(0, MIDI.trigger[0]);
	
	//setCarrierForVoice(1, MIDI.noteNum[0] + 12);
	//voxTicker(1,MIDI.trigger[0]);
	
//	setCarrierForVoice(0, 70);
 // voxTicker(0, 1);
	
	float out = algTic();
	
	out = castOutput(out,&Mixer1);
	
	btnCount();
	
	return out;
	
	//Do other stuff from UIFeedback//
}


