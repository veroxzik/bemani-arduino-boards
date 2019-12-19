# bemani-arduino-boards
 A collection of Arduuino breakout boards and code for Bemani uses.

## Physical Settings on the Boards

Each board has a few physical solder jumpers that you must set before use.

### Setting the lights power source

Locate the jumper labeled CNR PWR | USB PWR. If you wish to power the lights off of USB power, jump the center pad and the USB PWR pad together.

If you wish to use the external power header, jump the center pad and the CNR PWR pad together. All external power headers are such that the square pin is positive.

On several boards, it is necessary to select whether you want to use encoders or buttons. Such option is used by soldering the *two* jumpers between either BUT or ENC.

On the Micro boards, if you use one encoder, it must be QE2. On the Pro Micro board, it must be QE1. (Or you can change my code if you don't like this restriction.)
 
 
## How to Flash Firmware

### Load the board profile

Move the folder `Additional Files\arduino-bemani` to your local hardware folder, most commonly located at `Documents\Arduino\hardware\`.
Your final path should look like `Documents\Arduino\hardware\arduino-bemani`.

Start the Arduino IDE / restart if it's already open.

This uses a copy of the Arduino 1.8.1 core, for reference. You should not have to update it.

### Loading the firmware

In the Arduino IDE, select the board using `Tools->Board->Bemani Controller (Micro/Pro Micro)` under the `VXZK Custom Boards` section.

In `Config.h`, set the following parameters per your board and setup.

```c
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
//#define USE_PROMICRO
//#define USE_MICRO
```

You must uncomment either the USE_PROMICRO or USE_MICRO define or the compiler will throw an error.
