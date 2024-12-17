#include <stdio.h>
#include <wiringPi.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.

#define	LED	0
#define BUTTON  3

int main (void)
{

  wiringPiSetup () ;
  pinMode (LED, OUTPUT) ;
  pinMode (BUTTON, INPUT);

  for (;;)
  {
    if (digitalRead(BUTTON)==0)
	digitalWrite(LED, HIGH);
    else
	digitalWrite(LED, LOW);
  }
  return 0 ;
}