// This code adapted from mon's Pocket Voltex, which was adapted from Encoder.h by PRJC
// https://github.com/mon/PocketVoltex

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "Encoder.h"
#include <Arduino.h>

#define GET_ENCODER(pinA, pinB) (digitalRead(pinA) | (digitalRead(pinB) << 1))

class Encoder
{
  private:
    int8_t position;
    uint8_t state;
    uint8_t pins[2];
    uint8_t range;

  public:
    Encoder(uint8_t maxRange, uint8_t pinA, uint8_t pinB);
    int8_t getPosition() { return position; };
    void updateState();
    void updateEncoder();
};

#endif
