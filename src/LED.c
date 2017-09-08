// LED.c
// Runs on TM4C123
// Provide functions that initialize a GPIO as an input pin and
// allow reading of two negative logic switches on PF0 and PF4
// Output to LEDs
// Use bit-banded I/O.
// Daniel and Jonathan Valvano
// Feb 23, 2015
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2014
   Section 4.2    Program 4.2

  "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014
   Example 2.3, Program 2.9, Figure 2.36

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

#define PB7      (*((volatile unsigned long *)0x40005200))

//------------LED_Init------------
// Initialize GPIO Port F for negative logic switches on PF0 and
// PF4 as the Launchpad is wired.  Weak internal pull-up
// resistors are enabled, and the NMI functionality on PF0 is disabled.
// LEDs on PF3,2,1 are enabled
// Input: none
// Output: none
void LED_Init(void){       
  SYSCTL_RCGCGPIO_R |= 0x02;     // 1) activate Port F
  while((SYSCTL_PRGPIO_R & 0x02)!=0x02){}; // wait to finish activating      
	GPIO_PORTB_AMSEL_R &= ~0x80;
	GPIO_PORTB_PCTL_R &= ~0xF0000000;
	GPIO_PORTB_DEN_R = 0x80;
	GPIO_PORTB_AFSEL_R &= ~0x80;
	GPIO_PORTB_DIR_R |= 0x80;       
}


//------------LED_GreenOn------------
// Turn on green LED
// Input: none
// Output: none
void LED_GreenOn(void){
  PB7  = 0x80;
}
//------------LED_GreenOff------------
// Turn off green LED
// Input: none
// Output: none
void LED_GreenOff(void){
  PB7  = 0x00;
}
