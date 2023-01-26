#include "Keypad.c"
#include "PLL.c"
#include "LCD.c"
#include "UART.h"
#include <stdio.h>

void DebugInit(void);

int main(void){
	
	PLL_Init(80000000);
	SysTick_Init();
	keypadInit();
	UART_Init();
	
	char *c = (char*)malloc(sizeof(char));
	*c = 'x';
	
	while(*c != 'A'){
		*c = readKeypad();
		printf("\n Last Pressed Key : %c",*c);
		SysTick_Wait(10000000);
	}
}
