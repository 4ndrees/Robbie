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

	sleep(10);

	//gira 90 izquierda
	pwmWrite(PinMotor0_I, 0);
	pwmWrite(PinMotor1_D, v1_D);
	usleep(1500000);

	//para 1 segundo
	pwmWrite(PinMotor0_I, 0);
	pwmWrite(PinMotor1_D, 0);
	sleep(1);

	//gira 180 derecha (90 volver al centro + 90 girar derecha)
	pwmWrite(PinMotor0_I, v0_I);
	pwmWrite(PinMotor1_D, 0);
	usleep(3000000);

	//Parada
	pwmWrite(PinMotor1_D, 0);
	pwmWrite(PinMotor0_I, 0);

	return 0;
}
