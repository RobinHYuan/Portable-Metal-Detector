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


int main()
{
    unsigned char c;
    unsigned int j, n;
    unsigned long start, nbytes;
    unsigned short crc;

	DDPCON = 0;
	CFGCON = 0;

	TRISBbits.TRISB6 = 0;
	LATBbits.LATB6 = 0;	
	INTCONbits.MVEC = 1;
	
	Init_pwm(); // pwm output used to implement DAC
	SetupTimer1(); // The ISR for this timer playsback the sound
    UART2Configure(115200);  // Configure UART2 for a baud rate of 115200
    config_SPI(); // Configure hardware SPI module
 
	playcnt=0;
	play_flag=0;
	SET_CS; // Disable 25Q32 SPI flash memory
      
	while(1)
	{
		c=uart_getc();
		if(c=='#')
		{
			playcnt=0;
			play_flag=0;
			SET_CS; // Disable 25Q32 SPI flash memory

			c=uart_getc();
			switch(c)
			{
				case '0': // Identify command
				    CLR_CS; // Enable 25Q32 SPI flash memory.
				    SPIWrite(READ_DEVICE_ID);
				    c=SPIWrite((unsigned char)(0x00));
				    uart_putc(c);
				    c=SPIWrite((unsigned char)(0x00));
				    uart_putc(c);
				    c=SPIWrite((unsigned char)(0x00));
				    uart_putc(c);
				    SET_CS; // Disable 25Q32 SPI flash memory
				break;

				case '1': // Erase whole flash (takes a long time)
					Enable_Write();
				    CLR_CS; // Enable 25Q32 SPI flash memory.
				    SPIWrite(ERASE_ALL);
				    SET_CS; // Disable 25Q32 SPI flash memory
				    Check_WIP();
				    uart_putc(0x01);
				break;
				
				case '2': // Load flash page (256 bytes or less)
					Enable_Write();
				    CLR_CS; // Enable 25Q32 SPI flash memory.
				    SPIWrite(WRITE_BYTES);
				    c=uart_getc(); // Address bits 16 to 23
				    SPIWrite(c);
				    c=uart_getc(); // Address bits 8 to 15
				    SPIWrite(c);
				    c=uart_getc(); // Address bits 0 to 7
				    SPIWrite(c);
				    n=uart_getc(); // Number of bytes to write
				    if(n==0) n=256;
				    for(j=0; j<n; j++)
				    {
				    	c=uart_getc();
				    	SPIWrite(c);
				    }
				    SET_CS; // Disable 25Q32 SPI flash memory
				    Check_WIP();
				    uart_putc(0x01);
				break;
				
				case '3': // Read flash bytes (256 bytes or less)
				    CLR_CS; // Enable 25Q32 SPI flash memory.
				    SPIWrite(READ_BYTES);
				    c=uart_getc(); // Address bits 16 to 23
				    SPIWrite(c);
				    c=uart_getc(); // Address bits 8 to 15
				    SPIWrite(c);
				    c=uart_getc(); // Address bits 0 to 7
				    SPIWrite(c);
				    n=uart_getc(); // Number of bytes to write
				    if(n==0) n=256;
				    for(j=0; j<n; j++)
				    {
				    	c=SPIWrite(0x55);
				    	uart_putc(c);
				    }
				    SET_CS; // Disable 25Q32 SPI flash memory
				break;
				
				case '4': // Playback a portion of the stored wav file
					get_ulong(&start); // Get the start position
					get_ulong(&nbytes); // Get the number of bytes to playback
					Start_Playback(start, nbytes);
				break;
				
				case '5': ; // Calculate and send CRC-16 of ISP flash memory from zero to the 24-bit passed value.
					get_ulong(&nbytes); // Get how many bytes to use in calculation
				
					crc=0;
				    CLR_CS; // Enable 25Q32 SPI flash memory.
				    SPIWrite(READ_BYTES);
				    SPIWrite(0x00); // Address bits 16 to 23
				    SPIWrite(0x00); // Address bits 8 to 1
				    SPIWrite(0x00); // Address bits 0 to 7
				    
					for(start=0; start<nbytes; start++)
					{
						c=SPIWrite(0x00);
						crc=crc16_ccitt(c, crc); // Calculate CRC here
					}
				    SET_CS; // Disable 25Q32 SPI flash memory

					uart_putc(crc/0x100); // Send high byte of CRC
					uart_putc(crc%0x100); // Send low byte of CRC
				break;

				case '6': // Fill flash page (256 bytes or less).
					Enable_Write();
				    CLR_CS; // Enable 25Q32 SPI flash memory.
				    SPIWrite(WRITE_BYTES);
				    c=uart_getc(); // Address bits 16 to 23
				    SPIWrite(c);
				    c=uart_getc(); // Address bits 8 to 15
				    SPIWrite(c);
				    c=uart_getc(); // Address bits 0 to 7
				    SPIWrite(c);
				    c=uart_getc(); // byte to copy to page
				    for(j=0; j<256; j++)
				    {
				    	SPIWrite(c);
				    }
				    SET_CS; // Disable 25Q32 SPI flash memory
				    Check_WIP();
				    uart_putc(0x01);
				break;
			}
		}
    }  
 
    return 1;
}