#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PinMotor0_I 26
#define PinMotor1_D 23

int v0_I = 80;
int v1_D = 73;

int main(void){

	if (wiringPiSetup()==-1)
		exit(1);

	pinMode(PinMotor0_I, PWM_OUTPUT);
	pinMode(PinMotor1_D, PWM_OUTPUT);

	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(384);
	pwmSetRange(1024);

	//Avance
	pwmWrite(PinMotor0_I, v0_I);
	pwmWrite(PinMotor1_D, v1_D);
	printf("avanzando");
	sleep(15);

	//Parada
	pwmWrite(PinMotor1_D, 0);
	pwmWrite(PinMotor0_I, 0);

	return 0;
}