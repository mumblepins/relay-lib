About
===
Basic relay control library.  Based off of http://awtfy.com/2011/07/14/a-too-simple-arduino-library-for-handling-the-seeeduino-relay-shield-and-generic-relays/


##Constructors
```cpp
// Empty constructor.  Will cause problems if not replaced with another
// constructor at some point, or initialized with init() function
RelayLib relay = RelayLib();

// Constructor for use with standard digitalWrite function. initState is
// optional and defaults to LOW
// NOTE: Will run pinMode for you.
RelayLib relay = RelayLib(relayPin, initState); 

// Constructor for use with any function like digitalWrite. initState
// optional as before.
// NOTE: Will not setup pin mode. SET IT UP FIRST!
// digitalWrite like function must be of form:
// void function(uint16_t, uint8_t)
//
// E.G. using the MCP23008 GPIO expander:
void mcpDigitalWrite(uint16_t p, uint8_t d) {
    mcp.digitalWrite(p, d);
}

RelayLib relay = RelayLib(mcpDigitalWrite,relayPin,initState);

// Init functions are similar to constructor forms:
relay.init(relayPin, initState);
relay.init(mcpDigitalWrite,relayPin,initState);
```

##Member Functions
```cpp
// Turns relay on
void on();    
// Turns relay off
 void off();  
// Toggles state of relay between on and off
void toggle();  
// pulse relay on, then off after delay (in ms).
// If already on, will turn it off after the given delay time
void pulse(int delayTime=300); 

// returns state of relay (LOW/0/off or HIGH/1/on)
int state(); 

// Returns TRUE if the relay is on , false otherwise.
// Both functions are identical, and retained for backwards compatibility
bool isRelayOn();
bool isOn();

// Returns TRUE if the relay is off, false otherwise
bool isRelayOff();  
bool isOff();
```
