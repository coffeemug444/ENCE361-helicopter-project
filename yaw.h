/*
 * yaw.h
 *
 *  Created on: 14/05/2019
 *      Author: bsl28
 */

#ifndef YAW_H_
#define YAW_H_

//*****************************************************************************
// Handler for yaw interupt, sets the yaw flag
//*****************************************************************************
void
yawIntHandler(void);

//********************************************************
// initialise yaw functions, using constants defined in yaw.h.
//********************************************************
void
initYaw(void);

//********************************************************
// Update the current yaw values,
// also adjusts them appropriately within our tolerances
//********************************************************
void
update_yaw();

//********************************************************
// returns the current yaw
// which is  correctly scaled between -180 to 180 degrees
//********************************************************
uint16_t
getYaw();

//********************************************************
// returns the a boolean of if the helicopter is at its reference yaw point
//********************************************************
bool
atRef();


extern volatile bool yaw_flag;

#endif /* YAW_H_ */
