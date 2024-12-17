#include <stdio.h>
#include <wiringPi.h>

#define LED	0
#define CNY 	3

int main(int argc, char *argv[]){ 

	wiringPiSetup();
	pinMode (CNY, INPUT);
	pinMode (LED, OUTPUT);

	for(;;){
		if (digitalRead(CNY))
			digitalWrite(LED, HIGH);
		else
			digitalWrite(LED, LOW);
	}

	return 0;
}
