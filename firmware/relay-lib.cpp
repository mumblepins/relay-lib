
#include "relay-lib.h"

RelayLib::RelayLib()
{
  _relayState = LOW;
  _action = ACTIVE_HIGH;
  _timerSelect = USING_MILLIS;
  _pulseTime = 300;
}

RelayLib::RelayLib(uint8_t relayPin)
{
  _relayPin = relayPin;
  _relayState = LOW;
  _action = ACTIVE_HIGH;
  _timerSelect = USING_MILLIS;
  _pulseTime = 300;
}

// Constructor for custom digitalWrite function NOTE: will not set pinMode of output pin
// function must be of type `void function(uint16_t, uint8_t)`
RelayLib::RelayLib(dig_write_func_t* digWrite, int relayPin, int state)
{
  _relayPin = relayPin;
  _relayState = state;
  _digWrite = digWrite;
  this->init(_relayPin, _relayState, _action, _pulseTime);
}

void RelayLib::init()
{
  this->init(_relayPin, _relayState, _action, _pulseTime);
}
void RelayLib::init(const int relayPin)
{
  this->init(relayPin, _relayState, _action, _pulseTime);
}

void RelayLib::init(const int relayPin, int initialState, RelayAction action)
{
  this->init(relayPin, initialState, action, _pulseTime);
}

void RelayLib::init(const int relayPin, int initialState, RelayAction action, uint16_t pulseMillis)
{
  _relayPin = relayPin;
  pinMode(_relayPin, OUTPUT);
  _relayState = initialState;
  _action = action;
  _pulseTime = pulseMillis;
  this->setRelay(_relayState);
}

void RelayLib::on()
{
  this->setRelay(HIGH);
}

void RelayLib::off()
{
  this->setRelay(LOW);
}

void RelayLib::setRelay(int newState)
{
  _relayState = newState;
  digitalWrite(_relayPin, (_action == ACTIVE_HIGH)? _relayState : !_relayState);
}

void RelayLib::toggle()
{
  this->setRelay(!this->getState());
}

void RelayLib::pulse()
{
  this->pulse(_pulseTime, _timerSelect);
}

void RelayLib::pulse(unsigned long pulseTime, TimeIncrements timer)
{
  this->on();
  timer == USING_MICROS? delayMicroseconds(pulseTime) : delay(pulseTime);
  this->off();
}

void RelayLib::setPulse(int pulseTime)
{
  _pulseTime = pulseTime;
}

void RelayLib::noBlockPulse(unsigned long duration, TimeIncrements timer)
{
  _timerSelect = timer;
  _commandPulseTime = duration;
  _lastTime = _timerSelect? micros() : millis();
  _activePulse = true;
  this->on();
}

void RelayLib::noBlockPulse()
{
  this->noBlockPulse(_pulseTime);
}

void RelayLib::update()
{
  this->update(_timerSelect? micros() : millis());
}

void RelayLib::update(unsigned long time)
{
  if(_activePulse)
  {
    unsigned long elapsedTime = time - _lastTime;
    if(elapsedTime > _commandPulseTime)
    {
      _activePulse = false;
      this->off();
    }
  }
}

void RelayLib::pulse(int pulseMillis)
{
  this->on();
  delay(pulseMillis);
  this->off();
}

// STATE GETTERS

bool RelayLib::getState()
{
  return _relayState;
}
bool RelayLib::isRelayOn()
{
  return _relayState;
}
bool RelayLib::isRelayOff()
{
  return !_relayState;
}
bool RelayLib::isOn()
{
  return _relayState;
}
bool RelayLib::isOff()
{
  return !_relayState;
}

//

void RelayLib::init(dig_write_func_t* digWrite, int relayPin, int state)
{
  _digWrite = digWrite;
  _relayPin = relayPin;
  _relayState = state;

  if (_relayState)
  {
    this->on();
  }
  else
  {
    this->off();
  }
}
