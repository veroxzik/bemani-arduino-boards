/* --- --- --- --- --- --- --- --- --- --- --- ---
    Micro / Pro Micro Bemani Code
   --- --- --- --- --- --- --- --- --- --- --- ---
   Code written for use with:
   https://github.com/veroxzik/bemani-arduino-boards

   Refer to Config.h for user-settable variables

   Licensed under GNU GPL v3.0

   --- --- --- --- --- --- --- --- --- --- --- --- */

#include <Joystick.h>
#include "Config.h"
#include "Encoder.h"


// Encoders
extern uint8_t encoderPins[];
extern const uint16_t pulseCount;

Encoder *encoders[] = {
#if NUM_ENCODERS > 0
  new Encoder(pulseCount, encoderPins[0], encoderPins[1]),
#if NUM_ENCODERS > 1
  new Encoder(pulseCount, encoderPins[2], encoderPins[3])
#endif
#endif
};

// Buttons
extern uint8_t buttonPins[];
extern uint8_t numButtons;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, numButtons, 0,
                   true, true, false, false, false, false, false, false, false, false, false);

#include "HIDLED.h"

// Lights
bool lightStatus[NUM_SINGLE_LED];



void setup()
{
  Serial.begin(115200);

  // Setup Joystick
  Joystick.setXAxisRange(-(int16_t)pulseCount / 2, (int16_t)pulseCount / 2);
  Joystick.setYAxisRange(-(int16_t)pulseCount / 2, (int16_t)pulseCount / 2);
  Joystick.begin(false);
  Joystick.setXAxis(0);
  Joystick.setYAxis(0);

  // Setup Encoders
#if NUM_ENCODERS > 0
  encoders[0]->updateState();
#if NUM_ENCODERS > 1
  encoders[1]->updateState();
#endif
#endif

  // It's not possible to attach interrupts (well) inside classes, unfortunately
#if NUM_ENCODERS > 0
  attachInterrupt(digitalPinToInterrupt(encoderPins[0]), processEncoder0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPins[1]), processEncoder0, CHANGE);
#if NUM_ENCODERS > 1
  attachInterrupt(digitalPinToInterrupt(encoderPins[2]), processEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPins[3]), processEncoder1, CHANGE);
#endif
#endif

  // Setup Buttons
  for (int i = 0; i < numButtons; i++)
    pinMode(buttonPins[i], INPUT_PULLUP);

  // Setup Lights
  for (int i = 0; i < NUM_SINGLE_LED; i++)
    pinMode(ledPins[i], OUTPUT);
}

void loop()
{
  // Read / set buttons
  for (int i = 0; i < numButtons; i++)
  {
    uint8_t buttonState = digitalRead(buttonPins[i]);
    if (buttonState)
      Joystick.releaseButton(i);
    else
      Joystick.pressButton(i);
  }

  // Write analog values
#if NUM_ENCODERS > 0
#if NUM_ENCODERS > 1
  Joystick.setXAxis(encoders[0]->getPosition());
#endif
  Joystick.setYAxis(encoders[1]->getPosition());
#endif

  Joystick.sendState();

  // Set lights
  for (int i = 0; i < NUM_SINGLE_LED; i++)
    digitalWrite(ledPins[i], lightStatus[i]);
}

void processEncoder0()
{
  encoders[0]->updateEncoder();
}

void processEncoder1()
{
  encoders[1]->updateEncoder();
}

void light_update(SingleLED* single_leds, RGBLed* rgb_leds)
{
  for (int i = 0; i < NUM_SINGLE_LED; i++) {
    lightStatus[i] = single_leds[i].brightness > 0 ? true : false;
  }
  //  for (int i = 0; i < NUM_RGB_LED; i++) {
  //    // Do nothing
  //  }
}