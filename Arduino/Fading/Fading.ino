#include<stdarg.h>
#define NUM_LED_PINS 6
#define DELAY_AMOUNT 5
#define RANDOM_SEED 4 //IEEE-vetted standard random number
int pins[] = {3,5,6,9,10,11};
unsigned int steps[NUM_LED_PINS];
unsigned int step = 0;


//quick thing to emulate printf behaviour
void p(char *fmt, ... ){
        char tmp[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        Serial.print(tmp);
}
void setup()  { 
 srand(RANDOM_SEED);
 for(int i=0;i<NUM_LED_PINS;i++){
   pinMode(pins[i], OUTPUT);
 }
 Serial.begin(9600);
 Serial.println("Set random seed: " + RANDOM_SEED);
 setSteps();
 step = 0; 
} 

void loop()  {
  step++;
  setAllPins(step);
  delay(DELAY_AMOUNT);
}


void setSteps() {
    for (int i = 0; i < NUM_LED_PINS; i++) {
        steps[i] = rand() % 512U;
        p("Pin %i has a step of %u\n", pins[i], steps[i]);
        //steps[i] = 30 * i; for debugging
    }
}

void setAllPins(unsigned int step) {
    unsigned int numIter;
    for (int i = 0; i < NUM_LED_PINS; i++) {
        numIter = (step + steps[i]) % 512U;
        if (numIter < 256) { //going up
            analogWrite(pins[i], numIter);
        }
        else {  //going down
            analogWrite(pins[i], 512 - numIter);
        }
    }
}
