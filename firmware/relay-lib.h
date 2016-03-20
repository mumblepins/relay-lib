
#ifndef _RELAY_LIB
#define _RELAY_LIB

#include "application.h"

// Based on http://awtfy.com/2011/07/14/a-too-simple-arduino-library-for-handling-the-seeeduino-relay-shield-and-generic-relays/

#define MAX_MICRO_DELAY 16383

typedef void (dig_write_func_t)(uint16_t, uint8_t);

enum RelayAction{
  ACTIVE_LOW,
  ACTIVE_HIGH
};

enum TimeIncrements{
  USING_MILLIS,
  USING_MICROS
};

class RelayLib{
  public:
    RelayLib();
    RelayLib(uint8_t relayPin);
    void init();
    void init(const int relayPin);
    void init(const int relayPin, int initialState, RelayAction action = ACTIVE_HIGH);
    void init(const int relayPin, int initialState, RelayAction action, uint16_t pulseMillis);
    void on();
    void off();
    void toggle();
    void pulse();
    void pulse(unsigned long pulseTime,TimeIncrements timer = USING_MILLIS);
    void noBlockPulse();
    void noBlockPulse(unsigned long duration, TimeIncrements timer = USING_MILLIS);
    void update();
    void update(unsigned long time);
    void pulse(int pulseMillis);
    void setPulse(int pulseTime);
    bool isRelayOn();
    bool isRelayOff();
    bool isOn();
    bool isOff();
    //
    void init(dig_write_func_t* digitalWrite, int relayPin, int _relayState = LOW);
    RelayLib(dig_write_func_t* digitalWrite, int relayPin, int _relayState = LOW); // Constructor with custom digitalWrite function

  private:
    uint8_t _relayPin;
    bool _relayState;
    RelayAction _action;
    uint16_t _pulseTime;
    unsigned long _lastTime;
    unsigned long _commandPulseTime;
    TimeIncrements _timerSelect;
    void setRelay(int newState);
    bool getState();
    bool _activePulse;
    //
    dig_write_func_t* _digWrite; // digitalWrite function
};

#endif
