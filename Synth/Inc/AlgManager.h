#ifndef __ALGMANAGER_H
#define __ALGMANAGER_H

#include "config.h"
#include "noteTable.h"

void opConnect(void);

void opInit(int n); 


typedef struct
{
	int preset;
	int alg;
	int voxNum;
	float carrier;
	int noOfCarriers;
} algSound;

void algsConnect(void);

float algTic(void);

#endif
