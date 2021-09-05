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
*/

const int LightButton = 0;
const int HighBimButton = 1;
const int PassingLightButton = 2;
const int LeftTurnSignalButton = 3;
const int RightTurnSignalButton = 4;
const int HazardButton = 5;
const int EngineBrakeButton = 6;
const int RetarderUpButton = 7;
const int RetarderDownButton = 8;
const int WiperUpButton = 9;
const int WiperDownButton = 10;
const int CruiseControlSetButton = 11;
const int WarningLightButton = 12;

Joystick_ Joystick(0x04,JOYSTICK_TYPE_JOYSTICK,
    13, 0,                   //Button Count, Hat Switch Count
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
const int WiperMistPin = A1;
const int RearWiperPin = A2;
const int FrontWasherPin = A3;
const int RearWasherPin = A4;
const int TimeAnalogPin = A5;
const int PinCount = 14;

// Define state data set
int CurrentPinStateArray[PinCount];
int LastPinStateArray[PinCount];


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
    pinMode(WiperMistPin, INPUT);
    pinMode(RearWiperPin, INPUT);
    pinMode(FrontWasherPin, INPUT);
    pinMode(RearWasherPin, INPUT);
    pinMode(TimeAnalogPin, INPUT_PULLUP);
    // Initialize Joystick Library
    Joystick.begin();
}

void GetWiperSwitchState(int INTVALUE) {   
    int CurrentWiperSwitchState;
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
    CurrentPinStateArray[13] = CurrentWiperSwitchState;
}

void GetSwitchState() {
    CurrentPinStateArray[0] = digitalRead(LeftTurnSignalPin);
    CurrentPinStateArray[1] = digitalRead(RightTurnSignalPin);
    CurrentPinStateArray[2] = !digitalRead(TailLampPin);
    CurrentPinStateArray[3] = !digitalRead(HeadLampPin);
    CurrentPinStateArray[4] = !digitalRead(PassingPin);
    CurrentPinStateArray[5] = !digitalRead(FogLampPin);
    CurrentPinStateArray[6] = digitalRead(WiperINTPin);
    CurrentPinStateArray[7] = digitalRead(WiperLOPin);
    CurrentPinStateArray[8] = digitalRead(WiperHIPin);
    CurrentPinStateArray[9] = digitalRead(RearWiperPin);
    CurrentPinStateArray[10] = digitalRead(FrontWasherPin);
    CurrentPinStateArray[11] = digitalRead(RearWasherPin);
    CurrentPinStateArray[12] = digitalRead(WiperMistPin);
    int v = analogRead(TimeAnalogPin);
    GetWiperSwitchState(v);
}

void PressButton(int n, int x) {
    for (int i; i < x; i++) {
        Joystick.pressButton(n);
        delay(10);
        Joystick.releaseButton(n);
    }
}


void SetControllerButton() {
    for (int i = 0; i < PinCount; i++) {
        int CurrentPinState = CurrentPinStateArray[i];
        int LastPinState = LastPinStateArray[i];
        if (CurrentPinState != LastPinState) {
            switch (i) {
            // Turnsignal control
            case 0:
                PressButton(LeftTurnSignalButton, 1);
                LastPinStateArray[0] = CurrentPinState;
                break;
            case 1:
                PressButton(RightTurnSignalButton, 1);
                LastPinStateArray[1] = CurrentPinState;
                break;
            // Head light control
            case 2:
            case 3:
                int C1 = CurrentPinStateArray[2];
                int C2 = CurrentPinStateArray[3];
                int L1 = LastPinStateArray[2];
                int L2 = LastPinStateArray[3];
                int HeadLightIndex = (C1 + C2) - (L1 + L2);
                /*
                -2, -1, 1, 2
                */
                switch (HeadLightIndex)
                {
                case -2:
                    PressButton(LightButton, 1);
                    break;
                case -1:
                    PressButton(LightButton, 2);
                    break;
                case 1:
                    PressButton(LightButton, 1);
                    break;
                case 2:
                    PressButton(LightButton, 2);
                    break;
                default:
                    break;
                }
                LastPinStateArray[2] = C1;
                LastPinStateArray[3] = C2;
                break;
            // Passing light control
            case 4:
                int PassingIndex = CurrentPinState - LastPinState;
                switch (PassingIndex) {
                case -1:
                    Joystick.releaseButton(PassingLightButton);
                    break;
                case 1:
                    Joystick.pressButton(PassingLightButton);
                    break;
                default:
                    break;
                }
                LastPinStateArray[4] = CurrentPinState;
                break;
            // High bim control
            case 5:
                PressButton(HighBimButton, 1);
                LastPinStateArray[5] = CurrentPinState;
                break;
            // Retarder control
            case 6:
            case 7:
            case 8:
                int C1 = CurrentPinStateArray[6];
                int C2 = CurrentPinStateArray[7];
                int C3 = CurrentPinStateArray[8];
                int L1 = LastPinStateArray[6];
                int L2 = LastPinStateArray[7];
                int L3 = LastPinStateArray[8];
                /* 인덱스를 조정하기 위해 각 값에 따라 가중치를 부여하여 구분
                (int,lo,hi) : (0,0,0), (1,0,0), (0,1,0), (0,0,1)
                발생가능한 RetarderIndex의 값
                -1, 1 (off-int)
                -3, 3 (off-lo)
                -7, 7 (off-hi)
                -2, 2 (int-lo)
                -6, 6 (int-hi)
                -4, 4 (lo-hi)
                */
                int RetarderIndex = (C1-L1) + (C2-L2)*3 + (C3-L3)*7;
                switch (RetarderIndex)
                {
                case -7:
                    PressButton(RetarderDownButton, 3);
                    break;
                case -6:
                    PressButton(RetarderDownButton, 2);
                    break;
                case -4:
                    PressButton(RetarderDownButton, 1);
                    break;
                case -3:
                    PressButton(RetarderDownButton, 2);
                    break;
                case -2:
                    PressButton(RetarderDownButton, 1);
                    break;
                case -1:
                    PressButton(RetarderDownButton, 1);
                    break;
                case 1:
                    PressButton(RetarderUpButton, 1);
                    break;
                case 2:
                    PressButton(RetarderUpButton, 1);
                    break;
                case 3:
                    PressButton(RetarderUpButton, 2);
                    break;
                case 4:
                    PressButton(RetarderUpButton, 1);
                    break;
                case 6:
                    PressButton(RetarderUpButton, 2);
                    break;
                case 7:
                    PressButton(RetarderUpButton, 3);
                default:
                    break;
                }
                LastPinStateArray[6] = C1;
                LastPinStateArray[7] = C2;
                LastPinStateArray[8] = C3;
                break;
            // Warning light control
            case 9:
                PressButton(WarningLightButton, 1);
                LastPinStateArray[9] = CurrentPinState;
                break;
            // Hazard light control
            case 10:
                PressButton(HazardButton, 1);
                LastPinStateArray[10] = CurrentPinState;
                break;
            // Engine brake control
            case 11:
                int EngineBrakeIndex = CurrentPinState - LastPinState;
                switch (EngineBrakeIndex)
                {
                case -1:
                    Joystick.releaseButton(EngineBrakeButton);
                    break;
                case 1:
                    Joystick.pressButton(EngineBrakeButton);
                    break;
                default:
                    break;
                }
                LastPinStateArray[11] = CurrentPinState;
                break;
            // Cruise control
            case 12:
                int CruiseControlIndex = CurrentPinState - LastPinState
                switch (CruiseControlIndex)
                {
                case -1:
                    Joystick.releaseButton(CruiseControlSetButton);
                    break;
                case 1:
                    Joystick.pressButton(CruiseControlSetButton);
                    break;
                default:
                    break;
                }
                LastPinStateArray[12] = CurrentPinState;
                break;
            // Wiper control
            case 13:
                int WiperIndex = CurrentPinState - LastPinState;
                switch (WiperIndex)
                {
                case -3:
                    PressButton(WiperDownButton, 3);
                    break;
                case -2:
                    PressButton(WiperDownButton, 2);
                    break;
                case -1:
                    PressButton(WiperDownButton, 1);
                    break;
                case 1:
                    PressButton(WiperUpButton, 1);
                    break;
                case 2:
                    PressButton(WiperUpButton, 2);
                    break;
                case 3:
                    pressButton(WiperUpButton, 3);
                    break;
                default:
                    break;
                }
                LastPinStateArray[13] = CurrentPinState;
                break;
            }
        }
    }
}

void loop() {
    GetSwitchState();
    SetControllerButton();
    delay(10);
}
