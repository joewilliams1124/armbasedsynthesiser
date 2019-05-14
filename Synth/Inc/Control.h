#ifndef __CONTROL_H
#define __CONTROL_H

#include "envelope.h"
#include "Operator.h"
#include "noteTable.h"
#include "Buttons.h"
#include "Envelope.h"
#include "OutputMixer.h"
#include "MIDI.h"

void VelocityConnect(void);

void ControlCC(void);

float scale127(int MIDIvalue, float max);

void btnCount(void);

#endif
