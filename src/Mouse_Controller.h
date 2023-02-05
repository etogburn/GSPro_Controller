#ifndef MOUSE_CONTROLLER_h
#define MOUSE_CONTROLLER_h

#include <Arduino.h>
#include <Mouse.h>

#define MAX_STEP 127
#define SCREEN_HOMEX_DIRECTION -1 //negative is left, positive is right
#define SCREEN_HOMEY_DIRECTION -1 //negative is top, positive is bottom
#define X_HOME_DIR SCREEN_HOMEX_DIRECTION
#define Y_HOME_DIR SCREEN_HOMEY_DIRECTION
#define X_HOME_VAL MAX_STEP * X_HOME_DIR
#define Y_HOME_VAL MAX_STEP * Y_HOME_DIR
#define HOME_STEPS 12

class Mouse_Controller {
public:
    Mouse_Controller(int16_t, int16_t, uint8_t);
    void GoTo(int32_t, int32_t);
    void Home();
    void Click();
    void Move(int8_t, int8_t);
private:
    void Start();
    void MoveRaw(int8_t, int8_t);
    int16_t _xResolution;
    int16_t _yResolution;
};

#endif