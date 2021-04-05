# ELEC291 Project 2

------------

### Introduction:
For this project, we will design, build, program, and test a microcontroller-frequencymeter metal detector. The metal detector I am building for this
project relies on the inductance change that occurs when metal is placed close to a wire coil. If this inductor is part of an oscillator circuit, such change will produce a frequency variation. By measuring that frequency variation, it is possible to determine the type of metal that is near the sensor coil.

### Team Member:
Andi Li,&nbsp; &nbsp;  &nbsp;   &nbsp;  74700311\
Jerry Shao, &nbsp;  84982321\
Robin Yuan, 88011879\
Sean Fu, &nbsp;  &nbsp;   &nbsp;  25881012

------------
### Features List:
- [ ] Inductance and Capacitance Meter

- [x] Auto-adjustable-Backlight LCD

- [ ] Prototype Board

------------
### Update History:
**2021-04-03; 15:10:12; Saturday**
- The system can now play any given wav file that is 8-bit, 22050Hz, monotone and samller than 4MB
- A  header file is created to store all functions; the makefile is also modified to cope with the changes

**2021-04-04; 02:31:23; Sunday**
- Frequency detector circuit works

**2021-04-04; 03:15:40; Sunday**
- LCD is working

**2021-04-04; 15:28:27; Sunday**
- Auto-adjustable-Backlight LCD is working
- 555 timer-cirucit is added to measure capacitance

------------
### LCD Pin Assignments:

#define LCD_RS &nbsp; LATBbits.LATB13\
#define LCD_RW &nbsp;LATBbits.LATB12\
#define LCD_E  &nbsp; &nbsp; &nbsp;LATBbits.LATB10\
#define LCD_D4 &nbsp; LATAbits.LATA2\
#define LCD_D5 &nbsp; LATAbits.LATA3\
#define LCD_D6 &nbsp; LATBbits.LATB4\
#define LCD_D7 &nbsp; LATAbits.LATA4


### Breadboard Layout:
<img src="https://user-images.githubusercontent.com/68177491/113523138-d6e72580-955a-11eb-8dd0-a58f9840dbe7.jpg" width="521" height="391"/>

------------
### Matou Sakura is the best girl:
<img src="https://user-images.githubusercontent.com/68177491/113492318-6ae9bc00-948b-11eb-92c8-e79bb8f8cc76.jpg" width="640" height="905"/>
