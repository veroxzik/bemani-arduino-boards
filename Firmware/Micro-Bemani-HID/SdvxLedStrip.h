#ifndef __SDVXLEDSTRIP_H__
#define __SDVXLEDSTRIP_H__

#include <Arduino.h>
#include "Config.h"

// This is the number of LEDs across (not counting TC's double stacked LEDs)
#ifdef SDVX_TCLED
#include "MBI6024.h"
#define SDVX_NUM_LEDS 24
#else
//#error "Other interfaces are not supported at this time."
#include <FastLED.h>
#define SDVX_NUM_LEDS 10
#endif

#define BURST_WIDTH 7
#define SCROLL_SPEED  20

class SdvxLedStrip {

  public:
    SdvxLedStrip() {
#ifdef SDVX_TCLED
      mbi = new MBI6024_(4);
#endif
    }

    void setRightLedCenter(int index);
    void setLeftLedCenter(int index);

    void setLeftActive(bool dir);
    void setRightActive(bool dir);

    void update();

  private:
#ifdef SDVX_TCLED
    MBI6024_* mbi;
#endif
    int burstPosL = -1, burstPosR = -1;
    bool leftDirPos = true, rightDirPos = false;
    bool leftScroll = false, rightScroll = false;
    long lastMillis = 0;

    void setRightLed(int index, float brightness);
    void setLeftLed(int index, float brightness);

#ifdef SDVX_TCLED
    uint16_t leftBrightness[SDVX_NUM_LEDS];
    uint16_t rightBrightness[SDVX_NUM_LEDS];
    uint8_t pinMapLeft[SDVX_NUM_LEDS]  = {23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47};
    uint8_t pinMapRight[SDVX_NUM_LEDS] = {22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46};
#else
    CRGB leds[SDVX_NUM_LEDS];
#endif

};

#endif // __SDVXLED_STRIP_H__
