#include "LED.h"

void LED_Dance(void){
	for (int a = 0; a < 4; a++){
		for (int i = 0; i < 4; i++){
				BSP_LED_On(i);
				HAL_Delay(50);
				BSP_LED_Off(i);
			}
		}
}

//MAKE SOMETHING FOR DISPLAYING VALUES IN BINARY ON LIGHTS//
