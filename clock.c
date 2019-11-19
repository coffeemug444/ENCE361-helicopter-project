#include "clock.h"
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

uint32_t counter = 0;
volatile bool flag_40_hz;
volatile bool flag_20_hz;
volatile bool flag_8_hz;
volatile bool flag_2_hz;

//*****************************************************************************
// The interrupt handler for the for SysTick interrupt.
//*****************************************************************************
void
SysTickIntHandler(void)
{
    counter++;
    if (counter % (SAMPLE_RATE_HZ / 2) == 0){
        flag_2_hz = true;
        if (counter % (SAMPLE_RATE_HZ / 8) == 0)
            flag_8_hz = true;
        if (counter % (SAMPLE_RATE_HZ / 20) == 0) {
            flag_20_hz = true;
            if (counter % (SAMPLE_RATE_HZ / 40) == 0)
                flag_40_hz = true;
        }
        counter = 0;
    }



    //
    // Initiate a conversion
    //
    ADCProcessorTrigger(ADC0_BASE, 3);
}

bool getFlag40Hz()
{
    return flag_40_hz;
}

bool getFlag20Hz()
{
    return flag_20_hz;
}

bool getFlag8Hz()
{
    return flag_8_hz;
}

bool getFlag2Hz()
{
    return flag_2_hz;
}

void setFlag40Hz(bool flag)
{
    flag_40_hz = flag;
}

void setFlag20Hz(bool flag)
{
    flag_20_hz = flag;
}

void setFlag8Hz(bool flag)
{
    flag_8_hz = flag;
}

void setFlag2Hz(bool flag)
{
    flag_2_hz = flag;
}


//*****************************************************************************
// Initialisation functions for the clock
//*****************************************************************************
void
initClock (void)
{
    // Set the clock rate to 20 MHz
    SysCtlClockSet (SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
    //
    // Set up the period for the SysTick timer.  The SysTick timer period is
    // set as a function of the system clock.
    SysTickPeriodSet(SysCtlClockGet() / SAMPLE_RATE_HZ);
    //
    // Register the interrupt handler
    SysTickIntRegister(SysTickIntHandler);
    //
    // Enable interrupt and device
    SysTickIntEnable();
    SysTickEnable();
}
