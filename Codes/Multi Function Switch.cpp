#include <Arduino.h>
#include <Joystick.h>

/*
Button Map
Button 0 = Light
Button 1 = High-Bim
Button 2 = Passing Light
Button 3 = Left TurnSignal
Button 4 = Right TurnSignal
Button 5 = Hazard
Button 6 = Engine Brake
Button 7 = Retarder Up
Button 8 = Retarder Down
Button 9 = Wiper Up
Button 10 = Wiper Down
Button 11 = Cruise Control Set
Button 12 = Warning Light
Button 13 = Engine Electronic On/Stop
Button 14 = Engine Start/Stop
*/

Joystick_ Joystick(0x04,JOYSTICK_TYPE_JOYSTICK,
  15, 0,                   //Button Count, Hat Switch Count
  false, false, false,    //X and Y, Z Axis
  false, false, false,    //No Rx, Ry, or Rz
  false, false,           //No rudder or throttle
  false, false, false);   //No accelerator, brake, or steering

// Set Pin Map
const int RightTurnSignalPin = 2;
const int LeftTurnSignalPin = 3;
const int PassingPin = 4;
const int FogLampPin = 5;
const int HeadLampPin = 6;
const int TailLampPin = 7;
const int WiperLOPin = 8;
const int WiperHIPin = 9;
const int WiperINTPin = 10;
const int KeyStartPin = 11;
const int KeyOnPin = 12;
const int WiperMistPin = A1;
const int RearWiperPin = A2;
const int FrontWasherPin = A3;
const int RearWasherPin = A4;
const int TimeAnalogPin = A5;

void setup() {
  // Initialize Pins
  pinMode(RightTurnSignalPin, INPUT);
  pinMode(LeftTurnSignalPin, INPUT);
  pinMode(PassingPin, INPUT_PULLUP);
  pinMode(FogLampPin, INPUT_PULLUP);
  pinMode(HeadLampPin, INPUT_PULLUP);
  pinMode(TailLampPin, INPUT_PULLUP);
  pinMode(WiperHIPin, INPUT);
  pinMode(WiperINTPin, INPUT);
  pinMode(WiperLOPin, INPUT);
  pinMode(KeyStartPin, INPUT_PULLUP);
  pinMode(KeyOnPin, INPUT_PULLUP);
  pinMode(WiperMistPin, INPUT);
  pinMode(RearWiperPin, INPUT);
  pinMode(FrontWasherPin, INPUT);
  pinMode(RearWasherPin, INPUT);
  pinMode(TimeAnalogPin, INPUT_PULLUP);
  // Initialize Joystick Library
  Joystick.begin();
}

// Define variables current state of the light switch
int CurrentTailLampState = 0;
int CurrentHeadLampState = 0;
int CurrentLeftTurnSignalState = 0;
int CurrentRightTurnSignalState = 0;
int CurrentPassingSwitchState = 0;
int CurrentFogLampSwitchState = 0;

// Define variables current state of the washer switch
int CurrentINTSwitchState = 0;
int CurrentLOSwitchState = 0;
int CurrentHISwitchState = 0;
int CurrentFrontWasherState = 0;
int CurrentRearWiperSwitchState = 0;
int CurrentRearWasherState = 0;
int CurrentMistState = 0;
int CurrentINTState = 0;
int CurrentTimeState = 0;

// Define variables current state of the key switch
int CurrentKeyOnState = 0;
int CurrentKeyStartState = 0;

// Define variables current state of buttons
int CurrentHazardState = 0;
int CurrentEngineBrakeState = 0;
int CurrentWarningState = 0;
int CurrentWiperState = 0;
int CurrentRetarderState = 0;
int CurrentEngineState = 0;

// Define variables last state of the light switch
int LastTailLampState = 0;
int LastHeadLampState = 0;
int LastLeftTurnSignalState = 0;
int LastRightTurnSignalState = 0;
int LastPassingSwitchState = 0;
int LastFogLampSwitchState = 0;

// Define variables last state of the siper switch
int LastINTSwitchState = 0;
int LastLOSwitchState = 0;
int LastHISwitchState = 0;
int LastFrontWasherSwitchState = 0;
int LastRearWiperSwitchState = 0;
int LastRearWahserSwitchState = 0;
int LastMistSwitchState = 0;
int LastTimeState = 0;

// Define variables last state of the key switch
int LastKeyOnState = 0;

// Get state of current state of the light switch
void GetSwitchState() {
  CurrentHeadLampState = !digitalRead(HeadLampPin);
  CurrentTailLampState = !digitalRead(TailLampPin);
  CurrentLeftTurnSignalState = digitalRead(LeftTurnSignalPin);
  CurrentRightTurnSignalState = digitalRead(RightTurnSignalPin);
  CurrentPassingSwitchState = !digitalRead(PassingPin);
  CurrentFogLampSwitchState = !digitalRead(FogLampPin);
  CurrentINTSwitchState = digitalRead(WiperINTPin);
  CurrentLOSwitchState = digitalRead(WiperLOPin);
  CurrentHISwitchState = digitalRead(WiperHIPin);
  CurrentFrontWasherState = digitalRead(FrontWasherPin);
  CurrentRearWasherState = digitalRead(RearWasherPin);
  CurrentRearWiperSwitchState = digitalRead(RearWiperPin);
  CurrentMistState = digitalRead(WiperMistPin);
  CurrentTimeState = analogRead(TimeAnalogPin);
  CurrentKeyOnState = !digitalRead(KeyOnPin);
  CurrentKeyStartState = !digitalRead(KeyStartPin);
}

// Set the high-bim button
void SetHighBimButton() {
  if (CurrentFogLampSwitchState != LastFogLampSwitchState) {
    if (CurrentFogLampSwitchState == 1) {
      Joystick.pressButton(1);
      delay(10);
      Joystick.releaseButton(1);
    } else if (CurrentFogLampSwitchState == 0) {
      Joystick.pressButton(1);
      delay(10);
      Joystick.releaseButton(1);
    }
    LastFogLampSwitchState = CurrentFogLampSwitchState;
  }
}

// Set constant state of the lamp switch
const int LampOffState = 0;
const int LampOnState = 1;

// Set the head lamp button
void SetHeadLampButton() {
  if (CurrentTailLampState == LampOnState) {
    if (LastTailLampState == LampOffState) {
      Joystick.setButton(0, 1);
      delay(10);
      Joystick.setButton(0, 0);
    } else if (LastTailLampState == LampOnState) {
      if (CurrentHeadLampState == LampOnState) {
        if (LastHeadLampState == LampOffState) {
          Joystick.setButton(0, 1);
          delay(10);
          Joystick.setButton(0, 0);
        }
      } else if (CurrentHeadLampState == LampOffState) {
        if (LastHeadLampState == LampOnState) {
          Joystick.setButton(0, 1);
          delay(10);
          Joystick.setButton(0, 0);
          delay(10);
          Joystick.setButton(0, 1);
          delay(10);
          Joystick.setButton(0, 0);
        }
      }
    }
  } else if (CurrentTailLampState == LampOffState) {
    if (LastTailLampState == LampOnState) {
      Joystick.setButton(0, 1);
      delay(10);
      Joystick.setButton(0, 0);
      delay(10);
      Joystick.setButton(0, 1);
      delay(10);
      Joystick.setButton(0, 0);
    }
  }
  LastTailLampState = CurrentTailLampState;
  LastHeadLampState = CurrentHeadLampState;
}

// Set constant state of the turn signal switch
const int TurnSignalOffState = 0;
const int TurnSignalOnState = 1;

// Set the turn signal button
void SetTurnSignalButton() {
  if (CurrentLeftTurnSignalState == TurnSignalOnState) {
    if (LastLeftTurnSignalState == TurnSignalOffState) {
      Joystick.setButton(3, 1);
      delay(10);
      Joystick.setButton(3, 0);
    }
  } else if (CurrentLeftTurnSignalState == TurnSignalOffState) {
    if (LastLeftTurnSignalState == TurnSignalOnState) {
      Joystick.setButton(3, 1);
      delay(10);
      Joystick.setButton(3, 0);
    }
  }
  if (CurrentRightTurnSignalState == TurnSignalOnState) {
    if (LastRightTurnSignalState == TurnSignalOffState) {
      Joystick.setButton(4, 1);
      delay(10);
      Joystick.setButton(4, 0);
    }
  } else if (CurrentRightTurnSignalState == TurnSignalOffState) {
    if (LastRightTurnSignalState == TurnSignalOnState) {
      Joystick.setButton(4, 1);
      delay(10);
      Joystick.setButton(4, 0);
    }
  }
  LastLeftTurnSignalState = CurrentLeftTurnSignalState;
  LastRightTurnSignalState = CurrentRightTurnSignalState;
}

// Set constant state of the passing switch
const int PassingOffState = 0;
const int PassingOnState = 1;

// Set the passing button
void SetPassingButton() {
  if (CurrentPassingSwitchState != LastPassingSwitchState) {
    if (CurrentPassingSwitchState == PassingOffState) {
      Joystick.setButton(2,0);
    }
    else if (CurrentPassingSwitchState == PassingOnState) {
      Joystick.setButton(2,1);
    }
    LastPassingSwitchState = CurrentPassingSwitchState;
  }
}

const int DefaultWasherState = 0;
const int WasherOnState = 1;
const int HazardOffState = 0;
const int HazardOnState = 1;

void SetHazardButton() {
  if (CurrentFrontWasherState == WasherOnState) {
    if (CurrentHazardState == HazardOffState) {
      Joystick.setButton(5, 1);
      CurrentHazardState = HazardOnState;
    } else if (CurrentHazardState == HazardOnState) {
      Joystick.setButton(5, 1);
      CurrentHazardState = HazardOffState;
    }
  } else if (CurrentFrontWasherState == DefaultWasherState) {
    Joystick.setButton(5, 0);
  }
}

const int RearWasherOnState = 1;
const int EngineBrakeOffState = 0;
const int EngineBrakeOnState = 1;

void setEngineBrakeToggleButton() {
  if (CurrentRearWasherState == RearWasherOnState) {
    Joystick.setButton(6, 1);
  } else if (CurrentRearWasherState == DefaultWasherState) {
    Joystick.setButton(6, 0);
  }
}

const int MistOnState = 1;
const int MistOffState = 0;

void SetCruiseControlButton() {
  if (CurrentMistState == MistOnState) {
    Joystick.setButton(11, 1);
  } else if (CurrentMistState == MistOffState) {
    Joystick.setButton(11, 0);
  }
}

void SetWarningButton() {
  if (CurrentRearWiperSwitchState != LastRearWiperSwitchState) {
    Joystick.setButton(12, 1);
    delay(10);
    Joystick.setButton(12, 0);
    LastRearWiperSwitchState = CurrentRearWiperSwitchState;
  }
}

const int Time_OF_MAX = 1024;
const int Time_OF_MIN = 520;
const int Time_LO_MAX = 420;
const int Time_LO_MIN = 410;
const int Time_MD_MAX = 290;
const int Time_MD_MIN = 280;
const int Time_HI_MAX = 20;
const int Time_HI_MIN = 10;

void SetWiperButton() {
  if (Time_OF_MIN <= CurrentTimeState && CurrentTimeState <= Time_OF_MAX) {
    if (Time_LO_MIN <= LastTimeState && LastTimeState <= Time_LO_MAX) {
      Joystick.setButton(10, 1);
      delay(10);
      Joystick.setButton(10, 0);
    }
  } else if (Time_LO_MIN <= CurrentTimeState && CurrentTimeState <= Time_LO_MAX) {
    if (Time_OF_MIN <= LastTimeState && LastTimeState <= Time_OF_MAX) {
      Joystick.setButton(9, 1);
      delay(10);
      Joystick.setButton(9, 0);
    } else if (Time_MD_MIN <= LastTimeState && LastTimeState <= Time_MD_MAX) {
      Joystick.setButton(10, 1);
      delay(10);
      Joystick.setButton(10, 0);
    }
  } else if (Time_MD_MIN <= CurrentTimeState && CurrentTimeState <= Time_MD_MAX) {
    if (Time_LO_MIN <= LastTimeState && LastTimeState <= Time_LO_MAX) {
      Joystick.setButton(9, 1);
      delay(10);
      Joystick.setButton(9, 0);
    } else if (Time_HI_MIN <= LastTimeState && LastTimeState <= Time_HI_MAX) {
      Joystick.setButton(10, 1);
      delay(10);
      Joystick.setButton(10, 0);
    }
  } else if (Time_HI_MIN <= CurrentTimeState && CurrentTimeState <= Time_HI_MAX) {
    if (Time_MD_MIN <= LastTimeState && LastTimeState <= Time_MD_MAX) {
      Joystick.setButton(9, 1);
      delay(10);
      Joystick.setButton(9, 0);
    }
  }
  LastTimeState = CurrentTimeState;
}

int RetarderState = 0;

const int Retarder_OF = 0;
const int Retarder_LO = 1;
const int Retarder_MD = 2;
const int Retarder_HI = 3;

void SetRetarderButton() {
  if (CurrentINTSwitchState == 1 && CurrentLOSwitchState == 0 && CurrentHISwitchState == 0) {
    if (LastINTSwitchState == 0 && LastLOSwitchState == 1 && LastHISwitchState == 0) {
      Joystick.setButton(8, 1);
      delay(1000);
      Joystick.setButton(8, 0);
    } else if (LastINTSwitchState == 0 && LastLOSwitchState == 0 && LastHISwitchState == 0) {
      Joystick.setButton(7, 1);
      delay(1000);
      Joystick.setButton(7, 0);
    }
    RetarderState = Retarder_LO;
  } else if (CurrentINTSwitchState == 0 && CurrentLOSwitchState == 1 && CurrentHISwitchState == 0) {
    if (LastINTSwitchState == 1 && LastLOSwitchState == 0 && LastHISwitchState == 0) {
      Joystick.setButton(7, 1);
      delay(1000);
      Joystick.setButton(7, 0);
    } else if (LastINTSwitchState == 0 && LastLOSwitchState == 0 && LastHISwitchState == 1) {
      Joystick.setButton(8, 1);
      delay(1000);
      Joystick.setButton(8, 0);
    }
    RetarderState = Retarder_MD;
  } else if (CurrentINTSwitchState == 0 && CurrentLOSwitchState == 0 && CurrentHISwitchState == 1) {
    if (LastINTSwitchState == 0 && LastLOSwitchState == 1 && LastHISwitchState == 0) {
      Joystick.setButton(7, 1);
      delay(1000);
      Joystick.setButton(7, 0);
    }
    RetarderState = Retarder_HI;
  } else if (CurrentINTSwitchState == 0 && CurrentLOSwitchState == 0 && CurrentHISwitchState == 0) {
    if (LastINTSwitchState == 1 && LastLOSwitchState == 0 && LastHISwitchState == 0) {
      Joystick.setButton(8, 1);
      delay(1000);
      Joystick.setButton(8, 0);
    }
    RetarderState = Retarder_OF;
  }
  LastINTSwitchState = CurrentINTSwitchState;
  LastLOSwitchState = CurrentLOSwitchState;
  LastHISwitchState = CurrentHISwitchState;
}

void SetEngineStartButton() {
  if (CurrentKeyOnState == 1) {
    if (LastKeyOnState == 0) {
    Joystick.setButton(13, 1);
    delay(10);
    Joystick.setButton(13, 0);
  } else if (LastKeyOnState == 1) {
    if (CurrentKeyStartState == 1) {
      Joystick.setButton(14, 1);
    } else if (CurrentKeyStartState == 0) {
      Joystick.setButton(14, 0);
    }
  }
} else if (CurrentKeyOnState == 0) {
  if (LastKeyOnState == 1) {
    Joystick.setButton(13, 1);
    delay(10);
    Joystick.setButton(13, 0);
  }
}
}

void setJoystickButton() {
  SetHeadLampButton();
  SetHighBimButton();
  SetTurnSignalButton();
  SetPassingButton();
  SetWarningButton();
  SetCruiseControlButton();
  SetHazardButton();
  SetRetarderButton();
  SetWiperButton();
  SetEngineStartButton();
}

void loop() {
  GetSwitchState();
  setJoystickButton();
  delay(50);
}
