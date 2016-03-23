
#include "relay-lib.h"

RelayLib::RelayLib()
{
  _relayState     = LOW;
  _action         = ACTIVE_HIGH;
  _timerIncrement = USING_MILLIS;
  _pulseTime      = 300;
  _digWrite       = digitalWrite;
  _pinMode        = pinMode;
}

RelayLib::RelayLib(const pin_t relayPin)
{
  _relayPin       = relayPin;
  _relayState     = LOW;
  _action         = ACTIVE_HIGH;
  _timerIncrement = USING_MILLIS;
  _pulseTime      = 300;
  _digWrite       = digitalWrite;
  _pinMode        = pinMode;
}

RelayLib::RelayLib(const pin_t relayPin, const uint8_t initialState,
                   const RelayAction action, const uint32_t pulseMillis) {
  _relayPin       = relayPin;
  _relayState     = initialState;
  _action         = action;
  _timerIncrement = USING_MILLIS;
  _pulseTime      = pulseMillis;
  _digWrite       = digitalWrite;

  _pinMode = pinMode;
}

RelayLib::RelayLib(dig_write_func_t *digWrite,
                   pin_mode_func_t  *pMode,
                   const pin_t       relayPin) {
  _relayPin       = relayPin;
  _relayState     = LOW;
  _action         = ACTIVE_HIGH;
  _timerIncrement = USING_MILLIS;
  _pulseTime      = 300;
  _digWrite       = digWrite;
  _pinMode        = pMode;
}

RelayLib::RelayLib(dig_write_func_t *digWrite,
                   pin_mode_func_t  *pMode,
                   const pin_t       relayPin,
                   const uint8_t     initialState,
                   const RelayAction action,
                   const uint32_t    pulseMillis) {
  _relayPin       = relayPin;
  _relayState     = initialState;
  _action         = action;
  _timerIncrement = USING_MILLIS;
  _pulseTime      = pulseMillis;
  _digWrite       = digWrite;
  _pinMode        = pMode;
}

void RelayLib::init()
{
  this->init(_relayPin, _relayState, _action, _pulseTime);
}

void RelayLib::init(const pin_t relayPin)
{
  this->init(relayPin, _relayState, _action, _pulseTime);
}

void RelayLib::init(const pin_t relayPin, const uint8_t initialState,
                    const RelayAction action)
{
  this->init(relayPin, initialState, action, _pulseTime);
}

void RelayLib::init(const pin_t relayPin, const uint8_t initialState,
                    const RelayAction action, const uint32_t pulseMillis)
{
  _relayPin = relayPin;
  _pinMode(_relayPin, OUTPUT);
  _relayState = initialState;
  _action     = action;
  _pulseTime  = pulseMillis;
  this->setRelay(_relayState);
}

void RelayLib::init(dig_write_func_t *digitalWrite,
                    pin_mode_func_t  *pMode,
                    const pin_t       relayPin) {
  _digWrite = digitalWrite;
  _pinMode  = pMode;
  this->init(relayPin, _relayState, _action, _pulseTime);
}

void RelayLib::init(dig_write_func_t *digitalWrite,
                    pin_mode_func_t  *pMode,
                    const pin_t       relayPin,
                    const uint8_t     initialState,
                    const RelayAction action) {
  _digWrite = digitalWrite;
  _pinMode  = pMode;
  this->init(relayPin, initialState, action, _pulseTime);
}

void RelayLib::init(dig_write_func_t *digitalWrite, pin_mode_func_t *pMode,
                    const pin_t relayPin, const uint8_t initialState,
                    const RelayAction action, const uint32_t pulseMillis) {
  _digWrite = digitalWrite;
  _pinMode  = pMode;
  this->init(relayPin, initialState, action, pulseMillis);
}

void RelayLib::on()
{
  this->setRelay(HIGH);
}

void RelayLib::off()
{
  // this->setRelay(LOW);
}

void RelayLib::setRelay(const uint8_t newState)
{
  _relayState = newState;
  _digWrite(_relayPin, (_action == ACTIVE_HIGH) ? _relayState : !_relayState);
}

void RelayLib::toggle()
{
  this->setRelay(!this->getState());
}

void RelayLib::pulse()
{
  this->pulse(_pulseTime, _timerIncrement);
}

void RelayLib::pulse(const uint32_t       pulseTime,
                     const TimeIncrements timerIncrement)
{
  this->on();
  (timerIncrement == USING_MICROS) ? delayMicroseconds(pulseTime) : delay(
    pulseTime);
  this->off();
}

void RelayLib::setPulse(const uint32_t pulseTime)
{
  _pulseTime = pulseTime;
}

void RelayLib::noBlockPulse(const uint32_t       duration,
                            const TimeIncrements timerIncrement)
{
  _timerIncrement   = timerIncrement;
  _commandPulseTime = duration;
  _lastTime         = (_timerIncrement == USING_MICROS) ? micros() : millis();
  _activePulse      = true;
  this->on();
}

void RelayLib::noBlockPulse()
{
  this->noBlockPulse(_pulseTime);
}

void RelayLib::update()
{
  this->update((_timerIncrement == USING_MICROS) ? micros() : millis());
}

void RelayLib::update(const uint32_t time)
{
  if (_activePulse)
  {
    unsigned long elapsedTime = time - _lastTime;

    if (elapsedTime >= _commandPulseTime)
    {
      _activePulse = false;
      this->off();
    }
  }
}

void RelayLib::pulse(const uint32_t pulseMillis)
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
