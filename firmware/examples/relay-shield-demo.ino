// This #include statement was automatically added by the Spark IDE.
#include "relay-lib/relay-lib.h"

// For current Particle relay shield
#define RELAY1_PIN D3
#define RELAY2_PIN D4
#define RELAY3_PIN D5
#define RELAY4_PIN D6

// For original Spark relay shield
// #define RELAY1_PIN D0
// #define RELAY2_PIN D1
// #define RELAY3_PIN D2
// #define RELAY4_PIN D3

RelayLib relay[] = { RelayLib(RELAY1_PIN), RelayLib(RELAY2_PIN), RelayLib(
                       RELAY3_PIN),
                     RelayLib(RELAY4_PIN) };


void setup()
{
  for (int i = 0; i < sizeof(relay) / sizeof(relay[0]); i++) {
    relay[i].init();
  }
  Particle.function("relay", relayControl);
}

void loop()
{}

// command format r1,ON or r1,OFF or r1,SWITCH or r1,PULSE
int relayControl(String command)
{
  // parse the relay number
  int relayNumber = command.charAt(1) - '0';

  // do a sanity check
  if ((relayNumber < 1) || (relayNumber > 4)) return -1;

  // find out the state of the relay
  if (command.substring(3, 5) == "ON") relay[relayNumber - 1].on();
  else if (command.substring(3, 6) == "OFF") relay[relayNumber - 1].off();
  else if (command.substring(3, 9) == "SWITCH")  relay[relayNumber - 1].toggle();
  else if (command.substring(3, 9) == "PULSE")  relay[relayNumber - 1].pulse();
  else return -1;

  return 1;
}
