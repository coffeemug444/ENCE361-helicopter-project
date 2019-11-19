/*
 * rotors.c
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
#include "pwm.h"
#include "height.h"
#include "yaw.h"
#include "rotors.h"
#include "helistates.h"


controller alt = {0,0,KP_M,KI_M,KD_M,0,0};
controller yaw = {0,0,KP_Y,KI_Y,KD_Y,0,0};

int32_t main_duty = 0;
int32_t secondary_duty = 0;

//*****************************************************************************
// Handles control of main and secondary rotors. Calls the PID functions in Control.c
//*****************************************************************************
void
doControl(uint16_t frequency)
{
    yaw.actual = getYaw();
    if (yaw.desired - yaw.actual > 180)
        yaw.desired -= 360;
    if (yaw.desired - yaw.actual < -180)
        yaw.desired += 360;

    alt.actual = calculateMeanHeight();

    main_duty = PID(&alt, frequency) / SCALE;
    secondary_duty = PID(&yaw, frequency) / SCALE;

    if (main_duty > 80) main_duty = 80;
    if (main_duty < 20) main_duty = 20;

    if (secondary_duty > 80) secondary_duty = 80;
    if (secondary_duty < 0) secondary_duty = 0;

    if (heli_state ==  LANDING && alt.actual < 5) {
        secondary_duty = 0;
        main_duty = 0;
        heli_state = LANDED;
    }

    setDutyCycle(main_duty, MAIN_ROTOR);
    setDutyCycle(secondary_duty, SECONDARY_ROTOR);
}
