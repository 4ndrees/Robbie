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
#define LED0 0

int v0_I = 80;
int v1_D = 73;
int estado = 1;

int main(void){

	if (wiringPiSetup()==-1)
		exit(1);

	pinMode(LED0, OUTPUT);

	printf("wiringPiSPISetup RC=%d\n", wiringPiSPISetup(0, 500000));
	mcp3004Setup(BASE, SPI_CHAN);

	pinMode(PinMotor0_I, PWM_OUTPUT);
	pinMode(PinMotor1_D, PWM_OUTPUT);

	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(384);
	pwmSetRange(1024);

	while(1){

		int sensorDr = analogRead(BASE+3);
		int sensorIz = analogRead(BASE+2);
		int sensorAbajoDr = analogRead(BASE+1);
		int sensorAbajoIz = analogRead(BASE+0);

		if (sensorAbajoIz > 20 || sensorAbajoDr > 20){
			digitalWrite(LED0, LOW);
			estado = 1;
		} else if (sensorIz > 250 || sensorDr > 250){
			digitalWrite(LED0, HIGH);
			estado = 2;
		}else{
			digitalWrite(LED0, LOW);
			estado = 3;
		}

		switch(estado){
			case 1:
				pwmWrite(PinMotor0_I, 70);
				pwmWrite(PinMotor1_D, 80);
				usleep(1000000);
				pwmWrite(PinMotor0_I, v0_I);
				pwmWrite(PinMotor1_D, 0);
				usleep(2800000);
				break;
			case 2:
				pwmWrite(PinMotor0_I, v0_I);
				pwmWrite(PinMotor1_D, v1_D);
				usleep(50000);
				break;
			case 3:
				pwmWrite(PinMotor0_I, 0);
				pwmWrite(PinMotor1_D, v1_D);

				int n = 1600000;
				while(n){
					if (analogRead(BASE+2) > 250 || analogRead(BASE+3) > 250){
						digitalWrite(LED0, HIGH);
						estado = 2;
						break;
					}
					n-=100;
					usleep(100);
				}

				if (estado == 2) break;

				pwmWrite(PinMotor0_I, v0_I);
				pwmWrite(PinMotor1_D, 0);

				n = 2800000;
				while(n){
					if (analogRead(BASE+2) > 250 || analogRead(BASE+3) > 250){
						digitalWrite(LED0, HIGH);
						estado=2;
						break;
					}
					n-=100;
					usleep(100);
				}

				if (estado == 2) break;
				
				pwmWrite(PinMotor0_I, 0);
				pwmWrite(PinMotor1_D, v1_D);
				usleep(1600000);

				pwmWrite(PinMotor0_I, v0_I);
				pwmWrite(PinMotor1_D, v1_D);
				usleep(500000);

				break;
			default:
				pwmWrite(PinMotor0_I, 0);
				pwmWrite(PinMotor1_D, 0);
				break;
		}
	}

	//Parada
	pwmWrite(PinMotor1_D, 0);
	pwmWrite(PinMotor0_I, 0);

	return 0;
}
