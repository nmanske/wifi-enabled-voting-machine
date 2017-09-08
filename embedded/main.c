// Main.c
// Runs on LM4F120/TM4C123
// Use Timer2A in 32-bit periodic mode to request interrupts at a periodic rate
// Daniel Valvano
// May 5, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
  Program 7.5, example 7.6

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

// oscilloscope or LED connected to PF3-1 for period measurement
// When using the color wheel, the blue LED on PF2 is on for four
// consecutive interrupts then off for four consecutive interrupts.
// Blue is off for: dark, red, yellow, green
// Blue is on for: light blue, blue, purple, white
// Therefore, the frequency of the pulse measured on PF2 is 1/8 of
// the frequency of the Timer2A interrupts.

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "PLL.h"
#include "Timer2.h"
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
#include "ADCSWTrigger.h"
#include "Switch.h"
#include "UART.h"
#include "esp8266.h"
#include "LED.h"
#include "LCD.h"

#define BUFFER_SIZE 1024
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

// USER BUTTONS
#define PREV_SCREEN		1
#define NEXT_SCREEN		2
#define SELECT				4
#define CAST_BALLOT		8

// USER CHOICES
#define PRESIDENT				0
#define VICE_PRESIDENT	1
#define TECH_CORE				2
#define LANGUAGES				3
#define PETS						4

// OTHER
#define FALSE						0
#define TRUE						1
#define DESELECT_SQUARE 0
#define SELECT_SQUARE	  1

// WEB GLOBALS
char POST_BALLOT[281] = "POST /insert_vote.php HTTP/1.1\r\nHost: ec2-54-183-227-218.us-west-1.compute.amazonaws.com\r\nContent-Type: application/x-www-form-urlencoded\r\nConnection: keep-alive\r\nContent-Length: 84\r\n\r\npin=1234&president=1&vice_president=1&tech_core=1&favorite_language=1&favorite_pet=1";
char GET_PIN[] = "GET /getPIN.php HTTP/1.1\r\nHost: ec2-54-183-227-218.us-west-1.compute.amazonaws.com\r\n\r\n";
char userChoices[] = "     ";
char inputPin[] = "    ";
char serverPin[] = "    ";


// STATE LOGIC
enum {PIN_SCREEN=-1,VOTE_1,VOTE_2,VOTE_3,VOTE_4,VOTE_5,END} screenStates;
uint8_t numberScreenChoices[] = {4, 3, 3, 4, 4};
int8_t currScreenState;
uint8_t currPinState;
uint8_t nextPinState;
uint8_t pinPressed;
uint8_t currRectState;
uint8_t nextRectState;

uint8_t button;

long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
uint8_t isPinValid(void);
void castBallot(void);

// use with timer
void UserTask(void){
  
}

int main(void){
	// STANDARD INIT RITUALS
	DisableInterrupts();
  PLL_Init(Bus80MHz);              // bus clock at 80 MHz
	LED_Init();
	UART_Init();       // UART0 only used for debugging
	ADC0_InitSWTriggerSeq3_Ch9();
	PortE_Switch_Init();
	ST7735_InitR(INITR_REDTAB);
	
	// INIT WIFI MODULE
	printf("\n\r-----------\n\rSystem starting...\n\r");
	EnableScreenInit();
	LED_GreenOn();
	
  ESP8266_Init(115200);      // connect to access point, set up as client
  ESP8266_GetVersionNumber();
	
	LED_GreenOff();
	
	// INIT STARTING PIN SCREEN
	PinScreenInit();
	currPinState = ADCPinState();
	UpdatePinSquare(SELECT_SQUARE, currPinState); //this will need to check the adc... adc needs to be init and running for this to work
	currScreenState = PIN_SCREEN;
	pinPressed = 0;
	
	while(1){
		
		while(currScreenState == PIN_SCREEN){
			nextPinState = ADCPinState();
			if(currPinState != nextPinState){
				UpdatePinSquare(DESELECT_SQUARE, currPinState);
				UpdatePinSquare(SELECT_SQUARE, nextPinState);
				currPinState = nextPinState;
			}
			button = Switch_Input();
			if(button==SELECT){
				inputPin[pinPressed] = (char)(currPinState+'0');
				pinPressed++;
				DrawPinInput(currPinState,pinPressed);
				if(pinPressed==4){
					PinVerifyScreen(inputPin);
					if(isPinValid() == TRUE){
						currScreenState = VOTE_1;
						SelectionScreenInit(currScreenState);
						currRectState = ADCRectState(4); 
						SelectChoice(currRectState);
					}
					else{
						PinFailScreen(inputPin);
						DelayWait10ms(1600);
						PinScreenInit();
						currPinState = ADCPinState();
						UpdatePinSquare(SELECT_SQUARE, currPinState); //this will need to check the adc... adc needs to be init and running for this to work
						currScreenState = PIN_SCREEN;
						pinPressed = 0;
						strcpy(inputPin,"    ");
					}
				}
			}
		}
		
		while(currScreenState >= VOTE_1 && currScreenState <= VOTE_5){
			if(currScreenState == VOTE_1 || currScreenState == VOTE_4 || currScreenState == VOTE_5){
				nextRectState = ADCRectState(4);
			}
			else if(currScreenState == VOTE_2 || currScreenState == VOTE_3){
				nextRectState = ADCRectState(3);
			}
			if(currRectState != nextRectState){
				DeselectChoice(currRectState);
				SelectChoice(nextRectState);
				currRectState = nextRectState;
			}
			button = Switch_Input();
			
			if(button == SELECT){
				if(userChoices[currScreenState]== (char)(currRectState+48)){
					userChoices[currScreenState] = ' ';
					DeselectedBox(currScreenState);
					
				}
				else{
					userChoices[currScreenState] = (char)(currRectState+48);
					DrawSelectedBox(currScreenState,currRectState);
					DelayWait10ms(500);
					currScreenState++;
					if(currScreenState <= VOTE_5){
						SelectionScreenInit(currScreenState);
						if(currScreenState == VOTE_1 || currScreenState == VOTE_4 || currScreenState == VOTE_5){
							currRectState = ADCRectState(4);
							if( userChoices[currScreenState] != ' '){
								DrawSelectedBox(currScreenState, userChoices[currScreenState] - '0');
							}
						}
						else if(currScreenState == VOTE_2 || currScreenState == VOTE_3){
							currRectState = ADCRectState(3);
							if( userChoices[currScreenState] != ' '){
								DrawSelectedBox(currScreenState, userChoices[currScreenState] - '0');
							}
						}
						SelectChoice(currRectState);
					}
					else{
						currScreenState = END;
						CastBallotScreen();
						currRectState = ADCRectState(0); 
					}
				}
				
			}
			else if(button == NEXT_SCREEN){
				DelayWait10ms(500);
				currScreenState++;
				if(currScreenState <= VOTE_5){
					SelectionScreenInit(currScreenState);
					if(currScreenState == VOTE_1 || currScreenState == VOTE_4 || currScreenState == VOTE_5){
						currRectState = ADCRectState(4);
						if( userChoices[currScreenState] != ' '){
							DrawSelectedBox(currScreenState, userChoices[currScreenState] - '0');
						}
					}
					else if(currScreenState == VOTE_2 || currScreenState == VOTE_3){
						currRectState = ADCRectState(3);
						if( userChoices[currScreenState] != ' '){
							DrawSelectedBox(currScreenState, userChoices[currScreenState] - '0');
						}						
					}
					SelectChoice(currRectState);
				}
				else{
					currScreenState = END;
					CastBallotScreen();
					currRectState = ADCRectState(0); 
				}
			}
			else if(button == PREV_SCREEN) {
				if(currScreenState != VOTE_1){
					DelayWait10ms(500);
					currScreenState--;
					SelectionScreenInit(currScreenState);
					if(currScreenState == VOTE_1 || currScreenState == VOTE_4 || currScreenState == VOTE_5){
						currRectState = ADCRectState(4);
						if( userChoices[currScreenState] != ' '){
							DrawSelectedBox(currScreenState, userChoices[currScreenState] - '0');
						}	
					}
					else if(currScreenState == VOTE_2 || currScreenState == VOTE_3){
						currRectState = ADCRectState(3);
						if( userChoices[currScreenState] != ' '){
							DrawSelectedBox(currScreenState, userChoices[currScreenState] - '0');
						}	
					}
					SelectChoice(currRectState);
				}
			}
			else if(button == CAST_BALLOT) {
				currScreenState = END;
				CastBallotScreen();
				currRectState = ADCRectState(0);
				DelayWait10ms(500);
			}
		}
		
		while(currScreenState == END){
			button = Switch_Input();
			if(button == CAST_BALLOT){
				BallotSendScreen(inputPin);
				castBallot();
				VoteSentScreen();
				while(button != SELECT){
					button = Switch_Input();
				}
				currScreenState = PIN_SCREEN;
				PinScreenInit();
				currPinState = ADCPinState();
				UpdatePinSquare(SELECT_SQUARE, currPinState); //this will need to check the adc... adc needs to be init and running for this to work
				pinPressed = 0;
				strcpy(inputPin,"    ");
				strcpy(userChoices,"     ");
			}
			else if(button == PREV_SCREEN){
				currScreenState--;
				SelectionScreenInit(currScreenState);
				if(currScreenState == VOTE_1 || currScreenState == VOTE_4 || currScreenState == VOTE_5){
					currRectState = ADCRectState(4);
				}
				else if(currScreenState == VOTE_2 || currScreenState == VOTE_3){
					currRectState = ADCRectState(3);
								
				} 
				if(userChoices[currScreenState] != ' '){
					DrawSelectedBox(currScreenState, userChoices[currScreenState] - '0');
				}			
				SelectChoice(currRectState);
			}
		}
		
	}
	
}

// verify user input pin value is same as pin on server
uint8_t isPinValid(void){
	ESP8266_GetStatus();
	if(ESP8266_MakeTCPConnection("ec2-54-183-227-218.us-west-1.compute.amazonaws.com")){ // open socket in server
		LED_GreenOn();
		ESP8266_SendTCP(GET_PIN);	//AT+CIPSEND=?
	}
	else{
		ErrorScreenInit(5);
	}
	ESP8266_CloseTCPConnection();
	LED_GreenOff();
	strcpy(serverPin, getServerPin());
	if(serverPin[0] == inputPin[0] && serverPin[1] == inputPin[1] && serverPin[2] == inputPin[2]
		&& serverPin[3] == inputPin[3]){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void castBallot(void){
	POST_BALLOT[189] = inputPin[0];
	POST_BALLOT[190] = inputPin[1];
	POST_BALLOT[191] = inputPin[2];
	POST_BALLOT[192] = inputPin[3];
	
	POST_BALLOT[204] = userChoices[0];
	POST_BALLOT[221] = userChoices[1];
	POST_BALLOT[233] = userChoices[2];
	POST_BALLOT[253] = userChoices[3];
	POST_BALLOT[268] = userChoices[4];
	
	if(ESP8266_MakeTCPConnection("ec2-54-183-227-218.us-west-1.compute.amazonaws.com")){ // open socket in server
		LED_GreenOn();
		
		ESP8266_SendTCP(POST_BALLOT);	//AT+CIPSEND=?
	}
	else{
		ErrorScreenInit(6);
	}
	ESP8266_CloseTCPConnection();
	LED_GreenOff();

}
