#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>

#define NUM_PINS 7
#define DELAY_AMOUNT 5

int pins[] = {0, 1, 2, 3, 4, 5, 6};
unsigned int steps[NUM_PINS];


int setupPin(int pin);
void setSteps();
void setAllPins(int step);

int main() {
    //setup()
    wiringPiSetup();
    for (int i = 0; i < NUM_PINS; i++) {
        setupPin(pins[i]);
    }
    srand(0);
    setSteps();
    unsigned int step = 0;

    //loop()
    for (;;) {
        step++; // we're allowed to do this because unsigned ints wrap
        setAllPins(step);
        delay(DELAY_AMOUNT);
    }

    return 0;
}

int setupPin(int pin) {
    return softPwmCreate(pin, 0, 100);
}

void setSteps() {
    for (int i = 0; i < NUM_PINS; i++) {
        steps[i] = rand() % 202;
    }
}

void setAllPins(int step) {
    unsigned int numIter;
    for (int i = 0; i < NUM_PINS; i++) {
        numIter = (step - steps[i]) % 202;
        if (numIter < 101) { //going up
            softPwmWrite(pins[i], numIter);
        }
        else {  //going down
            softPwmWrite(pins[i], 201 - numIter);
        }
    }
}
