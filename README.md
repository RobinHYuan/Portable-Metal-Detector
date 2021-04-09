# ELEC291 Project 2

------------

### Introduction:
For this project, we will design, build, program, and test a microcontroller-frequencymeter metal detector. The metal detector we are building for this
project relies on the inductance change that occurs when metal is placed close to a wire coil. If this inductor is part of an oscillator circuit, such change will produce a frequency variation. By measuring that frequency variation, it is possible to determine the type of metal that is near the sensor coil.

### Team Member:
Andi Li,&nbsp; &nbsp;  &nbsp;   &nbsp;  74700311\
Jerry Shao, &nbsp;  84982321\
Robin Yuan, 88011879\
Sean Fu, &nbsp;  &nbsp;   &nbsp;  25881012

------------

### Features List:
- [x] Inductance and Capacitance Meter

- [x] Auto-adjustable-Backlight LCD

- [x] DHT11 Temperature Sensor

- [x] Dual LCD Display Including a 16x4 LCD

- [x] IR Remote Control and Pushbutton COntrol

- [x] User-friendly Menu Nevigation System 

- [x] Prototype Board

### Preview:

Breadboard: https://drive.google.com/file/d/1-iZb56TVcO2iSUi0TGHbikE_OU9lY_tn/view?usp=sharing\
Prototype Board: https://drive.google.com/file/d/1-kGT7yI_gWh4g1TP4VJDG7c39W3_VPlW/view?usp=sharing

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

**2021-04-05 ; 16:09:34; Monday**
- Push-button-detecting function is added
- The menu nevigating system is working 

**2021-04-05 ; 22:02:46; Monday**
- It can now detect if there is any small/large and ferrous/non-ferrous metal inside the coil

**2021-04-06 ; 01:55:51; Tuesday**
- Voice output system is working
- Inductance and capacitance meter is added


**2021-04-07 ; 02:59:08; Wednesday**
- An external ISR coded to drive the IR receiver
- Second LCD display is added
- DHT11 temperature and humidity sensor is working

**2021-04-08 ; 00:23:29; Thurdsay
- We can nevigate the menu using an IR remote controller instead of pushbuttons
- Menu can diplay the current task
- 
 **2021-04-09 ; 23:48:52; Thurdsay**
- Prototype board is working

------------
### Pin Assignments:

#define LCD_RS&nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; LATBbits.LATB13\
#define LCD_RW&nbsp; &nbsp; &nbsp; &nbsp; LATBbits.LATB12\
#define LCD_E &nbsp;  &nbsp;  &nbsp;  &nbsp; &nbsp;&nbsp; LATBbits.LATB10\
#define LCD_E2 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;LATBbits.LATB9\
#define LCD_D4&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;LATAbits.LATA2\
#define LCD_D5&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;LATAbits.LATA3\
#define LCD_D6&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;LATBbits.LATB4\
#define LCD_D7&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;LATAbits.LATA4\
#define SW1&nbsp;  &nbsp;  &nbsp;  &nbsp;    &nbsp;  &nbsp; &nbsp;  PORTBbits.RB15\
#define SW2&nbsp;  &nbsp;  &nbsp;  &nbsp;    &nbsp;  &nbsp; &nbsp;  PORTBbits.RB2\
#define DHT11_OUT&nbsp;&nbsp;LATBbits.LATB3\
#define DHT11 &nbsp;   &nbsp;  &nbsp; &nbsp;  &nbsp;  PORTBbits.RB3


### Schematic：
<img src="https://user-images.githubusercontent.com/68177491/114123614-7bdd6780-98a7-11eb-933a-7ecb3f500da2.jpg" width="827" height="1089"/>
<img src="https://user-images.githubusercontent.com/68177491/114123439-2608bf80-98a7-11eb-91bd-a6ff7104265c.jpg" width="800" height="600"/>

### Breadboard Layout:
<img src="https://user-images.githubusercontent.com/68177491/113850695-943a6e80-974f-11eb-941b-8a12ae64d914.jpg" width="521" height="391"/>

------------
### Matou Sakura is the best girl:
<img src="https://user-images.githubusercontent.com/68177491/113492318-6ae9bc00-948b-11eb-92c8-e79bb8f8cc76.jpg" width="640" height="905"/>
