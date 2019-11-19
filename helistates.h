/*
 * helistates.h
 *
 * Contains all states that the helicopter can be in as enums.
 * Default state INIT
 *
 *  Created on: 16/05/2019
 *      Author: bsl28
 */

#ifndef HELISTATES_H_
#define HELISTATES_H_

// Helicopter states
enum heli_states {INIT = 0, STARTUP, LANDED, LANDING, FLYING};


extern uint8_t heli_state;

#endif /* HELISTATES_H_ */
