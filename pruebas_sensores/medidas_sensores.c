#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include <wiringPiSPI.h>
#include <unistd.h>

#define BASE 100
#define SPI_CHAN 0

int main(int argc, char *argv[]){

	int i=0;
	printf("wiringPiSPISetup RC=%d\n", wiringPiSPISetup(0,500000));
	mcp3004Setup(BASE,SPI_CHAN);
	while(1){
		printf("Canal %d: valor %4d", SPI_CHAN,  analogRead(BASE+0));
		printf("\n");
		printf("Canal %d: valor %4d", SPI_CHAN+1, analogRead(BASE+1
));
		printf("\n");
		usleep(500000);
	}
}
