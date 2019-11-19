/*
 * height.h
 *
 *  Created on: 7/05/2019
 *      Author: bsl28
 */

#ifndef HEIGHT_H_
#define HEIGHT_H_

#define BUF_SIZE 100

//*****************************************************************************
// The handler for the ADC conversion complete interrupt.
// Writes to the circular buffer.
//*****************************************************************************
void ADCIntHandler(void);

//*****************************************************************************
// Initialisation functions for the ADC
//*****************************************************************************
void initADC (void);

//*****************************************************************************
// Calculate and return the rounded mean of the buffer contents
//*****************************************************************************
uint16_t
calculateMeanHeight(void);

//*****************************************************************************
// Set the landed reference of the helicopter.
// Uses the rounded mean of the circular buffer contents
//*****************************************************************************
void
setLandedRef(void);


#endif /* HEIGHT_H_ */
