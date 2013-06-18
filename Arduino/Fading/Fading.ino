const int numPins = 6;
const int fadeTime = 1000;
const int minWait = 1000;
const int rangeWait = 2000;
int pins[numPins] = {3,5,6,9,10,11};
boolean isOn[numPins];
void setup()  { 
 srand(1337);
 for(int i=0;i<numPins;i++)
   isOn[i]=rand()%2;
} 
void switchState(int pin){
  pin %= numPins;
  if (!isOn[pin])
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
      analogWrite(pins[pin], fadeValue);          
      delay(fadeTime/256);                            
    } 
  else
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
      analogWrite(pins[pin], fadeValue);             
      delay(fadeTime/256);                            
    } 
  isOn[pin] = !isOn[pin];
}
void loop()  {
  switchState(rand());
  delay(rand()%rangeWait + minWait);
}


