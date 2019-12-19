/* Arduino-HID-Lighting

    This code is copied and modified from mon's Arduino-HID-Library code:
    https://github.com/mon/Arduino-HID-Lighting

    Licensed under GPL-3.0
*/

#ifndef __HIDLED_H__
#define __HIDLED_H__

#include "Config.h"
#include "PluggableUSB.h"
#include <HID.h>

typedef struct {
  uint8_t brightness;
} SingleLED;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGBLed;

/* Important note!
    light_update works inside an interrupt handler. If the code inside here
    takes more than about 1ms, the USB stack will start breaking. Delay functions
    will also not work. Do not write out to Serial, neopixels, SPI etc. Just
    copy the data to a good place and then send it out in loop()

    Check the "examples" folder for how to do Neopixels without breaking.
*/

void light_update(SingleLED* single_leds, RGBLed* rgb_leds);

// ******************************
// don't need to edit below here

#define NUM_HID_LIGHTS (NUM_SINGLE_LED + NUM_RGB_LED*3)
#if NUM_HID_LIGHTS > 63
#error You must have less than 64 lights
#endif

union {
  struct {
    SingleLED singles[NUM_SINGLE_LED];
    RGBLed rgb[NUM_RGB_LED];
  } leds;
  uint8_t raw[NUM_HID_LIGHTS];
} led_data;

static const uint8_t PROGMEM _hidReportLEDs[] = {
  0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
  0x09, 0x00,                    // USAGE (Undefined)
  0xa1, 0x01,                    // COLLECTION (Application)
  // Globals
  0x95, NUM_HID_LIGHTS,          //   REPORT_COUNT
  0x75, 0x08,                    //   REPORT_SIZE (8)
  0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
  0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
  0x05, 0x0a,                    //   USAGE_PAGE (Ordinals)
  // Locals
  0x19, 0x01,                    //   USAGE_MINIMUM (Instance 1)
  0x29, NUM_HID_LIGHTS,          //   USAGE_MAXIMUM (Instance n)
  0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
  // BTools needs at least 1 input to work properly
  0x19, 0x01,                    //   USAGE_MINIMUM (Instance 1)
  0x29, 0x01,                    //   USAGE_MAXIMUM (Instance 1)
  0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
  0xc0                           // END_COLLECTION
};

// This is almost entirely copied from NicoHood's wonderful RawHID example
// Trimmed to the bare minimum
// https://github.com/NicoHood/HID/blob/master/src/SingleReport/RawHID.cpp
class HIDLED_ : public PluggableUSBModule {

    uint8_t epType[1];

  public:
    HIDLED_(void) : PluggableUSBModule(1, 1, epType) {
      epType[0] = EP_TYPE_INTERRUPT_IN;
      PluggableUSB().plug(this);
    }

    int getInterface(uint8_t* interfaceCount) {
      *interfaceCount += 1; // uses 1
      HIDDescriptor hidInterface = {
        D_INTERFACE(pluggedInterface, 1, USB_DEVICE_CLASS_HUMAN_INTERFACE, HID_SUBCLASS_NONE, HID_PROTOCOL_NONE),
        D_HIDREPORT(sizeof(_hidReportLEDs)),
        D_ENDPOINT(USB_ENDPOINT_IN(pluggedEndpoint), USB_ENDPOINT_TYPE_INTERRUPT, USB_EP_SIZE, 16)
      };
      return USB_SendControl(0, &hidInterface, sizeof(hidInterface));
    }

    int getDescriptor(USBSetup& setup)
    {
      // Check if this is a HID Class Descriptor request
      if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) {
        return 0;
      }
      if (setup.wValueH != HID_REPORT_DESCRIPTOR_TYPE) {
        return 0;
      }

      // In a HID Class Descriptor wIndex contains the interface number
      if (setup.wIndex != pluggedInterface) {
        return 0;
      }

      return USB_SendControl(TRANSFER_PGM, _hidReportLEDs, sizeof(_hidReportLEDs));
    }

    bool setup(USBSetup& setup)
    {
      if (pluggedInterface != setup.wIndex) {
        return false;
      }

      uint8_t request = setup.bRequest;
      uint8_t requestType = setup.bmRequestType;

      if (requestType == REQUEST_DEVICETOHOST_CLASS_INTERFACE)
      {
        return true;
      }

      if (requestType == REQUEST_HOSTTODEVICE_CLASS_INTERFACE) {
        if (request == HID_SET_REPORT) {
          if (setup.wValueH == HID_REPORT_TYPE_OUTPUT && setup.wLength == NUM_HID_LIGHTS) {
            USB_RecvControl(led_data.raw, NUM_HID_LIGHTS);
            light_update(led_data.leds.singles, led_data.leds.rgb);
            return true;
          }
        }
      }

      return false;
    }
};

HIDLED_ HIDLeds;

#endif
