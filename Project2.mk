SHELL=cmd
CC = xc32-gcc
OBJCPY = xc32-bin2hex
ARCH = -mprocessor=32MX170F256B
OBJ = Project2.o
PORTN=$(shell type COMPORT.inc)
HEADER = include/Project2.h

Project2.elf: $(OBJ)
	$(CC) $(ARCH) -o Project2.elf Project2.o -mips16 -DXPRJ_default=default \
		-legacy-libc -Wl,-Map=Project2.map
	$(OBJCPY) Project2.elf
	@echo Success!
	
Project2.o: Project2.c
	$(CC) -g -x c -mips16 -Os -c $(ARCH) -MMD -o Project2.o Project2.c \
		-DXPRJ_default=default -legacy-libc

clean:
	@del *.o *.elf *.hex *.d *.map 2>NUL

LoadFlash:
	@Taskkill /IM putty.exe /F 2>NUL | wait 500
	pro32 -p Project2.hex

putty:
	@Taskkill /IM putty.exe /F 2>NUL | wait 500
	cmd /c start c:\putty\putty.exe -serial $(PORTN) -sercfg 115200,8,n,1,N -v

dummy: Project2.hex Project2.map

explorer:
	@explorer .
