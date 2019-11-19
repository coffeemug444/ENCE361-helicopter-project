/*
 * display.h
 * Handles the display of the helicopters status via UART and the OLED screen
 *
 *  Created on: 13/05/2019
 *      Author: lbr63
 */



#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

//*****************************************************************************
// Initialises the OLED screen and UART communication
//*****************************************************************************
void initialiseDisplay(void);

//*****************************************************************************
// Displays the current status of the helicopter on the OLED screen
// Displays a given altitude, yaw, main duty cycle, and secondary duty cycle
//*****************************************************************************
void
displayStatusOLED(uint16_t altitude, uint16_t yaw, uint16_t main_duty, uint16_t secondary_duty);

//*****************************************************************************
// Displays the current status of the helicopter via UART
// Displays the current altitude, desired altitude, yaw, desired yaw, main duty cycle, and secondary duty cycle
//*****************************************************************************
void
displayStatusUART(uint16_t altitude, uint16_t desired_altitude, uint16_t yaw, uint16_t desired_yaw, uint16_t main_duty, uint16_t secondary_duty);


#endif /* DISPLAY_H_ */
