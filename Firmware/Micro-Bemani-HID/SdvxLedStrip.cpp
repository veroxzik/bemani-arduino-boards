#include "SdvxLedStrip.h"

void SdvxLedStrip::setRightLedCenter(int index) {
  burstPosR = index;
  int sideWidth = BURST_WIDTH / 2;
  if (burstPosR >= 0 && burstPosR < SDVX_NUM_LEDS)
  {
    for (int i = burstPosR - sideWidth; i <= burstPosR + sideWidth; i++)
    {
      float sat = abs(burstPosR - i) / (float)(sideWidth + 1);
      if (i >= 0 && i < SDVX_NUM_LEDS)
#ifdef SDVX_TCLED
        setRightLed(i, (1.0f - sat));
#else
        leds[i] = CHSV(160, 255, 255 * (1.0f - sat));
#endif
    }
  }
}

void SdvxLedStrip::setLeftLedCenter(int index) {
  burstPosL = index;
  int sideWidth = BURST_WIDTH / 2;
  if (burstPosL >= 0 && burstPosL < SDVX_NUM_LEDS)
  {
    for (int i = burstPosL - sideWidth; i <= burstPosL + sideWidth; i++)
    {
      float sat = abs(burstPosL - i) / (float)(sideWidth + 1);
      if (i >= 0 && i < SDVX_NUM_LEDS)
#ifdef SDVX_TCLED
        setLeftLed(i, (1.0f - sat));
#else
        leds[i] = CHSV(160, 255, 255 * (1.0f - sat));
#endif
    }
  }
}

void SdvxLedStrip::setLeftActive(bool dir) {
  leftDirPos = dir;
  leftScroll = true;
  if (burstPosL >= SDVX_NUM_LEDS)
    burstPosL = 0;
  else if (burstPosL < 0)
    burstPosL = SDVX_NUM_LEDS - 1;
}

void SdvxLedStrip::setRightActive(bool dir) {
  rightDirPos = dir;
  rightScroll = true;
  if (burstPosR >= SDVX_NUM_LEDS)
    burstPosR = 0;
  else if (burstPosR < 0)
    burstPosR = SDVX_NUM_LEDS - 1;
}

void SdvxLedStrip::update() {

#ifdef SDVX_TCLED

  // Clear the lights
  mbi->clearAll();

  // Update values
  setLeftLedCenter(burstPosL);
  setRightLedCenter(burstPosR);

  // Draw the lights
  mbi->sendData();
#endif

  // Update the scroll info
  if (leftScroll || rightScroll)
  {
    long curMillis = millis();
    if ((curMillis - lastMillis) > SCROLL_SPEED)
    {
      if (leftScroll)
      {
        if (leftDirPos)
          burstPosL++;
        else
          burstPosL--;

        if (burstPosL < 0 || burstPosL >= SDVX_NUM_LEDS)
          leftScroll = false;
      }
      if (rightScroll)
      {
        if (rightDirPos)
          burstPosR++;
        else
          burstPosR--;

        if (burstPosR < 0 || burstPosR >= SDVX_NUM_LEDS)
          rightScroll = false;
      }
      lastMillis = curMillis;
    }
  }
}

void SdvxLedStrip::setRightLed(int index, float brightness) {
#ifdef SDVX_TCLED
  rightBrightness[index] = (uint16_t)(16384.0f * brightness);
  mbi->setLed(pinMapRight[index], rightBrightness[index]);
#endif
}

void SdvxLedStrip::setLeftLed(int index, float brightness) {
#ifdef SDVX_TCLED
  leftBrightness[index] = (uint16_t)(16384.0f * brightness);
  mbi->setLed(pinMapLeft[index], leftBrightness[index]);
#endif
}
