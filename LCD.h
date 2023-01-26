//
// Created by Shrawan Sreekumar on 12/31/2022.
//

#ifndef LCD_H
#define LCD_H

#include "PLL.h"

#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_PDR_R        (*((volatile unsigned long *)0x40004514))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))

#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))


extern  int shift_toggle;
extern  int lcd_line_toggle;

void 	PortA_Init(void);
void 	PortB_Init(void);
void 	lcdInit(void);

int		checkBusyFlag();

void 	lcdENPulse(void);
void 	lcdClearScreen(void);
void 	lcdClearLast(void);
void    lcdCursorControl(int active);

void 	lcdWriteData(char c);
void    lcdWriteAlphaCaps(char c);
void    lcdWriteAlphaSmall(char c);
void    lcdWriteNumeric(char c);
void    lcdWriteSymbol(char c);
void    lcdNextLine(void);

void 	SendDisplayNibble(int type, unsigned long nibble);
void 	SendDisplayByte(int type, unsigned long first, unsigned long second);

#endif
