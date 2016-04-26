#include <stdint.h>

void EnableScreenInit(void);
void ErrorScreenInit(void);
void PinScreenInit(void);
void PinVerifyScreen(char *pin);
void PinFailScreen(char *pin);
void CastBallotScreen(void);
void VoteSentScreen(void);
void BallotSendScreen(char *pin);
void SelectionScreenInit(uint8_t screen_num);
void DrawPinInput(uint8_t pin_number, uint8_t pin_length);
void UpdatePinSquare(uint8_t mode, uint8_t square);
void SelectChoice(uint8_t slot);
void DeselectChoice(uint8_t slot);
void DrawSelectedBox(uint8_t screen_num, uint8_t choice);
void DeselectedBox(uint8_t screen_num);

