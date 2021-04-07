// PIC32_Receiver.c:  This program implements a simple serial port
// communication protocol to program, verify, and read SPI flash memories.  Since
// the program was developed to store wav audio files, it also allows 
// for the playback of said audio.  It is assumed that the wav sampling rate is
// 22050Hz, 8-bit, mono.

#include <XC.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "project2.h"

#define True 1
#define nf_s_metal_min_bound 20
#define nf_l_metal_min_bound 200
#define f_s_metal_min_bound -2
#define f_l_metal_min_bound -40
#define C1 4.75e-9
#define C2 95.3e-9
#define R  993

#define  IR    PORTBbits.RB7

int state=0;
void __ISR(_EXTERNAL_0_VECTOR, IPL7AUTO) Ext0ISR(void)
{	
	int index=0;
	int address[16], command[8];
	
	T1CONCLR = 0x8000;
	T4CONCLR = 0x8000;
	T2CONCLR = 0x8000;
	IEC0bits.INT0IE = 0;

	if(state<5) (state)++;
    else state = 0;
    waitms(200);
     
    IFS0bits.INT0IF = 0;  
    IEC0bits.INT0IE = 1;
    
    T1CON = 0x8000;
    T4CON = 0x8000;
    T2CON = 0x8000;
	
	return;
}






int main()
{
    unsigned char c;
    unsigned int j, n;
    unsigned long start, nbytes;
    unsigned short crc;
	char buffer [16];
	long int count=0;
	int index;
	float f ,capacitance=0,inductance=0,f_ref=0,f_result=0,difference,CT;
  	float Temp_DHT11=0,Hum_DHT11=0;
	char percent='%';
	int i=0;
	Initiate();
	waitms(500);
	
	__builtin_disable_interrupts();   // disable interrupts
     
    INTCONbits.INT0EP = 0;   // interrupt triggers on negative edge    
    IPC0bits.INT0IP = 7;     // EXT0 priority 7
    IPC0bits.INT0IS = 0;     // EXT0 sub-priority 0
    IFS0bits.INT0IF = 0;     // clear the interrupt flag
    
    IEC0bits.INT0IE = 1;     // enable interrupt on INT0
   
    INTCONbits.MVEC = 1;     //  Enable the multi vector interrupts

    __builtin_enable_interrupts();   
	
	
	while(True)
	{		
	

        
		
		LCDprint2("WAITING...",1,1);
		LCDprint2("  ",3,1);
	
		switch(state)
		{
			case 0:
				__builtin_disable_interrupts(); 
				count=GetPeriod(100);
				f=1/((count*2.0)/(SYSCLK*100.0));
				f_ref=0;
				LCDprint("Frequency:",1,1);
				sprintf(buffer,"%.1f Hz",f);
				LCDprint(buffer,2,1);
			break;
			
			case 2:
					
				LCDprint("Capaciatnce:",1,1);
				LCDprint("",2,1);
				f_result=avg_frequency();
				capacitance=1.44/(6000.0*f)*1000000;		

				LCDprint("               F",2,1);
				LCDprint("              \xf9",2,0);
				sprintf(buffer,"%.3f",capacitance);
				LCDprint(buffer,2,0);
				waitms(500);
			break;
		
		
			case 3:
				
				LCDprint("Inductance:",1,1);
				LCDprint("",2,1);
				f_result=avg_frequency();
				sprintf(buffer,"%.1f mH",inductance);
				CT=C1*C2/(C1+C2);
				inductance=1.0/((4*3.14159265359*3.14159265359*f_result*f_result)*CT);
				inductance*=1000;
				sprintf(buffer,"%.3f mH",inductance);
				LCDprint(buffer,2,0);
				waitms(500);
			break;

			case 4:
			
				DHT11_Read(&Temp_DHT11, &Hum_DHT11);
				LCDprint("Temperature:",1,1);
				LCDprint("              C",2,1);
				sprintf(buffer,"Current: %.1f\xdf",Temp_DHT11);  
				LCDprint(buffer,2,0);
				waitms(1000);
			break;
			
			case 5:
				LCDprint("Humidity:",1,1);
				sprintf(buffer,"Current: %.1f%c",Hum_DHT11,percent);
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
								
							Start_Playback(0x00c158,0x010f89-0x00c158);
							while(play_flag);//Small
							Start_Playback(0x2d,0x2f91-0x2d);
							while(play_flag);//Non
							Start_Playback(0x002f91,0x00799e -0x002f91);
							while(play_flag);//Ferrous
							Start_Playback(0x00799e,0x00c158-0x00799e);
							while(play_flag);//Metal
							Start_Playback(0x01e102,0x022cd9-0x01e102);
							while(play_flag);//Found
						}
						else
						{
							LCDprint("    LARGE",2,1);
							
							Start_Playback(0x015ea6,0x01a46f-0x015ea6);
							while(play_flag);//Large
							Start_Playback(0x2d,0x2f91-0x2d);
							while(play_flag);//Non
							Start_Playback(0x002f91,0x00799e -0x002f91);
							while(play_flag);//Ferrous
							Start_Playback(0x00799e,0x00c158-0x00799e);
							while(play_flag);//Metal
							Start_Playback(0x01e102,0x022cd9-0x01e102);
							while(play_flag);//Found
						}
					}
					else
					{
						if(difference>f_s_metal_min_bound)
						{
							LCDprint("No Metal Found",1,1);
							
							Start_Playback(0x01a46f,0x01e102-0x01a46f);
							while(play_flag);//No
							Start_Playback(0x00799e,0x00c158-0x00799e);
							while(play_flag);//Metal
							Start_Playback(0x01e102,0x022cd9-0x01e102);
							while(play_flag);//Found
						}
						else	
						{	
							LCDprint("Ferrous Metal",1,1);
							
							if(difference>f_l_metal_min_bound)
							{
								LCDprint("    SMALL",2,1);
								
								Start_Playback(0x00c158,0x010f89-0x00c158);
								while(play_flag);//Small
								Start_Playback(0x002f91,0x00799e -0x002f91);
								while(play_flag);//Ferrous
								Start_Playback(0x00799e,0x00c158-0x00799e);
								while(play_flag);//Metal
								Start_Playback(0x01e102,0x022cd9-0x01e102);
								while(play_flag);//Found
							}
							else
							{
								LCDprint("    LARGE",2,1);
								Start_Playback(0x015ea6,0x01a46f-0x015ea6);
								while(play_flag);//Large
								Start_Playback(0x002f91,0x00799e -0x002f91);
								while(play_flag);//Ferrous
								Start_Playback(0x00799e,0x00c158-0x00799e);
								while(play_flag);//Metal
								Start_Playback(0x01e102,0x022cd9-0x01e102);
								while(play_flag);//Found
							
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