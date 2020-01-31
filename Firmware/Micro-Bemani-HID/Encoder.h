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
    int16_t position;
    uint8_t state;
    uint8_t pins[2];
    uint16_t range;

  public:
    Encoder(uint16_t maxRange, uint8_t pinA, uint8_t pinB);
    int16_t getPosition() { return position; };
    void updateState();
    void updateEncoder();
};

#endif