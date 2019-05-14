#ifndef __MIDI_H
#define __MIDI_H

#include "..\Drivers\Audio\stm32f4_discovery.h"
#include "LED.h"
#include "PB_LCD_Drivers.h"
#include "math.h"
#include "stm32f4xx.h"
#include "Envelope.h"
#include "config.h"

typedef struct {
	int status;
	int dataByte[2];
	int velocity;
	int ccData[127];
	int program;
	int voxNumber;
	int noteNum[2];
	int trigger[2];
	int pitchBend;
}MIDImessage;

int PB_FTDI_Receive(void);
void PB_FTDI_Init(void);
void PB_FTDI_Send(char *bytes, int howMany);
void PB_FTDI_SendNewLine(void);
void readEnableUART2(void);
void USART2_IRQHandler(void);
int getNote(void);
int getVelocity(void);
int getTrigger(void);
void readMIDI(int rByte);
void resetEnv(void);
void processControlChange(void);
//int getVox(void);

#endif
