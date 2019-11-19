/*
 * yaw.c
 *
 *  Created on: 14/05/2019
 *      Author: bsl28
 */


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
#include "yaw.h"



static bool yaw_A_state = false;
static bool yaw_B_state = false;
static bool ref_state = false;
static int16_t yaw = 0;         //helicopter yaw scaled by 10x
volatile bool yaw_flag = false;

//*****************************************************************************
// Handler for yaw interupt, sets the yaw flag
//*****************************************************************************
void
yawIntHandler(void)
{
    yaw_flag = true;
    GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
}

//********************************************************
// initialise yaw functions, using constants defined in yaw.h.
//********************************************************
void
initYaw(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }

    GPIOIntRegister(GPIO_PORTB_BASE, yawIntHandler);

    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 );

    GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_DIR_MODE_IN);
    GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_BOTH_EDGES);
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
    {
    }

    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIODirModeSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
}

//********************************************************
// Update the current yaw values,
// also adjusts them appropriately within our tolerances
//********************************************************
void
update_yaw()
{
    bool new_A = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0);
    bool new_B = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_1);
    bool new_C = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4);

    if (!new_C) {
        yaw = 0;
    }
    else {
        if(!yaw_A_state && !yaw_B_state)
        {
            if (!new_A && new_B)    //  clockwise
                yaw += 8;
            else                    // anticlockwise
                yaw -= 8;
        }

        if(!yaw_A_state && yaw_B_state)
        {
            if (new_A && new_B)    //  clockwise
                yaw += 8;
            else                    // anticlockwise
                yaw -= 8;
        }

        if(yaw_A_state && yaw_B_state)
        {
            if (new_A && !new_B)    //  clockwise
                yaw += 8;
            else                    // anticlockwise
                yaw -= 8;
        }

        if(yaw_A_state && !yaw_B_state)
        {
            if (!new_A && !new_B)    //  clockwise
                yaw += 8;
            else                    // anticlockwise
                yaw -= 8;
        }



        if (yaw > 3600)
            yaw -= 3600;
        else if (yaw < 0)
            yaw += 3600;
    }

    yaw_A_state = new_A;
    yaw_B_state = new_B;
    ref_state = !new_C;
}

//********************************************************
// returns the current yaw
// which is  correctly scaled between -180 to 180 degrees
//********************************************************
uint16_t getYaw()
{
    return (2 * yaw + 10) / 2 / 10;
}

//********************************************************
// returns the a boolean of if the helicopter is at its reference yaw point
//********************************************************
bool atRef()
{
    return ref_state;
}
