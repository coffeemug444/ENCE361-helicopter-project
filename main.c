//*****************************************************************************
// Main file for the program to run from
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "utils/ustdlib.h"
#include "circBufT.h"
#include "uart.h"
#include "clock.h"
#include "input.h"
#include "display.h"
#include "pwm.h"
#include "input.h"
#include "height.h"
#include "yaw.h"
#include "helistates.h"
#include "rotors.h"


//*****************************************************************************
// Global variables
//*****************************************************************************
uint8_t heli_state = INIT;

//*****************************************************************************
// Check the status of all input devices (left, right, up, down buttons and switch 1)
// And update desired yaw, desired altitude, and current helicopter state appropriately
//*****************************************************************************
void
checkInputStatus (void)
{
    if (checkInput(LEFT) == PUSHED) {
        if (yaw.desired == 0)
            yaw.desired += 345;
        else yaw.desired -= 15;
    }

    if (checkInput(RIGHT) == PUSHED) {
        yaw.desired += 15;
        if (yaw.desired > 360) yaw.desired -= 360;
    }

    if (checkInput(UP) == PUSHED) {
        if (alt.desired != 100) {
            alt.desired += 10;
        }
    }

    if (checkInput(DOWN) == PUSHED) {
        if (alt.desired != 0) {
            alt.desired -= 10;
        }
    }
}

//*****************************************************************************
// Contains main loop of helicopter program.
// Initialises all nescecary functions, enables interupts, then begins looping
//*****************************************************************************
int
main(void)
 {
	
	initClock ();
	initADC ();
	initialiseDisplay ();
    initInput ();
    initYaw();
    initialisePWM ();
    setLandedRef();

    // Enable interrupts to the processor.
	IntMasterEnable();

	// Main program loop
	while (1)
	{
	    // Poll the buttons at 40hz
	    if (getFlag40Hz()) {
	        setFlag40Hz(false);
	        updateInput ();
	    }

	    if (yaw_flag){
	        yaw_flag = false;
	        update_yaw();
	    }

	    // Change the helicopter state when the switch is used
        if (checkInput(SW) == PUSHED)
        {
            switch (heli_state) {
            case INIT :     heli_state = STARTUP;
                            break;
            case LANDED :   yaw.error_integrated = 0;
                            alt.error_integrated = 0;
                            heli_state = FLYING;
                            break;
            case FLYING :   alt.desired = alt.actual - 10;
                            yaw.desired = 0;
                            heli_state = LANDING;
                            break;
            }
        }

        // Depending which state the helicopter is in, do something
        switch (heli_state) {
            case STARTUP :  if (atRef()) {
                                alt.desired = 0;
                                yaw.desired = 0;
                                yaw.error_integrated = 0;
                                heli_state = FLYING;
                            }
                            else if (getFlag20Hz()) {
                                setFlag20Hz(false);
                                if ((yaw.actual < yaw.desired + 6) && (yaw.actual > yaw.desired - 6)) {
                                    yaw.desired += 15;
                                    if (yaw.desired > 360)
                                        yaw.desired -= 360;
                                    yaw.error_integrated = 0;
                                }
                                doControl(20); //do control at 20Hz
                            }
                            break;
            case FLYING :   checkInputStatus();
                            if (getFlag20Hz()) {
                                setFlag20Hz(false);
                                doControl(20);
                            }
                            break;
            case LANDING :  if ((alt.actual < 8) && (yaw.actual < 5 || yaw.actual > 355)) {   //height less than 8% and yaw within 5 degrees of ref
                                alt.error_integrated = 0;
                                yaw.error_integrated = 0;
                                alt.desired = 0;
                                heli_state = LANDED;
                            }
                            else if (getFlag20Hz()) {
                                setFlag20Hz(false);
                                if (yaw.actual > 355 || yaw.actual < 5) {
                                    alt.desired = 0;
                                }
                                doControl(20);  //do control at 20Hz
                            }
                            break;
        }

        // Display the helicopters status on the OLED screen at 2hz
		if (getFlag2Hz()) {
		    setFlag2Hz(false);
		    displayStatusOLED(alt.actual, yaw.actual, main_duty, secondary_duty);
		}

        // Display the helicopters status through serial communication at 8hz
        if (getFlag8Hz()) {
            setFlag8Hz(false);
		    displayStatusUART(alt.actual, alt.desired, yaw.actual, yaw.desired, main_duty, secondary_duty);
		}
	}
}

