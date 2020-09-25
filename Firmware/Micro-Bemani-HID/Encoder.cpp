#include "Encoder.h"

Encoder::Encoder(uint16_t maxRange, uint8_t pinA, uint8_t pinB)
{
  position = 0;
  range = maxRange;
  pins[0] = pinA;
  pins[1] = pinB;
  pinMode(pins[0], INPUT_PULLUP);
  pinMode(pins[1], INPUT_PULLUP);
}

void Encoder::updateState()
{
  state = GET_ENCODER(pins[0], pins[1]);
}

bool Encoder::updateEncoder()
{
  bool dir = false;
  uint8_t newState = GET_ENCODER(pins[0], pins[1]);
  int16_t tempPosition = position;
  uint8_t tempState = state | (newState << 2);
  state = newState;
  switch (tempState) {
    case 1: case 7: case 8: case 14:
      position++;
      delta++;
      dir = true;
      break;
    case 2: case 4: case 11: case 13:
      position--;
      delta--;
      dir = false;
      break;
    case 3: case 12:
      position += 2;
      delta += 2;
      dir = true;
      break;
    case 6: case 9:
      position -= 2;
      delta -= 2;
      dir = false;
      break;
  }
  if (position < -(int16_t)range / 2)
    position += (int16_t)range;
  else if (position > (int16_t)range / 2)
    position -= (int16_t)range;

  return dir;
}

int16_t Encoder::getDelta()
{
  int16_t tempDelta = delta;
  delta = 0;
  return tempDelta;
}
