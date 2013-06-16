#include <wiringPi.h>
int main() {
    wiringPiSetup();
    pinMode(1, OUTPUT);
    for (;;) {
        digitalWrite(1, HIGH); delay(500);
        digitalWrite(1, LOW); delay(500);
    }
}
