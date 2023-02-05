#include "Mouse_Controller.h"

Mouse_Controller::Mouse_Controller(int16_t xVal, int16_t yVal, uint8_t scale) {
    _xResolution = xVal/scale;
    _yResolution = yVal/scale;
    Start();
}

void Mouse_Controller::GoTo(int32_t xTarget, int32_t yTarget) {
    Home();

    if(xTarget > 100 || yTarget > 100) return;

    xTarget = xTarget * _xResolution / 100;
    yTarget = yTarget * _yResolution / 100;
    int16_t xPos = 0;
    int16_t yPos = 0;
    int16_t xMoveVal = X_HOME_VAL * -1;
    int16_t yMoveVal = Y_HOME_VAL * -1;

    while(xMoveVal != 0 || yMoveVal != 0) {
        if(xPos >= xTarget - xMoveVal) xMoveVal = 0;
        if(yPos >= yTarget - yMoveVal) yMoveVal = 0;
        MoveRaw(xMoveVal, yMoveVal);
        xPos += xMoveVal;
        yPos += yMoveVal;
    }

    MoveRaw(xTarget - xPos, yTarget - yPos);
}

void Mouse_Controller::Click() {
    Mouse.click(MOUSE_LEFT);
}

void Mouse_Controller::Home() {
    int8_t xStep = X_HOME_VAL;
    int8_t yStep = Y_HOME_VAL;
    int8_t yStepRaw = yStep;
    int8_t xStepRaw = xStep;

    for(uint8_t j = 0; j < 1; j++) {
        if(j == 1) {
            xStep = 0;
            yStep = yStepRaw * -1;
        } else {
            xStep = xStepRaw;
            yStep = yStepRaw;
        }
        for(uint8_t i = 0; i < HOME_STEPS; i++) {
            MoveRaw(xStep, yStep);
        }
    }
}

void Mouse_Controller::Start() {
    Mouse.begin();
}

void Mouse_Controller::Move(int8_t xVal, int8_t yVal) {
    int32_t xCalc = xVal * _xResolution / 100;
    int32_t yCalc = yVal * _yResolution / 100;
    MoveRaw(xCalc, yCalc);
}

void Mouse_Controller::MoveRaw(int8_t xVal, int8_t yVal) {
    Mouse.move(xVal, yVal);
    delay(5);
}