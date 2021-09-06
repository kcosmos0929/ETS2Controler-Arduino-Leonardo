#include <Arduino.h>
#include <Joystick.h>

int EngineStartStopButton = 13;
//int KeySwitchState[3];
int CurrentAccOnState;
int CurrentOnStartState;
int CurrentStartState;
int LastAccOnState;
int LastOnStartState;
int LastStartState;

void PressButton(int n, int x) {
    for (int i; i < x; i++) {
        Joystick.pressButton(n);
        delay(10);
        Joystick.releaseButton(n);
    }
}

void GetKeyBoxState() {
    /*KeySwitchState[0] = digitalRead(AccOnPin);
    KeySwitchState[1] = digitalRead(OnStartPin);
    KeySwitchState[2] = digitalRead(StartPin);*/
    CurrnetAccOnState = digitalRead(AccOnPin);
    CurrentOnStartState = digitalRead(OnStartPin);
    CurrentStartState = digitalRead(StartPin);
}

void SetKeyButton() {
    /*
    (0,0,0),(1,0,0),(1,1,0),(0,1,1)
    -1, 1
    -3, 3
    -7, 7
    -2, 2
    -6, 6
    -4, 4
    */
    int KeyIndex = (CurrentAccOnState - LastAccOnState) + (CurrentOnStartState - LastOnStartState)*2 + (CurrentStartState - LastStartState)*5;
    switch (KeyIndex) {
        case -7:
            PressButton(EngineStartStopButton);
            break;
        case -6:
            break;
        case -4:
            break;
        case -3:
            break;
        case -2:
            break;
        case -1:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
    
