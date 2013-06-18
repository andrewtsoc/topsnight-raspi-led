//adjust these values as needed
const int numPins = 6;
const int minFadeTime = 500;
const int rangeFadeTime = 500;
const int minWait = 500;
const int rangeWait = 500;
const int seed = 1337;

int pins[numPins] = {3,5,6,9,10,11};
boolean isOn[numPins];
boolean isBeingChanged[numPins];

void setup()  { 
 srand(seed);
 for(int i=0;i<numPins;i++){
   isOn[i]=rand()%2;
   analogWrite(pins[i],(isOn[i])?255:0); //initialize states
 }
 delay(3000);
}

void switchStates(){
  int delayTime = (rand() % rangeFadeTime + minFadeTime)/51;
  for(int fadeValue = 0 ; fadeValue < 256; fadeValue +=5) { //fade
    for(int i=0;i<numPins;i++){ //loop over all pins
        if (isBeingChanged[i]){ //change only marked pins
          int pin = pins[i];
          analogWrite(pin, (isOn[i])? 255-fadeValue : fadeValue); //fade on or off 
        }
    }
    delay(delayTime); 
  }
  for(int i=0;i<numPins;i++)
    isOn[i] = !isBeingChanged[i] != !isOn[i]; //xor
}

void markChanges(){
  for(int i=0;i<numPins;i++)
    isBeingChanged[i] = (rand()%4 == 0); 
}

void loop()  {
  markChanges();
  switchStates();
  delay(rand()%rangeWait + minWait); //delay between changes
}


