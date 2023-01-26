//
// Created by Shrawan Sreekumar on 12/31/2022.
//

#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdlib.h>
#include "PLL.h"

#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))

#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PDR_R 		(*((volatile unsigned long *)0x40024514))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

//*************************************************************************************************************

//custom struct to hold read values of rows
typedef struct{
    //inputs
    unsigned long PORTE0;
    unsigned long PORTE1;
    unsigned long PORTE2;
    unsigned long PORTE3;
} Keypad;

//*************************************************************************************************************

extern  Keypad *this;

//*************************************************************************************************************

void PortD_Init(void);
void PortE_Init(void);
void keypadInit(void);

void readRow(void);
char readKeypad();

//*************************************************************************************************************

#endif
