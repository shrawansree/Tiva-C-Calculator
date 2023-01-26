//
// Created by Shrawan Sreekumar on 12/31/2022.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "LCD.h"
#include "PLL.h"
#include "Keypad.h"

void    displayShift        (int position);
void    displayWelcome      (void);
void    displayPassword     (void);
void    displayGoodbye      (void);
void    displayError        (void);
void    displaySuccess      (void);
void    displayPasswordError(void);
int     displayMenu         (void);
int     displayTrigSubMenu  (void);
void    displayNewPassword  (void);
void    displayReNewPassword(void);


void    printSin(void);
void    printCos(void);

#endif
