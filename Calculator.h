//
// Created by Shrawan Sreekumar on 12/31/2022.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h.>
#include <math.h>
#include "LCD.h"
#include "PLL.h"
#include "Keypad.h"
#include "Graphics.h"

#define STRINGLEN 34
#define MAX_INPUT 31
#define MAXTRIG_INPUT 27

extern  char        symbols[];

extern  char*       string;
extern  int         cursor_position;

extern  float*      values;
extern  int         valcount;

extern  char*       operators;
extern  int         opcount;

extern  float*      output;


void        calculatorInit  (void);
int         calculatorRun   (int inputLimit);
int         trigRun         (int choice);

void        processInput    (char key);
int         parseInput      (void);
int         is_symbol       (char c);
void        tokenize        (void);
void        parseDigit      (int* i);
int         errorCheck      (void);

void        printOutput     (void);
void        shutdown        (void);

#endif
