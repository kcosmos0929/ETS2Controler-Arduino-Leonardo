#include <Arduino.h>
#include <Joystick.h>

bool Light_Tail(0), Light_Head(0), Beam_LO(0), Beam_HI(0), Beam_Sig(0),
//Light Switch boolean variables
Blinker_Right(0), Blinker_Left(0),
//Blinker boolean variables
FWiper_INT(0), FWiper_LO(0), Fwiper_HI(0), RWiper_INT(0), RWiper_ON(0),
//Wiper Switch boolean variables
Fog(0), Mist(0), FWasher(0), RWasher(0);

int HeadLamp, Beam, Blinker, FWiper, RWiper;

