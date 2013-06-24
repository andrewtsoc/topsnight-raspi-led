#define NUM_LED_PINS 6
#define MIN_FADE_TIME 5
#define RANGE_FADE_TIME 1
#define MIN_WAIT 6
#define RANGE_WAIT 12
#define RANDOM_SEED 4

int pins[] = {3,5,6,9,10,11};
boolean isOn[NUM_LED_PINS];
boolean isBeingChanged[NUM_LED_PINS];

void setup()  { 
 srand(RANDOM_SEED);
 for (int i=1; i < 14; i++) {
   pinMode(i, OUTPUT);
   analogWrite(i, LOW);
 }
 for(int i=0;i<NUM_LED_PINS;i++){
   isOn[i]=rand()%2;
   analogWrite(pins[i],(isOn[i])?255:0); //initialize states
 }
 delay(3000);
}

void switchStates(){
  int delayTime = (rand() % RANGE_FADE_TIME + MIN_FADE_TIME);
  for(int fadeValue = 0 ; fadeValue < 256; fadeValue +=5) { //fade
    for(int i=0;i<NUM_LED_PINS;i++){ //loop over all pins
        if (isBeingChanged[i]){ //change only marked pins
          int pin = pins[i];
          analogWrite(pin, (isOn[i])? 255-fadeValue : fadeValue); //fade on or off 
        }
    }
    delay(delayTime); 
  }
  for(int i=0;i<NUM_LED_PINS;i++)
    isOn[i] = isBeingChanged[i] != isOn[i]; //xor
}

void markChanges(){
  for(int i=0;i<NUM_LED_PINS;i++)
    isBeingChanged[i] = (rand()%4 == 0); 
}

void loop()  {
  markChanges();
  switchStates();
  delay(rand()%RANGE_WAIT + MIN_WAIT); //delay between changes
}


