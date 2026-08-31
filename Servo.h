#ifndef LEGAL_SERVO_H_REPLACEMENT
#define LEGAL_SERVO_H_REPLACEMENT

// ------------------------------------------------------------
// Legal Servo.h Replacement (CC BY-NC-ND)
// Minimal clean-room Servo class stub.
// ------------------------------------------------------------

#include "Arduino.h"

class Servo {
public:
    Servo() : attachedPin(255), angle(0) {}

    uint8_t attach(uint8_t pin) {
        attachedPin = pin;
        return pin;
    }

    void detach() {
        attachedPin = 255;
    }

    void write(int value) {
        angle = value;   // store angle only, no real PWM
    }

    int read() const {
        return angle;
    }

    bool attached() const {
        return attachedPin != 255;
    }

private:
    uint8_t attachedPin;
    int angle;
};

#endif
