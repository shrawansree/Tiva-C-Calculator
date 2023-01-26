#include "UART.h"
#include "Calculator.h"
#include "LCD.h"
#include "Keypad.h"
#include "Graphics.h"
#include "Password.h"


void    run(void){

    int main_driver     =   0;
    int trig_driver     =   0;
    do{
        main_driver  =   displayMenu();
        switch (main_driver) {
            case 1:{
                lcdClearScreen();
                if(calculatorRun(MAX_INPUT)){
                    printOutput();
                }   else{
                    displayError();
                }
                delay_ms(5000);

                shutdown();
                calculatorInit();
                break;
            }
            case 2:{
                trig_driver =   displayTrigSubMenu();
                if(trig_driver == -1){
                    break;
                }

                if(trigRun(trig_driver)){
                    printOutput();
                }   else{
                    displayError();
                }
                delay_ms(5000);

                shutdown();
                calculatorInit();
                break;
            }
            case 3:{
                passwordReset();
								delay_ms(5000);
							
                shutdown();
                calculatorInit();
                break;
            }
            default:{
                break;
            }
        }
    } while (main_driver != -1);
}


int     main(void){

    keypadInit();
    lcdInit();
    UART_Init();
    passwordControlInit();

    displayWelcome();
	
    int timeout =   0;
    while(  timeout != 3 ){
        calculatorInit();
        displayPassword();
        promptPassword();

        if(verifyPassword()){
            shutdown();
            break;
        }

        displayPasswordError();
        shutdown();
        timeout++;
    }

    if( timeout != 3 ){
        calculatorInit();
        run();
    }
    displayGoodbye();
    lcdClearScreen();

}
