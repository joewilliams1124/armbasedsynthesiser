#ifndef __VOXMANAGER_H
#define __VOXMANAGER_H

#include "config.h"
#include "noteTable.h"

void voxReset(int n);

void voxTicker(int n, int trigger);

void setCarrierForVoice(int voxNumber, int note);

void linkVoxParamaters(void);

#endif
