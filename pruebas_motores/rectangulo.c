#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PinMotor0_I 26 // motor izquierdo conectado en el pwm0
#define PinMotor1_D 23 // motor derecho conectado en el pwm1

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

	sleep(15);

	//avanza 2 metros
	pwmWrite(PinMotor0_I, v0_I);
	pwmWrite(PinMotor1_D, v1_D);
	sleep(15);

	//gira 90 izquierda
	pwmWrite(PinMotor0_I, 0);
	pwmWrite(PinMotor1_D, v1_D);
	usleep(1700000);

	//avanza 1 metro
	pwmWrite(PinMotor0_I, v0_I);
	pwmWrite(PinMotor1_D, v1_D);
	usleep(7500000);

	//gira 90 izquierda
        pwmWrite(PinMotor0_I, 0);
        pwmWrite(PinMotor1_D, v1_D);
        usleep(1650000);

	//avanza 2 metros
        pwmWrite(PinMotor0_I, v0_I);
        pwmWrite(PinMotor1_D, v1_D);
	sleep(15);

	//gira 90 izquierda
        pwmWrite(PinMotor0_I, 0);
        pwmWrite(PinMotor1_D, v1_D);
        usleep(1700000);

	//avanza 1 metro
        pwmWrite(PinMotor0_I, v0_I);
        pwmWrite(PinMotor1_D, v1_D);
        usleep(7500000);

	//Parada
	pwmWrite(PinMotor1_D, 0);
	pwmWrite(PinMotor0_I, 0);

	return 0;
}
