/*
===============================================================================
 Name        : hello_world_firmware.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "chip.h"
#include <cr_section_macros.h>

#define STEAM_BUTTON_PORT	1
#define STEAM_BUTTON_PIN	19
#define STEAM_LED_PORT		0
#define STEAM_LED_PIN		21

int main(void) {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();

    // Initialize GPIO
    Chip_GPIO_Init(LPC_GPIO);

    // Initialize steam button
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, STEAM_BUTTON_PORT, STEAM_BUTTON_PIN);

    // Initialize steam led
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, STEAM_LED_PORT, STEAM_LED_PIN);
    Chip_GPIO_SetPinState(LPC_GPIO, STEAM_LED_PORT, STEAM_LED_PIN, false);

    // State of steam button on previous iteration
    bool lastState = true;

    while(1) {
    	// Get state of steam button
    	bool buttonState = Chip_GPIO_GetPinState(LPC_GPIO, STEAM_BUTTON_PORT, STEAM_BUTTON_PIN);
    	// If state has been changed
    	if((lastState ^ buttonState) != 0) {
    		lastState = buttonState;
    		// If btton pressed
    		if(!buttonState) {
    			// Toggle steam led
    			Chip_GPIO_SetPinToggle(LPC_GPIO, STEAM_LED_PORT, STEAM_LED_PIN);
    		}
    	}
    }
    return 0 ;
}
