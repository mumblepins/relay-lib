#include "relay-lib.h"

//
// The constructor sets up a single relay, specified by the Pin that relay is attached to

//
// The constructor will also properly set the assigned pin to OUTPUT.
//
RelayLib::RelayLib(int _relayPin, int _state)
{
  init(_relayPin, _state);
}


// Constructor for custom digitalWrite function NOTE: will not set pinMode of output pin
// function must be of type `void function(uint16_t, uint8_t)`
RelayLib::RelayLib(dig_write_func_t* _digWrite, int _relayPin, int _state) {
  init(_digWrite, _relayPin, _state);
}

void RelayLib::init(int _relayPin, int _state)
{
  digWrite=digitalWrite;
  relayPin=_relayPin;
  pinMode(relayPin, OUTPUT);

  if (_state == LOW) {
    relayState=LOW;
    off();
  }
  else {
    relayState=HIGH;
    on();
  }
}

void RelayLib::init(dig_write_func_t* _digWrite, int _relayPin, int _state) {
  digWrite=_digWrite;
  relayPin=_relayPin;

  if (_state == LOW) {
    relayState=LOW;
    off();
  }
  else {
    relayState=HIGH;
    on();
  }
}

// Turns the relay on.
void RelayLib::on()
{
  digitalWrite(relayPin, HIGH);
  relayState=HIGH;
}

// Turns the relay off.
void RelayLib::off()
{
  digitalWrite(relayPin, LOW);
  relayState=LOW;
}

//Toggles the state of the relay
void RelayLib::toggle()
{
  if (relayState==HIGH) {
    off();
  } else {
    on();
  }
}

// Pulse relay on, then off.  If relay is on, turn off after delay time
void RelayLib::pulse(int delayTime) {
  on();
  delay(delayTime);
  off();
}

// Returns the state of the relay (LOW/0 or HIGH/1)
int RelayLib::state()
{
  return(relayState);
}

// If the relay is on, returns true, otherwise returns false
bool RelayLib::isRelayOn()
{
  if (relayState==HIGH)
    return true;
  else
    return false;
}

// If the relay is off, returns true, otherwise returns false
bool RelayLib::isRelayOff()
{
  if (relayState==LOW)
    return true;
  else
    return false;
}
