//
// Created by Shrawan Sreekumar on 12/31/2022.
//

#include "Graphics.h"

char    welcomeString   []  =   "    Welcome    \0";
char    goodbyeString   []  =   "    Goodbye    \0";
char    errorString     []  =   "  !!!ERROR!!!  \0";
char    successString   []  =   "   Success!!!  \0";

char    passwordString  []  =   "Pass:>\0";
char    passwordError   []  =   "  !WRONG PASS! \0";

char    passwordNew     []  =   "New Pass:>     \0";
char    passwordReNew   []  =   "Re New Pass:>  \0";

char    menu1[]             =   "1.Calc         \0";
char    menu2[]             =   "2.Trig         \0";
char    menu3[]             =   "3.Reset Pass   \0";
char    menu4[]             =   "4.Exit         \0";

char    trigmenu1[]         =   "1.Sin          \0";
char    trigmenu2[]         =   "2.Cos          \0";
char    trigmenu3[]         =   "3.Tan          \0";
char    trigmenu4[]         =   "4.Sinh         \0";
char    trigmenu5[]         =   "5.Cosh         \0";
char    trigmenu6[]         =   "6.Tanh         \0";
char    trigmenu7[]         =   "7.<Back        \0";



void    displayShift(int position){
    if(!position) { //if LCD line postion 0; set DDRAM to value 00;
        SendDisplayByte(0,0x08, 0x00);
        delay_us(40);
    }   else{   //if LCD line position 1; set DDRAM to value 40
        SendDisplayByte(0, 0x0C, 0x00);
        delay_us(40);
    }

}


void    displayWelcome(void) {

    lcdClearScreen();   //clear screen
    lcdCursorControl(0);    //set cursor to disable

    int cycle;
    for(int i = 0;  i < 16;  i++){  //8 second welcome (16*0.5s)
        cycle   =   0;
        if(i % 2 == 0) {
            while (welcomeString[cycle] != '\0') {
                lcdWriteAlphaCaps   (welcomeString[cycle]); //writes all uppercase characters in string
                lcdWriteAlphaSmall  (welcomeString[cycle]); //writes all lowercase characters in string
                lcdWriteSymbol      (welcomeString[cycle]); //writes all symbols in string
                cycle++;
            }
            displayShift(1);    //shift display to second line

            for(int j = 0; j < i; j++){
                lcdWriteSymbol(' ');
            }
            lcdWriteSymbol('*');

            displayShift(0);
        }
        else{
            for(int j = 0; j < i; j++){
                lcdWriteSymbol(' ');
            }
            lcdWriteSymbol('*');
            displayShift(1); //shift display to second line

            cycle = 0;
            while (welcomeString[cycle] != '\0') {
                lcdWriteAlphaCaps(welcomeString[cycle]);
                lcdWriteAlphaSmall(welcomeString[cycle]);
                lcdWriteSymbol(welcomeString[cycle]);
                cycle++;
            }

            displayShift(0);
        }

        delay_ms(500);
    }

}


void    displayPassword(void){

    lcdClearScreen();
    lcdCursorControl(0);

    int cycle   =   0;
    while(passwordString[cycle] != '\0'){
        lcdWriteAlphaCaps   (passwordString[cycle]);
        lcdWriteAlphaSmall  (passwordString[cycle]);
        lcdWriteSymbol      (passwordString[cycle]);
        cycle++;
    }
}


void    displayGoodbye(void){

    lcdClearScreen();
    lcdCursorControl(0);

    int cycle;
    for(int i = 0;  i < 17;  i++){
        cycle   =   0;
        if(i % 2 == 0) {
            while (goodbyeString[cycle] != '\0') {
                lcdWriteAlphaCaps(goodbyeString[cycle]);
                lcdWriteAlphaSmall(goodbyeString[cycle]);
                lcdWriteSymbol(goodbyeString[cycle]);
                cycle++;
            }
            displayShift(1);

            for(int j = 0; j < i; j++){
                lcdWriteSymbol(' ');
            }
            lcdWriteSymbol('*');

            displayShift(0);
        }
        else{
            for(int j = 0; j < i; j++){
                lcdWriteSymbol(' ');
            }
            lcdWriteSymbol('*');
            displayShift(1);

            cycle = 0;
            while (goodbyeString[cycle] != '\0') {
                lcdWriteAlphaCaps(goodbyeString[cycle]);
                lcdWriteAlphaSmall(goodbyeString[cycle]);
                lcdWriteSymbol(goodbyeString[cycle]);
                cycle++;
            }

            displayShift(0);
        }

        delay_ms(500);
    }
}


void    displayError(void){

    lcdClearScreen();
    lcdCursorControl(0);
    displayShift(0);

    int cycle   =   0;
    while(errorString[cycle] != '\0'){
        lcdWriteSymbol(errorString[cycle]);
        lcdWriteAlphaCaps(errorString[cycle]);
        cycle++;
    }

}


void    displaySuccess(void){

    lcdClearScreen();
    lcdCursorControl(0);
    displayShift(0);

    int cycle   =   0;
    while(successString[cycle] != '\0'){
        lcdWriteSymbol(successString[cycle]);
        lcdWriteAlphaCaps(successString[cycle]);
        lcdWriteAlphaSmall(successString[cycle]);
        cycle++;
    }

    delay_ms(3000);
}


void    displayNewPassword(void){

    lcdClearScreen();
    lcdCursorControl(0);
    displayShift(0);

    int cycle   =   0;
    while(passwordNew[cycle] != '\0'){
        lcdWriteSymbol(passwordNew[cycle]);
        lcdWriteAlphaCaps(passwordNew[cycle]);
        lcdWriteAlphaSmall(passwordNew[cycle]);
        cycle++;
    }

}


void    displayReNewPassword(void){

    lcdClearScreen();
    lcdCursorControl(0);
    displayShift(0);

    int cycle   =   0;
    while(passwordReNew[cycle] != '\0'){
        lcdWriteSymbol(passwordReNew[cycle]);
        lcdWriteAlphaCaps(passwordReNew[cycle]);
        lcdWriteAlphaSmall(passwordReNew[cycle]);
        cycle++;
    }

}


void    displayPasswordError(void){

    lcdClearScreen();
    lcdCursorControl(0);
    displayShift(0);

    int cycle   =   0;
    while(passwordError[cycle] != '\0'){
        lcdWriteSymbol(     passwordError[cycle]);
        lcdWriteAlphaCaps(  passwordError[cycle]);
        cycle++;
    }

    delay_ms(3000);
}


int     displayMenu(void) {

    lcdClearScreen();
    lcdCursorControl(0);

    int     menu    =   1;
    int     cycle   =   0;
    char*   key     =   (char*) malloc(sizeof(char));
    key[0]          =   'x';

    while(1){
        *key =   readKeypad();  //read keypad value
        delay_ms(110);

        switch(menu){       //switch case through menu
            case 1:{
                displayShift(0);    cycle   =   0;
                while(menu1[cycle] != '\0'){
                    lcdWriteNumeric     (menu1[cycle]);
                    lcdWriteSymbol      (menu1[cycle]);
                    lcdWriteAlphaCaps   (menu1[cycle]);
                    lcdWriteAlphaSmall  (menu1[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(menu2[cycle] != '\0'){
                    lcdWriteNumeric     (menu2[cycle]);
                    lcdWriteSymbol      (menu2[cycle]);
                    lcdWriteAlphaCaps   (menu2[cycle]);
                    lcdWriteAlphaSmall  (menu2[cycle]);
                    cycle++;
                }
                break;
            }
            case 2:{
                displayShift(0);    cycle   =   0;
                while(menu2[cycle] != '\0'){
                    lcdWriteNumeric     (menu2[cycle]);
                    lcdWriteSymbol      (menu2[cycle]);
                    lcdWriteAlphaCaps   (menu2[cycle]);
                    lcdWriteAlphaSmall  (menu2[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(menu3[cycle] != '\0'){
                    lcdWriteNumeric     (menu3[cycle]);
                    lcdWriteSymbol      (menu3[cycle]);
                    lcdWriteAlphaCaps   (menu3[cycle]);
                    lcdWriteAlphaSmall  (menu3[cycle]);
                    cycle++;
                }
                break;
            }
            case 3:{
                displayShift(0);    cycle   =   0;
                while(menu3[cycle] != '\0'){
                    lcdWriteNumeric     (menu3[cycle]);
                    lcdWriteSymbol      (menu3[cycle]);
                    lcdWriteAlphaCaps   (menu3[cycle]);
                    lcdWriteAlphaSmall  (menu3[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(menu4[cycle] != '\0'){
                    lcdWriteNumeric     (menu4[cycle]);
                    lcdWriteSymbol      (menu4[cycle]);
                    lcdWriteAlphaCaps   (menu4[cycle]);
                    lcdWriteAlphaSmall  (menu4[cycle]);
                    cycle++;
                }
                break;
            }
            case 4:{
                displayShift(0);    cycle   =   0;
                while(menu4[cycle] != '\0'){
                    lcdWriteNumeric     (menu4[cycle]);
                    lcdWriteSymbol      (menu4[cycle]);
                    lcdWriteAlphaCaps   (menu4[cycle]);
                    lcdWriteAlphaSmall  (menu4[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(menu1[cycle] != '\0'){
                    lcdWriteNumeric     (menu1[cycle]);
                    lcdWriteSymbol      (menu1[cycle]);
                    lcdWriteAlphaCaps   (menu1[cycle]);
                    lcdWriteAlphaSmall  (menu1[cycle]);
                    cycle++;
                }
                break;
            }
            default:{
                if(menu < 1){
                    menu = 4;
                }
                if(menu > 4){
                    menu = 1;
                }
            }
        }

        switch (*key) {     //switch case through input
            case '1':{
                return 1;
            }
            case '2':{
                return 2;
            }
            case '3':{
                return 3;
            }
            case '4':{
                return -1;
            }
            case 'A':{
                menu--;
                break;
            }
            case 'B':{
                menu++;
                break;
            }
            default:{
                break;
            }
        }
    }
}


int     displayTrigSubMenu(void){

    lcdClearScreen();
    lcdCursorControl(0);

    int     menu    =   1;
    int     cycle   =   0;
    char*   key     =   (char*) malloc(sizeof(char));
    key[0]          =   'x';

    while(1){
        *key =   readKeypad();  //read keypad values
        delay_ms(110);

        switch(menu){   //switch case through trig-menu
            case 1:{
                displayShift(0);    cycle   =   0;
                while(trigmenu1[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu1[cycle]);
                    lcdWriteSymbol      (trigmenu1[cycle]);
                    lcdWriteAlphaCaps   (trigmenu1[cycle]);
                    lcdWriteAlphaSmall  (trigmenu1[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(trigmenu2[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu2[cycle]);
                    lcdWriteSymbol      (trigmenu2[cycle]);
                    lcdWriteAlphaCaps   (trigmenu2[cycle]);
                    lcdWriteAlphaSmall  (trigmenu2[cycle]);
                    cycle++;
                }
                break;
            }
            case 2:{
                displayShift(0);    cycle   =   0;
                while(trigmenu2[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu2[cycle]);
                    lcdWriteSymbol      (trigmenu2[cycle]);
                    lcdWriteAlphaCaps   (trigmenu2[cycle]);
                    lcdWriteAlphaSmall  (trigmenu2[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(trigmenu3[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu3[cycle]);
                    lcdWriteSymbol      (trigmenu3[cycle]);
                    lcdWriteAlphaCaps   (trigmenu3[cycle]);
                    lcdWriteAlphaSmall  (trigmenu3[cycle]);
                    cycle++;
                }
                break;
            }
            case 3:{
                displayShift(0);    cycle   =   0;
                while(trigmenu3[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu3[cycle]);
                    lcdWriteSymbol      (trigmenu3[cycle]);
                    lcdWriteAlphaCaps   (trigmenu3[cycle]);
                    lcdWriteAlphaSmall  (trigmenu3[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(trigmenu4[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu4[cycle]);
                    lcdWriteSymbol      (trigmenu4[cycle]);
                    lcdWriteAlphaCaps   (trigmenu4[cycle]);
                    lcdWriteAlphaSmall  (trigmenu4[cycle]);
                    cycle++;
                }
                break;
            }
            case 4:{
                displayShift(0);    cycle   =   0;
                while(trigmenu4[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu4[cycle]);
                    lcdWriteSymbol      (trigmenu4[cycle]);
                    lcdWriteAlphaCaps   (trigmenu4[cycle]);
                    lcdWriteAlphaSmall  (trigmenu4[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(trigmenu5[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu5[cycle]);
                    lcdWriteSymbol      (trigmenu5[cycle]);
                    lcdWriteAlphaCaps   (trigmenu5[cycle]);
                    lcdWriteAlphaSmall  (trigmenu5[cycle]);
                    cycle++;
                }
                break;
            }
            case 5:{
                displayShift(0);    cycle   =   0;
                while(trigmenu5[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu5[cycle]);
                    lcdWriteSymbol      (trigmenu5[cycle]);
                    lcdWriteAlphaCaps   (trigmenu5[cycle]);
                    lcdWriteAlphaSmall  (trigmenu5[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(trigmenu6[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu6[cycle]);
                    lcdWriteSymbol      (trigmenu6[cycle]);
                    lcdWriteAlphaCaps   (trigmenu6[cycle]);
                    lcdWriteAlphaSmall  (trigmenu6[cycle]);
                    cycle++;
                }
                break;
            }
            case 6:{
                displayShift(0);    cycle   =   0;
                while(trigmenu6[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu6[cycle]);
                    lcdWriteSymbol      (trigmenu6[cycle]);
                    lcdWriteAlphaCaps   (trigmenu6[cycle]);
                    lcdWriteAlphaSmall  (trigmenu6[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(trigmenu7[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu7[cycle]);
                    lcdWriteSymbol      (trigmenu7[cycle]);
                    lcdWriteAlphaCaps   (trigmenu7[cycle]);
                    lcdWriteAlphaSmall  (trigmenu7[cycle]);
                    cycle++;
                }
                break;
            }
            case 7:{
                displayShift(0);    cycle   =   0;
                while(trigmenu7[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu7[cycle]);
                    lcdWriteSymbol      (trigmenu7[cycle]);
                    lcdWriteAlphaCaps   (trigmenu7[cycle]);
                    lcdWriteAlphaSmall  (trigmenu7[cycle]);
                    cycle++;
                }
                displayShift(1);    cycle   =   0;
                while(trigmenu1[cycle] != '\0'){
                    lcdWriteNumeric     (trigmenu1[cycle]);
                    lcdWriteSymbol      (trigmenu1[cycle]);
                    lcdWriteAlphaCaps   (trigmenu1[cycle]);
                    lcdWriteAlphaSmall  (trigmenu1[cycle]);
                    cycle++;
                }
                break;
            }
            default:{
                if(menu < 1){
                    menu = 7;
                }
                if(menu > 7){
                    menu = 1;
                }
            }
        }

        switch (*key) { //switch case through key input
            case '1':{
                return 1;
            }
            case '2':{
                return 2;
            }
            case '3':{
                return 3;
            }
            case '4':{
                return 4;
            }
            case '5':{
                return 5;
            }
            case '6':{
                return 6;
            }
            case '7':{
                return -1;
            }
            case 'A':{
                menu--;
                break;
            }
            case 'B':{
                menu++;
                break;
            }
            default:{
                break;
            }
        }
    }
}


