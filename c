#include <wiringPi.h>  
#include <stdio.h>  
#include <sys/time.h>  

#define  Trig    4  
#define  Echo    5  
#define  LedPin  0


void ultraInit(void)  
{  
	pinMode(Echo, INPUT);  
	pinMode(Trig, OUTPUT);  

}  

float disMeasure(void)  
{  
	//Send trig pulse
        digitalWrite(Trig, HIGH);
        delayMicroseconds(20);
        digitalWrite(Trig, LOW);
 
        //Wait for echo start
        while(digitalRead(Echo) == LOW);
 
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(Echo) == HIGH);
        long travelTime = micros() - startTime;
 
        //Get distance in cm
        int distance = travelTime / 58;
 
        return distance;  
}  

int main(void)  
{  
		if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	pinMode(LedPin, OUTPUT);



	float dis;  

	if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen  
		printf("setup wiringPi failed !\n");  
		return -1;   
	}  

	ultraInit();  

	while(1){  
		dis = disMeasure();
		digitalWrite(LedPin, HIGH);  //led off  
		if (dis>50)
		{ 
		digitalWrite(LedPin, LOW);   //led on
		//delay(20);
	    } 
		printf("Distance = %0.2f cm\n",dis);  
		delay(1000);  
	}  

	return 0;  
}  
