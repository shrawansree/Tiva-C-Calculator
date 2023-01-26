//
// Created by Shrawan Sreekumar on 12/31/2022.
//

#ifndef PLL_H
#define PLL_H

//PLL related Defines
#define SYSCTL_RIS_R          (*((volatile unsigned long *)0x400FE050))
#define SYSCTL_RCC_R          (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R         (*((volatile unsigned long *)0x400FE070))

//SysTick related Defines
#define NVIC_ST_CTRL_R        (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R      (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R     (*((volatile unsigned long *)0xE000E018))


void delay_us(int delay);
void delay_ms(int delay);
int round_divider(unsigned long freq);
void PLL_Init(unsigned long freq);
void SysTick_Wait(unsigned long delay);
void SysTick_Init(void);

#endif
