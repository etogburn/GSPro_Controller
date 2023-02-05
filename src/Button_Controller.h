#ifndef BUTTON_CONTROLLER_h
#define BUTTON_CONTROLLER_h

#include <Arduino.h>

//returns from button.State()
//number of bits to shift over
#define BTN_RELEASED 0 //open
#define BTN_PRESSED 1 //closed
#define BTN_PRESSING 2
#define BTN_RELEASING 3
#define BTN_LONG_PRESS 4
#define BTN_TIMEOUT_PRESS 5
#define LONG_PRESS_THRESHOLD 1000 //ms
#define BTN_TIMEOUT_THRESHOLD 3000 //ms
#define DEBOUNCE_DELAY 20

class Button_Controller {
public:
    Button_Controller(uint8_t pin);
    uint8_t State();
    uint8_t State(uint8_t);
    void DoEvents();
    
private:
    bool ReadPin();
    uint8_t _pin = 0;
    uint8_t _state = 0;
    uint8_t _clickCount = 0;
    long _timePressed = 0;
    long _timeReleased = 0;
    long _startReleased = -1;
    long _startPressed = -1;
    long _lastPress = 0;
    long GetTimePressed();
    long GetTimeReleased();
    bool _timeoutEnabled = false;

    void StateClear();
    void StateAdd(uint8_t);
    void StateRemove(uint8_t);
    void StateRelease();
    void StatePress();
    void StateIsReleasing();
    void StateIsPressing();
};

#endif