#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>

/* --- --- --- --- --- --- ---
   Frequently Changed Settings
   --- --- --- --- --- --- --- */

// This is the number of encoders you are using.
// If it is 1 and you are using a Micro board, then you must use QE2.
// If it is 1 and you are using a Pro Micro board, then you must use QE1.
#define NUM_ENCODERS 0

// This is the PPR of your encoder
// Common values are 600 for Chinese encoders and 24 for Bourns encoders
const uint16_t pulseCount = 24;

// Input mode
// Uncomment INPUT_KEYBOARDMOUSE to use keyboard buttons as defined below and Mouse X-Y axes for analog.
// Uncomment INPUT_JOYSTICK for Joystick buttons and X-Y axes for analog.
//#define INPUT_KEYBOARDMOUSE
//#define INPUT_JOYSTICK

// If using Keyboard mode, this array reports back the keys corresponding to buttons 1-12
const char buttonKeys[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' , 'j' , 'k', 'l'};

// If using Mouse Mode, set this number higher to increase the multiplier that is applied per turn.
#define MOUSE_MULTIPLIER 1

// Light Mode
// Uncomment this line for HID lights, leave commented for reactive lights
//#define HID_LIGHTS

// Uncomment the corresponding define for the board you are using
//#define USE_MICRO
//#define USE_MICRORGB
//#define USE_MICRORGB_V1_2
//#define USE_PROMICRO

// Uncomment your RGB LED interface for the SDVX LED strip
//#define SDVX_TCLED
//#define SDVX_WS2812B
//#define SDVX_APA102

// More SDVX LED strip options
// If the colors are swapped, set this to true
#define SDVX_REVERSE_KNOB true
// If the left knob lights scroll in the wrong direction, set this to true
#define SDVX_DIRECTION_LEFT false
// If the right knob lights scroll in the wrong direction, set this to true
#define SDVX_DIRECTION_RIGHT true



/* --- --- --- --- --- --- --- ---
   Error Messages! Do not modify
   --- --- --- --- --- --- --- --- */

#if NUM_ENCODERS > 2
#error "More than 2 encoder cannot be defined"
#endif

#if defined(USE_MICRO) + defined(USE_MICRORGB) + defined(USE_MICRORGB_V1_2) + defined(USE_PROMICRO) != 1
#error "Exactly one board must be defined."
#endif

#if defined(USE_MICRORGB) || defined(USE_MICRORGB_V1_2)
#define RGB_BOARD
#endif

#if defined(INPUT_KEYBOARDMOUSE) + defined(INPUT_JOYSTICK) != 1
#error "Must select either Keyboard+Mouse or Joystick mode (but not both)"
#endif

#if (!defined(RGB_BOARD) && (defined(SDVX_TCLED) || defined(SDVX_WS2812B) || defined(SDVX_APA102)))
#error "Cannot use a SDVX led strip on a non RGB board."
#endif

#if defined(SDVX_TCLED) + defined(SDVX_WS2812B) + defined(SDVX_APA102) > 1
#error "Cannot define multiple SDVX LED strip interfaces."
#elif (defined(SDVX_TCLED) || defined(SDVX_WS2812B) || defined(SDVX_APA102))
#define USE_SDVX_LED_STRIP
#endif

// This board does not support RGB
#define NUM_RGB_LED 0

#endif
