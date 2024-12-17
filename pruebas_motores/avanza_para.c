#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>
#include <stdbool.h>

#define PinMotor0_I 26
#define PinMotor1_D 23
#define BASE 100
#define SPI_CHAN 0


int v0_I = 80;
int v1_D = 73;

int main(void){

	if (wiringPiSetup()==-1)
		exit(1);

	printf("wiringPiSPISetup RC=%d\n", wiringPiSPISetup(0, 500000));
	mcp3004Setup(BASE, SPI_CHAN);

	pinMode(PinMotor0_I, PWM_OUTPUT);
	pinMode(PinMotor1_D, PWM_OUTPUT);

	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(384);
	pwmSetRange(1024);

	pwmWrite(PinMotor0_I, v0_I);
        pwmWrite(PinMotor1_D, v1_D);


	//Avance
	bool seguir=true;
	while(seguir){
		if(analogRead(BASE+2)<500 || analogRead(BASE+3)<480)
			seguir = true;
		else
			seguir = false;

		usleep(50000);
	}

	//Parada
	pwmWrite(PinMotor1_D, 0);
	pwmWrite(PinMotor0_I, 0);

	return 0;
}
