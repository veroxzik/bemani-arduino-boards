#ifndef __UTIL_H__
#define __UTIL_H__

uint8_t countBits(uint16_t input)
{
  uint8_t count;
  for (int i = 0; i < 16; i++)
  {
    if ((input >> i) & 0x1 == 1)
      count++;
  }

  return count;
}

bool isEven(uint8_t input)
{
  return input % 2 == 0 ? true : false;
}

#endif // __UTIL_H__
