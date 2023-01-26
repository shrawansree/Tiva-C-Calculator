//
// Created by Shrawan Sreekumar on 1/2/2023.
//

#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdint.h>
#include "Calculator.h"
#include "Keypad.h"
#include "Graphics.h"

#define BASE_ADDRESS						((volatile uint32_t*)0x00020000)
#define FLASH_BOOTCFG_R         (*((volatile uint32_t *)0x400FE1D0))
#define FLASH_FMA_R             (*((volatile uint32_t *)0x400FD000))
#define FLASH_FMD_R             (*((volatile uint32_t *)0x400FD004))
#define FLASH_FMC_R             (*((volatile uint32_t *)0x400FD008))

#define PASSWORD_PARITY         1234



extern uint16_t    access_key;

void            passwordControlInit (void);
int             passwordWrite       (unsigned int* password);
unsigned int*   passwordRead        (int wordsize);
int             passwordClear       (int blocks);

void            promptPassword      (void);
int             verifyPassword      (void);
int             passwordReset       (void);



#endif //MINI_PROJECT_PASSWORD_H
