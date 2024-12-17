#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PinMotor0 26
#define PinMotor1 26

int main(void){

	if (wiringPiSetup()==-1)
		exit(1);

	pinMode(PinMotor0, PWM_OUTPUT);

	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(384);
	pwmSetRange(1024);

	for (int i = 70; i < 80; i++) {
		printf("Va por el %d\n", i);
		pwmWrite(PinMotor0, i);
		sleep(2);
	}
	pwmWrite(PinMotor0, 0);

	return 0;
}
