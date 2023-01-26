#include "Keypad.h"


Keypad *this;


char readKeypad(){

    free(this);     //clear memory for fresh read

    this = (Keypad*)malloc(sizeof(Keypad)); //new memory allocated to store values

    for(int i = 0; i < 4; i++){         //4 columns to be read from

        GPIO_PORTD_DATA_R = (1U << i);  //cycle through each of the columns
        delay_ms(1);
        readRow();
        delay_ms(1);

        switch (i){
            case 0:{
                if(this->PORTE0 == 0x01){
                    return '1'; //if keypad matrix 1x1 pressed
                } else if(this->PORTE1 == 0x02){
                    return '4'; //if keypad matrix 2x1 pressed
                } else if(this->PORTE2 == 0x04){
                    return '7'; //if keypad matrix 3x1 pressed
                } else if(this->PORTE3 == 0x08){
                    return '*'; //if keypad matrix 4x1 pressed
                } else{
                    //empty
                }
                break;
            }
            case 1:{
                if(this->PORTE0 == 0x01){
                    return '2'; //if keypad matrix 1x2 pressed
                } else if(this->PORTE1 == 0x02){
                    return '5'; //if keypad matrix 2x2 pressed
                } else if(this->PORTE2 == 0x04){
                    return '8'; //if keypad matrix 3x2 pressed
                } else if(this->PORTE3 == 0x08){
                    return '0'; //if keypad matrix 4x2 pressed
                } else{
                    //empty
                }
                break;
            }
            case 2:{
                if(this->PORTE0 == 0x01){
                    return '3'; //if keypad matrix 1x3 pressed
                } else if(this->PORTE1 == 0x02){
                    return '6'; //if keypad matrix 2x3 pressed
                } else if(this->PORTE2 == 0x04){
                    return '9'; //if keypad matrix 3x3 pressed
                } else if(this->PORTE3 == 0x08){
                    return '#'; //if keypad matrix 4x3 pressed
                } else{
                    //empty
                }
                break;
            }
            case 3:{
                if(this->PORTE0 == 0x01){
                    return 'A'; //if keypad matrix 1x4 pressed
                } else if(this->PORTE1 == 0x02){
                    return 'B'; //if keypad matrix 2x4 pressed
                } else if(this->PORTE2 == 0x04){
                    return 'C'; //if keypad matrix 3x4 pressed
                } else if(this->PORTE3 == 0x08){
                    return 'D'; //if keypad matrix 4x4 pressed
                } else{
                    //empty
                }
                break;
            }
            default:
                break;
        }
    }
    return 'n';
}


void readRow(void){
    this->PORTE0 = GPIO_PORTE_DATA_R & 0x01;
    this->PORTE1 = GPIO_PORTE_DATA_R & 0x02;
    this->PORTE2 = GPIO_PORTE_DATA_R & 0x04;
    this->PORTE3 = GPIO_PORTE_DATA_R & 0x08;
}


void keypadInit(void){
    PortD_Init();   //initialize PORTD
    PortE_Init();   //initialize PORTE
    this = (Keypad*)malloc(sizeof(Keypad)); //allocated memory to store values from 'readRow'
    readRow();      //read current values of rows
}


void PortD_Init(void){

    volatile unsigned long delay;
    SYSCTL_RCGC2_R          |= 0x00000008;      // 1) D clock
    delay                   = SYSCTL_RCGC2_R;   // delay
    GPIO_PORTD_LOCK_R 		= 0x4C4F434B;   	// 2) unlock PortD
    GPIO_PORTD_CR_R 		= 0x0F;             // allow changes to PD3-0
    GPIO_PORTD_AMSEL_R 		= 0x00;        		// 3) disable analog function
    GPIO_PORTD_PCTL_R 		= 0x00000000;   	// 4) GPIO clear bit PCTL
    GPIO_PORTD_DIR_R 		= 0x0F;          	// 5) PD3-P0 output
    GPIO_PORTD_AFSEL_R 		= 0x00;        		// 6) no alternate function
    GPIO_PORTD_DEN_R 		= 0x0F;          	// 7) enable digital pins PD3-0
}


void PortE_Init(void){

    volatile unsigned long delay;
    SYSCTL_RCGC2_R          |= 0x00000010;      // 1) E clock
    delay                   = SYSCTL_RCGC2_R;   // delay
    GPIO_PORTE_CR_R 	    = 0x1F;             // allow changes to PE4-0
    GPIO_PORTE_AMSEL_R 		= 0x00;             // 3) disable analog function
    GPIO_PORTE_PCTL_R 		= 0x00000000;       // 4) GPIO clear bit PCTL
    GPIO_PORTE_DIR_R 		= 0x00;             // 5) PE3-0 input
    GPIO_PORTE_AFSEL_R 		= 0x00;        		// 6) no alternate function
    GPIO_PORTE_DEN_R 		= 0x0F;             // 7) enable digital pins PE3-0
    GPIO_PORTE_PDR_R 		= 0x0F; 			// 8) pull-ups enabled
}