#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_LED_PINS 7
#define DELAY_AMOUNT 5
#define RANDOM_SEED 4 //IEEE-vetted standard random number

int pins[] = {0, 1, 2, 3, 4, 5, 6};
unsigned int steps[NUM_LED_PINS];


int setupPin(int pin);
void setSteps();
void setAllPins(unsigned int step);

int main() {
    //setup()
    wiringPiSetup();
    for (int i = 0; i < NUM_LED_PINS; i++) {
        setupPin(pins[i]);
    }
    srand(RANDOM_SEED);
    fprintf(stderr, "Set random to be %i\n", RANDOM_SEED);
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
    for (int i = 0; i < NUM_LED_PINS; i++) {
        steps[i] = rand() % 202U;
        fprintf(stderr, "Pin %i has a step of %u\n", pins[i], steps[i]);
        //steps[i] = 30 * i; for debugging
    }
}

void setAllPins(unsigned int step) {
    unsigned int numIter;
    for (int i = 0; i < NUM_LED_PINS; i++) {
        numIter = (step + steps[i]) % 202U;
        if (numIter < 101) { //going up
            softPwmWrite(pins[i], numIter);
        }
        else {  //going down
            softPwmWrite(pins[i], 201 - numIter);
        }
    }
}
