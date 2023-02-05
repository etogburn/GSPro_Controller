#include "Button_Controller.h"

Button_Controller::Button_Controller(uint8_t pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
    DoEvents();
};

uint8_t Button_Controller::State() {
    return _state;
};

uint8_t Button_Controller::State(uint8_t num) {
    return State() & (1 << num);
};

void Button_Controller::DoEvents() {
    if(millis() - _lastPress < DEBOUNCE_DELAY) return;

    StateRemove(BTN_TIMEOUT_PRESS);
    StateRemove(BTN_PRESSING);
    StateRemove(BTN_RELEASING);
    StateRemove(BTN_LONG_PRESS);

    if(ReadPin()) {
        if(GetTimePressed() >= BTN_TIMEOUT_THRESHOLD) {
            StateAdd(BTN_TIMEOUT_PRESS);
            _timeoutEnabled = true;
            StateRelease();
            StateIsReleasing();
        }
        if(State(BTN_RELEASED)) {
            StateIsPressing();
        }
        StatePress();
        
    } else  {
        if(State(BTN_PRESSED)) {
            StateIsReleasing();
        }
        StateRelease();
    } 
};

long Button_Controller::GetTimePressed() {
    _startPressed > 0 ? _timePressed = millis() - _startPressed : _timePressed = 0;

    return _timePressed;
};

bool Button_Controller::ReadPin() {
    bool _pinStatus = digitalRead(_pin) ? true : false;
    if(_timeoutEnabled) {
        if(!_pinStatus) _timeoutEnabled = false;
        _pinStatus = false;
    } 
    return _pinStatus;
}

void Button_Controller::StateClear() {
    _state = 0;
}

void Button_Controller::StateAdd(uint8_t num) {
    _state |= 1 << num;
}

void Button_Controller::StateRemove(uint8_t num) {
    _state &= ~(1 << num);
}

void Button_Controller::StateRelease() {
    StateAdd(BTN_RELEASED);
    StateRemove(BTN_PRESSED);
    _startPressed = -1;
}

void Button_Controller::StatePress() {
    StateAdd(BTN_PRESSED);
    StateRemove(BTN_RELEASED);
    _startReleased = -1;
}

void Button_Controller::StateIsReleasing() {
    _startReleased = millis();
    StateAdd(BTN_RELEASING);
    if(GetTimePressed() > LONG_PRESS_THRESHOLD && GetTimePressed() < BTN_TIMEOUT_THRESHOLD) StateAdd(BTN_LONG_PRESS);
}

void Button_Controller::StateIsPressing() {
    _startPressed = millis();
    _lastPress = _startPressed;
    StateAdd(BTN_PRESSING);
}