#ifndef __MBI6024_H__
#define __MBI6024_H__

#include <SPI.h>

class MBI6024_ {

  public:
    MBI6024_(int _num);

    void getHeader() {
      Serial.println(headerArray[0]); Serial.println(headerArray[1]); Serial.println(headerArray[2]);
    }

    void getDataHeader() {
      Serial.println(dataHeader[0]); Serial.println(dataHeader[1]); Serial.println(dataHeader[2]);
    }

    void setLed(uint16_t index, uint16_t grayscaleVal);
    void clearAll();
    void sendData();

    int getNumChips() {
      return numChips;
    }
    
    int getNumLeds() {
      return numLeds;
    }

  private:
    SPISettings spiSettings;
    int numChips;
    int numLeds;

    uint16_t headerArray[3];
    // All default values, except disable dot correction mode
    uint16_t configArray[3];
    uint16_t dataHeader[3];
    uint16_t* dataArray;
};

#endif
