/*
	Students: Nathan Manske and Nathan Vu
	TA Name: Mahesh
	Last Change: 02/xx/16
	Module Purpose: Switch Interface
	Hardware Config: See attached Lab5_Artist.sch
*/


// **************DelayWait10ms*********************
// Does a 10ms computation n number of times
// Input: how many 10ms to wait 
// Output: none
void DelayWait10ms(uint32_t n);

// **************PortE_Switch_Init*********************
// Initialize external switches
// Input: none
// Output: none
void PortE_Switch_Init(void);

// **************Switch_Input*********************
// Input from switches
// Input: none 
// Output: 0 to 7 depending on switches
// 0x01 is PE0, 0x02 is PE1,
// 0x04 is PE2
uint8_t Switch_Input(void);
