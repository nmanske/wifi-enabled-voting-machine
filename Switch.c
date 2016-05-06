/*
	Students: Nathan Manske and Nathan Vu
	TA Name: Mahesh
	Last Change: 02/xx/16
	Module Purpose: Switch Interface
	Hardware Config: See attached Lab8_Artist.sch
*/

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"

#define PE0  (*((volatile unsigned long *)0x40024004))
#define PE1  (*((volatile unsigned long *)0x40024008))
#define PE2  (*((volatile unsigned long *)0x40024010))
#define PE3  (*((volatile unsigned long *)0x40024020))
uint8_t value;

void DelayWait10ms(uint32_t n){
	volatile uint32_t time;
	while(n){
		time = 727240*2/91;  // 10msec
		while(time){
			time--;
		}
		n--;
	}
}

void PortE_Switch_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x10;            	// activate clock for port E
	while((SYSCTL_RCGCGPIO_R & 0x10) == 0){};	//wait for clock to settle

	GPIO_PORTE_DIR_R &= ~0x0F;            	// make PE3-PE0 inputs
	GPIO_PORTE_DEN_R |= 0x0F;            	// enable digital I/O on PE3-PE0

	GPIO_PORTE_AFSEL_R &= ~0x0F;          	// disable alt funct on PE3-PE0
	GPIO_PORTE_PCTL_R &= ~0x0000FFFF;		// configure PE3-PE0 as GPIO
	GPIO_PORTE_AMSEL_R = 0;            		// disable analog functionality on PortE
}


//are we going to try to avoid switch interaction if 2 are pressed at same time?
uint8_t Switch_Input(void){				
	if(((PE3>>3) || (PE2>>2) || (PE1>>1) || PE0) == 0){return 0;}
	DelayWait10ms(5);
	value = PE3+PE2+PE1+PE0;
	if(((PE3>>3) || (PE2>>2) || (PE1>>1) || PE0) == 1){
		while(((PE3>>3) || (PE2>>2) || (PE1>>1) || PE0) == 1){};
		return value;
	}
	return 0;
}

