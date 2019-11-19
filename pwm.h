/*
 * pwm.h
 *
 *  Created on: 13/05/2019
 *      Author: lbr63
 *
 *  Uses a modified version of pwnGen.h, by P.J. Bones UCECE
 *
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>
#include <stdbool.h>

#include "stdlib.h"
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


// PWM configuration
#define PWM_START_DUTY  0
#define PWM_RATE_MIN_DUTY    0
#define PWM_RATE_MAX_DUTY    100
#define PWM_FIXED_RATE_HZ     200
#define PWM_DIVIDER_CODE   SYSCTL_PWMDIV_4

//  PWM Hardware Details
#define PWM_MAIN_BASE        PWM0_BASE
#define PWM_MAIN_GEN         PWM_GEN_3
#define PWM_MAIN_OUTNUM      PWM_OUT_7
#define PWM_MAIN_OUTBIT      PWM_OUT_7_BIT
#define PWM_MAIN_PERIPH_PWM  SYSCTL_PERIPH_PWM0
#define PWM_MAIN_PERIPH_GPIO SYSCTL_PERIPH_GPIOC
#define PWM_MAIN_GPIO_BASE   GPIO_PORTC_BASE
#define PWM_MAIN_GPIO_CONFIG GPIO_PC5_M0PWM7
#define PWM_MAIN_GPIO_PIN    GPIO_PIN_5

#define PWM_SECONDARY_BASE        PWM1_BASE
#define PWM_SECONDARY_GEN         PWM_GEN_2
#define PWM_SECONDARY_OUTNUM      PWM_OUT_5
#define PWM_SECONDARY_OUTBIT      PWM_OUT_5_BIT
#define PWM_SECONDARY_PERIPH_PWM  SYSCTL_PERIPH_PWM1
#define PWM_SECONDARY_PERIPH_GPIO SYSCTL_PERIPH_GPIOF
#define PWM_SECONDARY_GPIO_BASE   GPIO_PORTF_BASE
#define PWM_SECONDARY_GPIO_CONFIG GPIO_PF1_M1PWM5
#define PWM_SECONDARY_GPIO_PIN    GPIO_PIN_1

#define MAIN_ROTOR 1
#define SECONDARY_ROTOR 2

//*****************************************************************************
// Initialisation functions for the PWM. Initialises module 0 and module 1.
// Using the constants defined in pwm.h
//*****************************************************************************
void
initialisePWM (void);

//*****************************************************************
//  Function to set the duty cycle of the main, or secondary rotor
// ****************************************************************
void
setDutyCycle (uint32_t ui32Duty, uint8_t rotor);


#endif /* PWM_H_ */
