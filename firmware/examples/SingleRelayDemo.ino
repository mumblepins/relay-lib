#include "RelayLib.h"

const int relay_pin = D7;

//RelayLib relay;  // you need to call begin() no matter what and provide minimum pin argument (see below)
RelayLib relay(relay_pin);  // still requires begin() to set pinMode to output

void setup() 
{
  Serial.begin(9600);
  relay.begin();  // BEGIN: pin, Initial State (HIGH or LOW), Relay Action (ACTIVE_LOW or ACTIVE_HIGH), Pulse Delay in mS
  relay.on(); 
  delay(2000);
  relay.off();
  delay(2000);
  relay.pulse(16383, USING_MICROS);  // this kind of pulse blocks!
  delay(1000);
  relay.pulse();  // this kind of pulse blocks, using default pulseDelay 
  delay(1000);
}

void loop() 
{
  relay.update();
  static unsigned long lastTime = 0;
  if(millis() - lastTime > 2000UL)
  {
    //relay.isOn()? relay.off(): relay.on();  // example using getter method
    relay.noBlockPulse(50000UL, USING_MICROS); // MUST be used with update() in loop(), optional USING_MICROS vs USING_MILLIS
    //relay.noBlockPulse(300UL); // MUST be used with update() in loop() defaults to USING_MILLIS
    lastTime = millis();
  }
}
