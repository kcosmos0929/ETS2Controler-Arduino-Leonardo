#include Joystick.h

int INTVALUE;
int CurrentWiperSwitchState;
int LastWiperSwitchState;
int WiperUPButton;
int WiperDOWNButton;

void PressWiperUPButton()
{
  Joystick.pressButton(WiperUPButton);
  delay(10);
  Joystick.releaseButton(WiperUPButton);
}

void PressWiperDOWNButton()
{
  Joystick.pressButton(WiperDOWNButton);
  delay(10);
  Joystick.releaseButton(WiperDOWNButton);
}

void GetWiperSwitchState()
{
  if (INTVALUE <= 300) {
    CurrentWiperSwitchState = 3;
    }
  else if (300 < INTVALUE <= 450) {
    CurrentWiperSwitchState = 2;
    }
  else if (450 < INTVALUE <= 750) {
    CurrentWiperSwitchState = 1;
    }
  else if (750 < INTVALUE) {
    CurrentWiperSwitchState = 0;
    }
}

void WiperButtonState()
{
  int KeyValue;
  KeyValue = CurrentWiperSwitchState - LastWiperSwitchState;
  if (KeyValue > 0) {
    for (int i = 0; i < KeyValue; i++) {
      PressWiperUPButton();
    }
  } 
  else if (KeyValue < 0) {
    KeyValue = KeyValue * (-1);
    for (int i; i < KeyValue; i++) {
      PressWiperDOWNButton();
    }
  }

  
