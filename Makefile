CFLAGS= -Wall -std=c99
LFLAGS= -lwiringPi

all: blink blinkall fadeall

blink:
	gcc $(CFLAGS) -o blink blink.c $(LFLAGS)

blinkall:
	gcc $(CFLAGS) -o blinkall blinkall.c $(LFLAGS)

fadeall:
	gcc $(CFLAGS) -o fadeall fadeall.c $(LFLAGS)

clean:
	rm blink blinkall fadeall

again: clean blink blinkall fadeall
