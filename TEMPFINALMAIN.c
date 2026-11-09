#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>

#define LOW 68
#define HIGH 76
#define PIN 17

int main()
{
    int TempReadings[3] = {};
    char Choice = 'N';
    int Count = -1;

    gpioInitialize();
    gpioSetMode(PIN, PI_OUTPUT);

    while(Choice != 'N')
    {
        Count++;
        printf("Would you like to enter a temperature? Y/N ");
        scanf("%c", Choice);
        
        if(Choice != 'N')
        {
            printf("Please enter a temperature value or Q to quit ")
            scanf("%d", TempReadings[Count])
            //GETTING LIGHT
            if(TempReadings[Count] > HIGH || TempReadings[Count] < LOW)
            {
                gpioWrite(PIN,1);
            }
        }
    }
    
}