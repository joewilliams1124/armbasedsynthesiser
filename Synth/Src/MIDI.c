#include "MIDI.h"
#include <stdbool.h>
#include "Envelope.h"
#include "control.h"
#include "VoxManager.h"


//PA3 is input!!!!

int rByte;
int byteNum = 0;
int n = 0;

MIDImessage MIDI;

void midiInit(){
	//MIDI.noteNum = 60;
  //MIDI.trigger = 1;
	//MIDI.velocity = 127;
	//MIDI.voxNumber = 0;
	//MIDI.program = 1;
}

void readMIDI(int rByte){
	if (rByte > 127){
		MIDI.status = rByte;
		byteNum = 0;
	} else {
		MIDI.dataByte[byteNum] = rByte;
		byteNum = !byteNum; //Flips from 0 to 1.
	}
}

void resetEnv(){
	if (MIDI.trigger[MIDI.voxNumber] == 0){ //voice is reset if last message was note off
		voxReset(MIDI.voxNumber);
	}
}

void processNote(void){
	
	if (MIDI.status == 0x90){ //Note On
				
			 //Reset the envelop of that voice so it can be used
			 resetEnv();
		
		if (MIDI.dataByte[1] == 0){
			
			// If there's 0 velocity then it's a note off
			// Set the trigger of the previous vox accordingly //
			MIDI.trigger[0] = 0;
			
			//MIDI.trigger[MIDI.voxNumber] = 0;
			
			//voxReset(!MIDI.voxNumber);
			
			//Change to the other voice
			
		}else{
		 	// A note on message is coming in//
		  // Therefore we need to switch voice//
		  //MIDI.voxNumber = !MIDI.voxNumber;
			
			//If this value isn't zero set it as the velocity
			
			//TODO change it so the velocity is ascocciate with the note//
			MIDI.velocity = MIDI.dataByte[1];
			
			//Control connect processes the velocity
			VelocityConnect();
			
		  //Extract the note number from the MIDI message
		  MIDI.noteNum[0] = MIDI.dataByte[0];
			
			//MIDI.noteNum[MIDI.voxNumber] = MIDI.dataByte[0];
			
			//Set the trigger on that voice to 1
			MIDI.trigger[0] = 1;

			//MIDI.trigger[MIDI.voxNumber] = 1;
		}
		
	}
}

void processControlChange(void){
	if (MIDI.status >= 0xB0 && MIDI.status <= 0xBF){
		MIDI.ccData[MIDI.dataByte[0]] = MIDI.dataByte[1];
		ControlCC();
		}
}

void processPitchBend(void){
	if (MIDI.status >= 0xE0 && MIDI.status <= 0xEF){
		MIDI.pitchBend = MIDI.dataByte[1] + MIDI.dataByte[0];
	}
}

void processProgramChange(void){
	if (MIDI.status >= 0xC0 && MIDI.status <= 0xCF){
		//TODO
		//MIDI.program = MIDI.dataByte[1];
		//byteNum = !byteNum;
		//BSP_LED_On(1);
		}
}
void readEnableUART2(){
	USART2->CR1 |= USART_CR1_RE; //YOU HAVE TO RUN IN HERE ELSE THE INTERRUPT MESSES UP
}

void USART2_IRQHandler(void){
	int rByte = PB_FTDI_Receive();
	readMIDI(rByte);
	processNote();
	processControlChange();
	processPitchBend();
	//processProgramChange();
}

void PB_FTDI_Init(){
  // Start trying to use USART2 (which is connected to the FTDI module via PA2).
  const unsigned int RCC_APB1RSTR = RCC_BASE + 0x20;     // Address of reset register
  const unsigned int USART2_BIT_IN_RCC = RCC_APB1RSTR_USART2RST_Pos; // USART2 on bit 17
  
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable the UART2 clock
  
  // First, reset the UART then bring it out of reset:
  *(unsigned int*)RCC_APB1RSTR |= 1UL << USART2_BIT_IN_RCC;
  *(unsigned int*)RCC_APB1RSTR &= ~(1UL << USART2_BIT_IN_RCC);
  
  // Set up the UART as a 9600 baud 
  USART2->BRR = 0x511;
  USART2->CR1 = (1UL << 13) | (1UL << 3);
  
  // Turn clock to GPIOA on, set-up PA2 as an output, and configure PA3 to take 
  // input from USART2 (note you have to turn the clock on before writing to 
  // the register):
	
  RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOAEN;         // Enable GPIOA clock  
  GPIOA->AFR[0] = (GPIOA->AFR[0] & 0xFFFFF0FF) | (0x7 << 8);
  unsigned int bit = 2;
  unsigned int bitMask = ~(3UL << 2*bit);
  GPIOA->MODER = (GPIOA->MODER & bitMask) | (2UL << 2*bit);  

  // Also set up PA3 as in AF mode, also with alternate function AF7:
  GPIOA->AFR[0] = (GPIOA->AFR[0] & 0xFFFF0FFF) | (0x7 << 12);
  bit = 3;
  bitMask = ~(3UL << 2*bit);
  GPIOA->MODER = (GPIOA->MODER & bitMask) | (2UL << 2*bit);
	
	USART2->CR1 |= USART_CR1_RXNEIE | USART_CR1_UE; //Enable RXNE interrupt
	
	NVIC_EnableIRQ(USART2_IRQn);
	
	midiInit();
	
}


int PB_FTDI_Receive() {
	// Returns the received character.  If there is no receive character in the 
	// receive buffer, it returns 1.
	USART2->CR1 |= USART_CR1_RE;
	int data = 0;
	if (USART2->SR & USART_SR_RXNE) data = USART2->DR;
	return data;
}
