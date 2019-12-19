#include "Encoder.h"

Encoder::Encoder(uint8_t maxRange, uint8_t pinA, uint8_t pinB)
{
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

void Encoder::updateEncoder()
{
  uint8_t newState = GET_ENCODER(pins[0], pins[1]);
  int8_t tempPosition = position;
  uint8_t state = state | (newState << 2);
  state = newState;
  switch (state) {
    case 1: case 7: case 8: case 14:
      position++;
      break;
    case 2: case 4: case 11: case 13:
      position--;
      break;
    case 3: case 12:
      position += 2;
      break;
    case 6: case 9:
      position -= 2;
      break;
  }
  if (position < -range / 2)
    position += range;
  else if (position > range / 2)
    position -= range;
}
