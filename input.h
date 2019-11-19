#ifndef INPUT_H_
#define INPUT_H_

// *******************************************************
// input.h
//
// Support for a set of 5 specific buttons on the Tiva/Orbit.
// The buttons are:  UP and DOWN (on the Orbit daughterboard) plus
// LEFT and RIGHT on the Tiva, and SW1 on the boosterpack
//
// Uses a modified version of buttons.h, by P.J. Bones UCECE
// 
// *******************************************************

#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
// Constants
//*****************************************************************************
enum butNames {UP = 0, DOWN, LEFT, RIGHT, SW, NUM_BUTS};
enum butStates {RELEASED = 0, PUSHED, NO_CHANGE};
// UP button
#define UP_BUT_PERIPH  SYSCTL_PERIPH_GPIOE
#define UP_BUT_PORT_BASE  GPIO_PORTE_BASE
#define UP_BUT_PIN  GPIO_PIN_0
#define UP_BUT_NORMAL  false
// DOWN button
#define DOWN_BUT_PERIPH  SYSCTL_PERIPH_GPIOD
#define DOWN_BUT_PORT_BASE  GPIO_PORTD_BASE
#define DOWN_BUT_PIN  GPIO_PIN_2
#define DOWN_BUT_NORMAL  false
// LEFT button
#define LEFT_BUT_PERIPH  SYSCTL_PERIPH_GPIOF
#define LEFT_BUT_PORT_BASE  GPIO_PORTF_BASE
#define LEFT_BUT_PIN  GPIO_PIN_4
#define LEFT_BUT_NORMAL  true
// RIGHT button
#define RIGHT_BUT_PERIPH  SYSCTL_PERIPH_GPIOF
#define RIGHT_BUT_PORT_BASE  GPIO_PORTF_BASE
#define RIGHT_BUT_PIN  GPIO_PIN_0
#define RIGHT_BUT_NORMAL  true
// SWITCH
#define SW_PERIPH  SYSCTL_PERIPH_GPIOA
#define SW_PORT_BASE  GPIO_PORTA_BASE
#define SW_PIN  GPIO_PIN_7
#define SW_NORMAL  false

#define NUM_BUT_POLLS 3


void
ResetIntHandler(void);

// *******************************************************
// Initialise functions for input, so buttons can be used
// defined by the constants in the input.h header file.
//*****************************************************************************
void
initInput (void);

// *******************************************************
// Polls all buttons once and updates variables associated with the buttons if
// necessary.  It is efficient enough to be part of an ISR, e.g. from
// a SysTick interrupt.
// Contains a debounce algorithm: A state machine is associated with each button.
//*****************************************************************************
void
updateInput (void);

// *******************************************************
// checkButton: Function returns the new button logical state if the button
// logical state (PUSHED or RELEASED) has changed since the last call,
// otherwise returns NO_CHANGE.
//*****************************************************************************
uint8_t
checkInput (uint8_t butName);

#endif /*INPUT_H_*/
