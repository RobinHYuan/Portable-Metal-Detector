// PIC32_Receiver.c:  This program implements a simple serial port
// communication protocol to program, verify, and read SPI flash memories.  Since
// the program was developed to store wav audio files, it also allows 
// for the playback of said audio.  It is assumed that the wav sampling rate is
// 22050Hz, 8-bit, mono.

#include <XC.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>
#include "project2.h"

#define True 1

int main()
{
    unsigned char c;
    unsigned int j, n;
    unsigned long start, nbytes;
    unsigned short crc;
	char buffer [16];
	long int count;
	int state =0;
	float f ,capacitance=0,inductance=0;

	Initiate();
	
	while(True)
	{	
		count=GetPeriod(100);
		f=1/((count*2.0)/(SYSCLK*100.0));
		
		switch(state)
		{
			case 0:
				LCDprint("Frequency:",1,1);
				sprintf(buffer,"%.1f Hz",f);
				LCDprint(buffer,2,1);
			break;
			
			case 1:
				LCDprint("Capaciatnce:",1,1);
				sprintf(buffer,"%.1f pF",capacitance);
				LCDprint(buffer,2,1);
			break;
		
		
			case 2:
				LCDprint("Inductance:",1,1);
				sprintf(buffer,"%.1f mH",inductance);
				LCDprint(buffer,2,1);
			break;
			
			case 3:
				LCDprint("PRESS SW2 TO",1,1);
				LCDprint("DETECT METAL",2,1);
			break;
			
		}

  		SW1_Check(&state);
		waitms(200);
 
		
    }  
 
    return 1;
}