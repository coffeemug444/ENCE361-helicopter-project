/*
 * control.h
 *
 * Handles the PID control for the program
 *
 *  Created on: 14/05/2019
 *      Author: bsl28
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include <stdint.h>

typedef struct controller {
    int32_t desired;
    int32_t actual;
    uint16_t Kp;
    uint16_t Ki;
    uint16_t Kd;
    int32_t error_integrated;
    int32_t error_previous;
} controller;

//*****************************************************************************
// Handles Proportional control
//*****************************************************************************
int32_t
proportional (controller *controlled);

//*****************************************************************************
// Handles Integral control
//*****************************************************************************
int32_t
integral (controller *controlled, uint16_t frequency);

//*****************************************************************************
// Handles Derivative control
//*****************************************************************************
int32_t
derivative (controller *controlled, uint16_t frequency);

//*****************************************************************************
// Main PID function, returns the PID value after using proportional, integral and derivative control
//*****************************************************************************
int32_t
PID (controller *controlled, uint16_t frequency);

#endif /* CONTROL_H_ */
