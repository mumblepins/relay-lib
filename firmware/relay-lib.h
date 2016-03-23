/*
   The MIT License (MIT)
   Copyright (c) 2016 Daniel Sullivan (mumblepins)

   Permission is hereby granted, free of charge, to any person obtaining a copy
      of this software and associated documentation files (the "Software"), to
      deal in the Software without restriction, including without limitation the
      rights to use, copy, modify, merge, publish, distribute, sublicense,
      and/or sell copies of the Software, and to permit persons to
       whom the
      Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
      all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
      THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
      LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
      FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
      DEALINGS IN THE SOFTWARE.


   Based on
      http://awtfy.com/2011/07/14/a-too-simple-arduino-library-for-handling-the-seeeduino-relay-shield-and-generic-relays/


 */

#ifndef _RELAY_LIB
#define _RELAY_LIB

#include "application.h"

typedef void (dig_write_func_t) (pin_t,
                                 uint8_t);

typedef void (pin_mode_func_t) (pin_t,
                                PinMode);

enum RelayAction : uint8_t {
  ACTIVE_LOW,
  ACTIVE_HIGH
};

enum TimeIncrements : uint8_t {
  USING_MILLIS,
  USING_MICROS
};

class RelayLib {
public:

  RelayLib();
  RelayLib(pin_t relayPin);
  RelayLib(pin_t relayPin, uint8_t initialState = LOW,
           RelayAction action = ACTIVE_HIGH, uint32_t pulseMillis = 300);


  RelayLib(dig_write_func_t * digWrite, pin_mode_func_t * pMode,
           pin_t relayPin);
  RelayLib(dig_write_func_t * digWrite, pin_mode_func_t * pMode,
           pin_t relayPin, uint8_t initialState = LOW,
           RelayAction action = ACTIVE_HIGH, uint32_t pulseMillis = 300);

  void init();
  void init(pin_t relayPin);
  void init(pin_t       relayPin,
            uint8_t     initialState,
            RelayAction action = ACTIVE_HIGH);
  void init(pin_t       relayPin,
            uint8_t     initialState,
            RelayAction action,
            uint32_t    pulseMillis);

  void init(dig_write_func_t *digitalWrite,
            pin_mode_func_t  *pMode,
            pin_t             relayPin);
  void init(dig_write_func_t *digitalWrite,
            pin_mode_func_t  *pMode,
            pin_t             relayPin,
            uint8_t           initialState,
            RelayAction       action = ACTIVE_HIGH);
  void init(dig_write_func_t *digitalWrite,
            pin_mode_func_t  *pMode,
            pin_t             relayPin,
            uint8_t           initialState,
            RelayAction       action,
            uint32_t          pulseMillis);

  void setRelay(uint8_t newState);
  void on();
  void off();
  void toggle();
  void pulse();
  void pulse(uint32_t       pulseTime,
             TimeIncrements timerIncrement = USING_MILLIS);
  void noBlockPulse();
  void noBlockPulse(uint32_t       duration,
                    TimeIncrements timerIncrement = USING_MILLIS);
  void update();
  void update(uint32_t time);
  void pulse(uint32_t pulseMillis);
  void setPulse(uint32_t pulseTime);
  bool isRelayOn();
  bool isRelayOff();
  bool isOn();
  bool isOff();

  bool getState();

private:

  pin_t _relayPin;
  bool  _relayState;
  RelayAction _action;
  unsigned long  _pulseTime;
  unsigned long  _lastTime;
  unsigned long  _commandPulseTime;
  TimeIncrements _timerIncrement;
  bool _activePulse = false;

  dig_write_func_t *_digWrite; // digitalWrite function
  pin_mode_func_t  *_pinMode;
};

 #endif /* ifndef _RELAY_LIB */
