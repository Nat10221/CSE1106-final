#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include <stdlib.h>

#define LOW 68
#define HIGH 76
#define PIN 17

int main()
{
    int TempReadings[50] = {};
    char Choice = 'Y';
    int Count = -1;

    gpioInitialise();
    gpioSetMode(PIN, PI_OUTPUT);

    while(Choice != 'N')
    {
        Count++;
        printf("Would you like to enter a temperature? Y/N ");
        getchar();
        scanf("%c", &Choice);
        
        if(Choice != 'N')
        {
            gpioWrite(PIN,0);
            printf("Please enter a temperature value ");
            scanf("%d", &TempReadings[Count]);
            //GETTING LIGHT
            if(TempReadings[Count] > HIGH || TempReadings[Count] < LOW)
            {
                gpioWrite(PIN,1);
                printf("WARNING - Your value is not in range!\n");
            }
            else
            {
                printf("NORMAL - Your value is in range!\n");
            }
        }
    }
    gpioWrite(PIN,0);
    //AFTER LOOP
    FILE* FH = NULL;
    FH = fopen("temps", "w+");
    if(FH == NULL)
    {
        printf("run away screaming");
       exit(0);
    }
    
    fprintf(FH, "    Temperature\t\tSystem Status\t\tWarning LED\n");
    for(int k = 0; k < Count; k++)
    {
        if(TempReadings[k] > HIGH || TempReadings[k] < LOW)
        {
            fprintf(FH, "    %11d\t\tWARNING\t\t\tON\n", TempReadings[k]);
        }
        else
        {
            fprintf(FH, "    %11d\t\tNORMAL\t\t\tOFF\n", TempReadings[k]);
        }
    } 
    int average = 0;
    int sum = 0;
    for(int j = 0; j < Count; j++) 
    {
        sum += TempReadings[j];  
    }
    
    average = sum/(Count);        
    fprintf(FH, "\n    The Average Temperature is %d", average);
    fclose(FH);
    
}
