#ifndef __CONFIG_H__
#define __CONFIG_H__

/* --- --- --- --- --- --- ---
   Frequently Changed Settings
   --- --- --- --- --- --- --- */

// This is the number of encoders you are using.
// If it is 1 and you are using a Micro board, then you must use QE2.
// If it is 1 and you are using a Pro Micro board, then you must use QE1
#define NUM_ENCODERS 0

// This is the PPR of your encoder
// Common values are 600 for Chinese encoders and 24 for Bourns encoders
const uint16_t pulseCount = 24;

// Uncomment the corresponding define for the microcontroller you are using
//#define USE_MICRO
//#define USE_PROMICRO



/* --- --- --- --- --- --- --- ---
   Less Frequenly Changed Settings
   --- --- --- --- --- --- --- --- */

#if NUM_ENCODERS > 2
#error "More than 2 encoder cannot be defined"
#endif

#if defined(USE_MICRO)

// Pins for the buttons
// If using the breakout boards, these aleady in the correct order to correspond with B1-B12.
uint8_t numButtons = (12 - NUM_ENCODERS);
uint8_t buttonPins[] = {12, 10, 8, 6, 4, SS, 13, A2, A4, MISO, 1, 2};
uint8_t ledPins[] = {11, 9, 7, 5, MOSI, A0, A1, A3, A5, SCK, 0, 3};

// Pins for the Encoders
// QE1 is pins 0 and 1
// QE2 is pins 2 and 3
// These cannot be changed, as they are linked to interrupt pins.
uint8_t encoderPins[] = {2, 3, 0, 1};
#define NUM_SINGLE_LED (12 - NUM_ENCODERS)

#elif defined(USE_PROMICRO)
// Pins for the buttons
// If using the breakout boards, these aleady in the correct order to correspond with B1-B9.
uint8_t numButtons = (9 - NUM_ENCODERS);
uint8_t buttonPins[] = {20, 18, 14, 10, 5, 7, 9, 2, 1};
uint8_t ledPins[] = {21, 19, 15, 16, 4, 6, 8, 3, 0};
#define NUM_SINGLE_LED (9 - NUM_ENCODERS)

// Pins for the Encoders
// QE1 is pins 0 and 1
// QE2 is pins 2 and 3
// These cannot be changed, as they are linked to interrupt pins.
uint8_t encoderPins[] = {0, 1, 2, 3};

#else
#error "Board Not Defined in Confing.h"
#endif

// This board does not support RGB
#define NUM_RGB_LED 0

#endif