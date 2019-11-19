/*
 * clock.h
 *
 *  Created on: 7/05/2019
 *      Author: bsl28
 */

#ifndef CLOCK_H_
#define CLOCK_H_


#include <stdbool.h>

#define SAMPLE_RATE_HZ 800
#define CLOCK_RATE 20000000



bool getFlag40Hz();
bool getFlag20Hz();
bool getFlag8Hz();
bool getFlag2Hz();

void setFlag40Hz(bool flag);
void setFlag20Hz(bool flag);
void setFlag8Hz(bool flag);
void setFlag2Hz(bool flag);


//*****************************************************************************
//
// The interrupt handler for the for SysTick interrupt.
//
//*****************************************************************************
void SysTickIntHandler(void);

//*****************************************************************************
// Initialisation functions for the clock
//*****************************************************************************
void initClock (void);

#endif /* CLOCK_H_ */
