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
int estado = 1;

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

	bool parar=false;
	//Avance
	while(!parar){
		switch(estado){
			//hacia alante
			case 1:
				if(analogRead(BASE+0)>10){
					estado = 2;
				}
				if(analogRead(BASE+1)>20){
					estado = 3;
				}
				if (analogRead(BASE+0)>10 && analogRead(BASE+1)>20)
					parar=true;
				break;
			case 2:
				if(analogRead(BASE+0)>10 && analogRead(BASE+1)>20){
					estado = 4;
				}
				if(analogRead(BASE+0)<10 && analogRead(BASE+1)<20){
					estado = 1;
				}
				break;
			case 3:
				if(analogRead(BASE+0)>10 && analogRead(BASE+1)>20){
					estado = 5;
				}
				if(analogRead(BASE+0)<10 && analogRead(BASE+1)<20){
					estado = 1;
				}
				break;
			case 4:
				if (analogRead(BASE+0) < 10 && analogRead(BASE+1)<20){
					estado = 1;
				}
				break;
			case 5:
				if(analogRead(BASE+0) <10 && analogRead(BASE+1)<20){
					estado = 1;
				}
				break;
		}

		//Actuacion sobre los motores
		switch(estado){
			case 1:
				pwmWrite(PinMotor0_I, v0_I);
				pwmWrite(PinMotor1_D, v1_D);
				break;
			case 2:
				pwmWrite(PinMotor0_I, v0_I);
				pwmWrite(PinMotor1_D, v1_D+1);
				break;
			case 3:
				pwmWrite(PinMotor0_I, v0_I-1);
				pwmWrite(PinMotor1_D, v1_D);
				break;
			case 4:
				pwmWrite(PinMotor0_I, v0_I);
				pwmWrite(PinMotor1_D, 0);
				break;
			case 5:
				pwmWrite(PinMotor0_I, 0);
				pwmWrite(PinMotor1_D, v1_D);
				break;
		}

		usleep(5000);
	}

	//Parada
	pwmWrite(PinMotor1_D, 0);
	pwmWrite(PinMotor0_I, 0);

	return 0;
}
