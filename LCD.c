#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ST7735.h"
#include "LCD.h"
#include "../inc/tm4c123gh6pm.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define DESELECT 0
#define SELECT 1

// USER CHOICES
#define PRESIDENT				0
#define VICE_PRESIDENT	1
#define TECH_CORE				2
#define LANGUAGES				3
#define PETS						4

#define TRUE 1
#define FALSE 0

static char presidentChoices[4][10] = {"Bard","Patt","Telang","Valvano"};
static char vicePresidentChoices[3][10] = {"Dylan","Mahesh","Ryan"};
static char techCoreChoices[3][10] = {"Embedded","Software","Other"};
static char buildingChoices[4][10] = {"C/C++","Java","Python","Other"};
static char petChoices[4][10] = {"Birds","Cats","Dogs","Fish"};
uint8_t numScreenChoices[] = {4, 3, 3, 4, 4};
uint8_t isSelectEnabled = TRUE;

char pinInput[7] = {"       "};

void EnableScreenInit(){
	ST7735_FillScreen(ST7735_BLUE);
	ST7735_DrawStringS(0,0,"PLEASE",ST7735_WHITE,2);
	ST7735_DrawStringS(0,2,"WAIT..",ST7735_WHITE,2);
	ST7735_DrawStringS(0,5,"ENABLING",ST7735_WHITE,2);
	ST7735_DrawStringS(0,7,"WIFI!",ST7735_WHITE,2);
	ST7735_DrawStringS(0,11,":)",ST7735_WHITE,2);
}

// display when wifi init fails
void ErrorScreenInit(){
	ST7735_DrawStringS(0,0,"CONNECTION",ST7735_WHITE,2);
	ST7735_DrawStringS(0,2,"ERROR...",ST7735_WHITE,2);
	ST7735_DrawStringS(0,5,"CHECK AND",ST7735_WHITE,2);
	ST7735_DrawStringS(0,7,"RESTART!",ST7735_WHITE,2);
	ST7735_DrawStringS(0,11,":(",ST7735_WHITE,2);
	while(1){}
}

void PinScreenInit(){
	uint32_t color;
	ST7735_FillScreen(ST7735_BLUE);
	ST7735_DrawStringS(0,0,"Enter PIN: ",ST7735_WHITE,2);
	
	// draw num pad
	color = ST7735_WHITE;
	ST7735_DrawSquare(4,39,38,color);
	ST7735_DrawSquare(4,80,38,color);
	ST7735_DrawSquare(4,121,38,color);
	ST7735_DrawSquare(45,39,38,color);
	ST7735_DrawSquare(45,80,38,color);
	ST7735_DrawSquare(45,121,38,color);
	ST7735_DrawSquare(86,39,38,color);
	ST7735_DrawSquare(86,80,38,color);
	ST7735_DrawSquare(86,121,38,color);
	ST7735_DrawChar(19,51,'1',ST7735_WHITE,ST7735_BLUE,2);
	ST7735_DrawChar(60,51,'2',ST7735_WHITE,ST7735_BLUE,2);
	ST7735_DrawChar(101,51,'3',ST7735_WHITE,ST7735_BLUE,2);
	ST7735_DrawChar(19,92,'4',ST7735_WHITE,ST7735_BLUE,2);
	ST7735_DrawChar(60,92,'5',ST7735_WHITE,ST7735_BLUE,2);
	ST7735_DrawChar(101,92,'6',ST7735_WHITE,ST7735_BLUE,2);
	ST7735_DrawChar(19,133,'7',ST7735_WHITE,ST7735_BLUE,2);
	ST7735_DrawChar(60,133,'8',ST7735_WHITE,ST7735_BLUE,2);
	ST7735_DrawChar(101,133,'9',ST7735_WHITE,ST7735_BLUE,2);
	
	// draw pin underscore
	ST7735_DrawFastHLine(24,36,10,ST7735_WHITE);
	ST7735_DrawFastHLine(24+24,36,10,ST7735_WHITE);
	ST7735_DrawFastHLine(24+48,36,10,ST7735_WHITE);
	ST7735_DrawFastHLine(24+72,36,10,ST7735_WHITE);
}

void PinVerifyScreen(char *pin){
	ST7735_FillScreen(ST7735_BLUE);
	ST7735_DrawStringS(0,0,"VERIFYING",ST7735_WHITE,2);
	ST7735_DrawStringS(0,2,"PIN ",ST7735_WHITE,2);
	ST7735_DrawStringS(8,2,pin,ST7735_WHITE,2);
	ST7735_DrawStringS(0,4,"WITH THE",ST7735_WHITE,2);
	ST7735_DrawStringS(0,6,"SERVER..",ST7735_WHITE,2);
}

void PinFailScreen(char *pin){
	ST7735_FillScreen(ST7735_BLUE);
	ST7735_DrawStringS(0,0,"PIN ",ST7735_WHITE,2);
	ST7735_DrawStringS(7,0,pin,ST7735_WHITE,2);
	ST7735_DrawStringS(0,2,"IS NOT",ST7735_WHITE,2);
	ST7735_DrawStringS(0,4,"CORRECT",ST7735_WHITE,2);
	ST7735_DrawStringS(0,7,"TRY AGAIN!",ST7735_WHITE,2);
}

void CastBallotScreen(void){
	ST7735_FillScreen(ST7735_BLUE);
	ST7735_DrawStringS(0,0,"END OF",ST7735_WHITE,2);
	ST7735_DrawStringS(0,2,"BALLOT!",ST7735_WHITE,2);
	ST7735_DrawStringS(0,5,"PRESS CAST",ST7735_WHITE,2);
	ST7735_DrawStringS(0,7,"VOTE BUTTON",ST7735_WHITE,2);
	ST7735_DrawStringS(0,9,"TO SUBMIT",ST7735_WHITE,2);
}

void SelectionScreenInit(uint8_t screen_num){
	int i;
	ST7735_FillScreen(ST7735_BLUE);
	if(screen_num == PRESIDENT){
		ST7735_DrawStringS(2,0,"President",ST7735_WHITE,2);
	}
	else if(screen_num == VICE_PRESIDENT){
		ST7735_DrawStringS(0,0,"Vice Pres",ST7735_WHITE,2);
	}
	else if(screen_num == TECH_CORE){
		ST7735_DrawStringS(1,0,"Tech Core",ST7735_WHITE,2);
	}
	else if(screen_num == LANGUAGES){
		ST7735_DrawStringS(0,0,"Best Lang?",ST7735_WHITE,2);
	}
	else if(screen_num == PETS){
		ST7735_DrawStringS(0,0,"Which Pet?",ST7735_WHITE,2);
	}
	
	for(i = numScreenChoices[screen_num]-1; i>=0 ; i--){
		if(screen_num == PRESIDENT){
			ST7735_DrawStringUnfixed(30,35+(i*33),presidentChoices[i],ST7735_WHITE,1);
		}
		else if(screen_num == VICE_PRESIDENT){
			ST7735_DrawStringUnfixed(30,35+(i*33),vicePresidentChoices[i],ST7735_WHITE,1);
		}
		else if(screen_num == TECH_CORE){
			ST7735_DrawStringUnfixed(30,35+(i*33),techCoreChoices[i],ST7735_WHITE,1);
		}
		else if(screen_num == LANGUAGES){
			ST7735_DrawStringUnfixed(30,35+(i*33),buildingChoices[i],ST7735_WHITE,1);
		}
		else if(screen_num == PETS){
			ST7735_DrawStringUnfixed(30,35+(i*33),petChoices[i],ST7735_WHITE,1);
		}
		ST7735_DrawFastHLine(5,23+((i)*33),117,ST7735_WHITE);
		ST7735_DrawFastHLine(5,53+((i)*33),117,ST7735_WHITE);
		ST7735_DrawFastVLine(5,23+((i)*33),30,ST7735_WHITE);
		ST7735_DrawFastVLine(122,23+((i)*33),30,ST7735_WHITE);
		ST7735_DrawSquare(14,33+(i*33),9,ST7735_WHITE);		
	}
}

void DrawPinInput(uint8_t pin_number, uint8_t pin_length){
	if(pin_length == 1){
		strcpy(pinInput,"       ");
	}
	pinInput[(pin_length-1)*2] = (char)(pin_number+48);
	ST7735_DrawStringS(4,2,pinInput,ST7735_WHITE,2);
}

void UpdatePinSquare(uint8_t mode, uint8_t square){
	uint32_t color;
	if(mode == DESELECT){
		color = ST7735_WHITE;
	}
	else if(mode == SELECT){
		color = ST7735_RED;
	}
	switch(square){
		case 1:
			ST7735_DrawSquare(4,4+35,38,color);
			ST7735_DrawChar(19,51,'1',ST7735_WHITE,ST7735_BLUE,2);
			break;
		case 2:
			ST7735_DrawSquare(45,4+35,38,color);
			ST7735_DrawChar(60,51,'2',ST7735_WHITE,ST7735_BLUE,2);
			break;
		case 3:
			ST7735_DrawSquare(86,4+35,38,color);
			ST7735_DrawChar(101,51,'3',ST7735_WHITE,ST7735_BLUE,2);
			break;
		case 4:
			ST7735_DrawSquare(4,45+35,38,color);
			ST7735_DrawChar(19,92,'4',ST7735_WHITE,ST7735_BLUE,2);
			break;
		case 5:
			ST7735_DrawSquare(45,45+35,38,color);
			ST7735_DrawChar(60,92,'5',ST7735_WHITE,ST7735_BLUE,2);
			break;
		case 6:
			ST7735_DrawSquare(86,45+35,38,color);
			ST7735_DrawChar(101,92,'6',ST7735_WHITE,ST7735_BLUE,2);
			break;
		case 7:
			ST7735_DrawSquare(4,86+35,38,color);
			ST7735_DrawChar(19,133,'7',ST7735_WHITE,ST7735_BLUE,2);
			break;
		case 8:
			ST7735_DrawSquare(45,86+35,38,color);
			ST7735_DrawChar(60,133,'8',ST7735_WHITE,ST7735_BLUE,2);
			break;
		case 9:
			ST7735_DrawSquare(86,86+35,38,color);
			ST7735_DrawChar(101,133,'9',ST7735_WHITE,ST7735_BLUE,2);
			break;
	}
}

void SelectChoice(uint8_t slot){
	ST7735_DrawFastHLine(5,23+((slot-1)*33),117,ST7735_RED);
	ST7735_DrawFastHLine(5,53+(((slot-1))*33),117,ST7735_RED);
	ST7735_DrawFastVLine(5,23+((slot-1)*33),30,ST7735_RED);
	ST7735_DrawFastVLine(122,23+((slot-1)*33),30,ST7735_RED);
}

void DeselectChoice(uint8_t slot){
	ST7735_DrawFastHLine(5,23+((slot-1)*33),117,ST7735_WHITE);
	ST7735_DrawFastHLine(5,53+((slot-1)*33),117,ST7735_WHITE);
	ST7735_DrawFastVLine(5,23+((slot-1)*33),30,ST7735_WHITE);
	ST7735_DrawFastVLine(122,23+((slot-1)*33),30,ST7735_WHITE);
}	

void DrawSelectedBox(uint8_t screen_num, uint8_t choice){
	int i;
	for(i = numScreenChoices[screen_num]-1; i>=0 ; i--){
		ST7735_FillRect(15,34+(i*33),8,8,ST7735_BLUE);
	}
	ST7735_FillRect(15,1+(choice*33),8,8,ST7735_RED);
}
