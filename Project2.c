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
#define nf_s_metal_min_bound 20
#define nf_l_metal_min_bound 200
#define f_s_metal_min_bound -2
#define f_l_metal_min_bound -40

int main()
{
    unsigned char c;
    unsigned int j, n;
    unsigned long start, nbytes;
    unsigned short crc;
	char buffer [16];
	long int count;
	int state =0,index;
	float f ,capacitance=0,inductance=0,f_ref=0,f_result=0,difference;
	float f_initial [100], f_end[100];

	Initiate();
	
	while(True)
	{	
		count=GetPeriod(100);
		f=1/((count*2.0)/(SYSCLK*100.0));
		float f_ref=0;
		switch(state)
		{
			case 0:
				LCDprint("Frequency:",1,1);
				sprintf(buffer,"%.1f Hz",f);
				LCDprint(buffer,2,1);
			break;
			
			case 2:
				LCDprint("Capaciatnce:",1,1);
				sprintf(buffer,"%.1f pF",capacitance);
				LCDprint(buffer,2,1);
			break;
		
		
			case 3:
				LCDprint("Inductance:",1,1);
				sprintf(buffer,"%.1f mH",inductance);
				LCDprint(buffer,2,1);
			break;
			
			case 1:
				LCDprint("  PRESS SW2 TO",1,1);
				LCDprint("  DETECT METAL",2,1);
				if (SW2_Check())
				{	
					while(!SW2_Check())	
					{
						LCDprint("     Coil ",1,1);
						LCDprint("Away From Metal",2,1);
						waitms(1200);
						LCDprint("  PRESS SW2 TO",1,1);
						LCDprint("    CALIBRATE",2,1);
						waitms(1200);
					}	

					LCDprint("  Calibrating",1,1);
					LCDprint("",2,1);
					
					index=0; f_ref=0;
					while( index<99 )
					{
						count=GetPeriod(100);
						f=1/((count*2.0)/(SYSCLK*100.0));
						f_initial[index] = f;
						waitms(40);
						f_ref+=f;
						index++;
					}
					f_ref=f_ref/100.0;
					
					LCDprint("Reference:",1,1);
					sprintf(buffer,"%.1f Hz",f_ref);
					LCDprint(buffer,2,1);
					waitms(3000);
					
					while(!SW2_Check())	
					{
					
						LCDprint("PLACE THE METAL",1,1);
						LCDprint("INSIDE THE COIL",2,1);
						waitms(2000);
						LCDprint("  PRESS SW2 TO",1,1);
						LCDprint("    CONTINUE",2,1);
						waitms(2000);
					}	
					
					LCDprint("Measuring...",1,1);
					LCDprint("",2,1);
					
					index=0; f_result=0;
					while( index<99 )
					{
						count=GetPeriod(100);
						f=1/((count*2.0)/(SYSCLK*100.0));
						f_end[index] = f;
						waitms(40);
						f_result+=f;
						index++;
					}
					f_result=f_result/100.0;
					
					sprintf(buffer,"Result:%.0f Hz",f_result);
					LCDprint(buffer,1,1);
					sprintf(buffer,"Ref:%.0f Hz",f_ref);
					LCDprint(buffer,2,1);
					waitms(2000);
					
					difference=f_result-f_ref;
					
					if(difference> nf_s_metal_min_bound)
					{
						LCDprint("NonFerrous Metal",1,1);
						if(difference<nf_l_metal_min_bound)
						{			
							LCDprint("    SMALL",2,1);
						}
						else
						{
							LCDprint("    LARGE",2,1);
						}
					}
					else
					{
						if(difference>f_s_metal_min_bound)
						{
							LCDprint("No Metal Found",1,1);
						}
						else
						{	LCDprint("Ferrous Metal",1,1);
							if(difference>f_l_metal_min_bound)
							{
								LCDprint("    SMALL",2,1);
							}
							else
							{
								LCDprint("    LARGE",2,1);
							
							}
						}
				
					}
					while(1);
				}

			break;
			
		}

  		SW1_Check(&state);
		waitms(200);
 
		
    }  
 
    return 1;
}