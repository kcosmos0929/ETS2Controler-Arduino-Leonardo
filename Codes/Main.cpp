#include <Arduino.h>
#include <Joystick.h>

bool TailLightPinState = 0;
bool HeadLightPinState = 0;
bool RightBlinkerPinState = 0;
bool LeftBlinkerPinState = 0;
bool LoBeamSwitchPinState = 0;
bool HiBeamSwitchPinState = 0;
bool LoBeamSignalPinState = 0;
bool FogLightPinState = 0;
bool IntWiperPinState = 0;
bool LoWiperPinState = 0;
bool HiWiperPinState = 0;
bool MistWiperPinState = 0;
bool RearIntWiperPinState = 0;
bool RearOnWiperPinState = 0;
bool WasherPinState = 0;
bool RearWasherPinState = 0;
bool AnalogIntPinValue = 0;

// Define the variables of states and set the variables to zero

int Value;
int S1;
int S2;
int Data;
int SH;
int SP;

// Define the pinS

char HeadLampSwitch = "O";
// O = off, T = tail, H = head
char BlinkerSwitch = "O";
// O = off, R = right, L = left
char PassingDimmerSwitch = "L";
// L = low, H = high, P = passing
char FogLampSwitch = "F";
// F = off, T = on
char WiperSwitch = "O";
// O = off, I = int, L = lo, H = hi
char MistSwitch = "F";
// F = off, T = on
char RearWiperSwitch = "O";
// O = off, I = int, N = on
char WasherSwitch = "F";
char RearWasherSwitch = "F";
// F = off, T = on
