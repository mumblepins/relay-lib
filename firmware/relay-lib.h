
#ifndef _RELAY_LIB
#define _RELAY_LIB

#include "application.h"

// Based on
// http://awtfy.com/2011/07/14/a-too-simple-arduino-library-for-handling-the-seeeduino-relay-shield-and-generic-relays/



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


  // template < typename T >
  // RelayLib(void (T::*write_func)(pin_t, uint8_t),
  //          void (T::*mode_func)(pin_t, PinMode), T * instance, pin_t relayPin) {
  //   _relayPin       = relayPin;
  //   _relayState     = LOW;
  //   _action         = ACTIVE_HIGH;
  //   _timerIncrement = USING_MILLIS;
  //   _pulseTime      = 300;
  //
  //   using namespace std::placeholders;
  //   _digWrite = std::bind(write_func, instance, _1, _2);
  //   _pinMode  = std::bind(mode_func, instance, _1, _2);
  // }

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


  // template < typename T>

// void init(void (T::*write_func)(pin_t, uint8_t),
//           void (T::*mode_func)(pin_t, PinMode), T *instance, pin_t relayPin)
// {
//   using namespace std::placeholders;
//
//   this->init(std::bind(write_func, instance, _1, _2),
//              std::bind(mode_func, instance, _1, _2), relayPin);
// }


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
