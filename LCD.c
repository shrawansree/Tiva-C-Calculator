
#include "LCD.h"
int shift_toggle;
int lcd_line_toggle;

int checkBusyFlag(){
    if(GPIO_PORTA_DATA_R & (1<<6)){
        return 1;
    }	else{
        return 0;
    }
}


void    lcdNextLine(void){
    if(!lcd_line_toggle) {  //if toggle set
        //set DDRAM address to value 40 (first character in line 2 of the LCD)
        SendDisplayByte(0, 0x0C, 0x00);
        lcd_line_toggle = !lcd_line_toggle; //set toggle on
    }   else{
        //set DDRAM address to value 16 (last character in line 1 of the LCD)
        SendDisplayByte(0, 0x09, 0x00);
        lcd_line_toggle = !lcd_line_toggle; //set toggle off
    }
    delay_us(50);   //delay > 45us
}


void    lcdClearLast(void){

    SendDisplayByte(0,0x01,0x00);   //command to shift cursor left
    delay_us(50);                              //delay > 45us
    SendDisplayByte(1,0x02,0x00);   //send blank character to LCD
    delay_us(50);                              //delay > 45us
    SendDisplayByte(0,0x01,0x00);   //command to shift cursor left
    delay_us(50);                              //delay > 45us
}


void    lcdClearScreen(void){
    //Clear Display
    SendDisplayByte(0,0x00,0x01);
    delay_ms(5);
}


void    lcdCursorControl(int active){
    //sets cursor to visible/blinking or off
    if(!active){
        SendDisplayByte(0,0x00,0x0C);
    }   else{
        SendDisplayByte(0,0x00,0x0F);
    }
    delay_us(50);   //delay > 45ms
}


void    lcdWriteData(char c){

    //sends display data to write the appropriate symbol 'c' to the LCD
    //this function is specific to the Calculator class as it also accounts for the 'shift' case
    switch (c){
        case '1':{
            SendDisplayByte(1,0x03,0x01);
            break;
        }
        case '2':{
            SendDisplayByte(1,0x03,0x02);
            break;
        }
        case '3':{
            SendDisplayByte(1,0x03,0x03);
            break;
        }
        case '4':{
            SendDisplayByte(1,0x03,0x04);
            break;
        }
        case '5':{
            SendDisplayByte(1,0x03,0x05);
            break;
        }
        case '6':{
            SendDisplayByte(1,0x03,0x06);
            break;
        }
        case '7':{
            SendDisplayByte(1,0x03,0x07);
            break;
        }
        case '8':{
            SendDisplayByte(1,0x03,0x08);
            break;
        }
        case '9':{
            SendDisplayByte(1,0x03,0x09);
            break;
        }
        case '0':{
            if(!shift_toggle) { //prints '0'
                SendDisplayByte(1,0x03,0x00);
            } else{             //prints '^'
                SendDisplayByte(1, 0x05, 0x0E);
            }
            break;
        }
        case 'A':{
            if(!shift_toggle) { //prints '+'
                SendDisplayByte(1, 0x02, 0x0B);
            } else{             //prints 'x'
                SendDisplayByte(1, 0x07, 0x08);
            }
            break;
        }
        case 'B':{
            if(!shift_toggle) { //prints '-'
                SendDisplayByte(1, 0x02, 0x0D);
            } else{             //prints '/'
                SendDisplayByte(1, 0x02, 0x0F);
            }
            break;
        }
        case 'C':{
            if(!shift_toggle) { //prints '.'
                SendDisplayByte(1, 0x02, 0x0E);
            } else{             //prints 'E'
                SendDisplayByte(1, 0x04, 0x05);
            }
            break;
        }
        default:{
            break;
        }
    }
    delay_us(50);
}


void    lcdWriteAlphaCaps(char c){

    //sends display data to write the appropriate upper case alphabet 'c' to the LCD
    switch(c){
        case 'A':{
            SendDisplayByte(1, 0x04, 0x01);
            break;
        }
        case 'B':{
            SendDisplayByte(1, 0x04, 0x02);
            break;
        }
        case 'C':{
            SendDisplayByte(1, 0x04, 0x03);
            break;
        }
        case 'D':{
            SendDisplayByte(1, 0x04, 0x04);
            break;
        }
        case 'E':{
            SendDisplayByte(1, 0x04, 0x05);
            break;
        }
        case 'F':{
            SendDisplayByte(1, 0x04, 0x06);
            break;
        }
        case 'G':{
            SendDisplayByte(1, 0x04, 0x07);
            break;
        }
        case 'H':{
            SendDisplayByte(1, 0x04, 0x08);
            break;
        }
        case 'I':{
            SendDisplayByte(1, 0x04, 0x09);
            break;
        }
        case 'J':{
            SendDisplayByte(1, 0x04, 0x0A);
            break;
        }
        case 'K':{
            SendDisplayByte(1, 0x04, 0x0B);
            break;
        }
        case 'L':{
            SendDisplayByte(1, 0x04, 0x0C);
            break;
        }
        case 'M':{
            SendDisplayByte(1, 0x04, 0x0D);
            break;
        }
        case 'N':{
            SendDisplayByte(1, 0x04, 0x0E);
            break;
        }
        case 'O':{
            SendDisplayByte(1, 0x04, 0x0F);
            break;
        }
        case 'P':{
            SendDisplayByte(1, 0x05, 0x00);
            break;
        }
        case 'Q':{
            SendDisplayByte(1, 0x05, 0x01);
            break;
        }
        case 'R':{
            SendDisplayByte(1, 0x05, 0x02);
            break;
        }
        case 'S':{
            SendDisplayByte(1, 0x05, 0x03);
            break;
        }
        case 'T':{
            SendDisplayByte(1, 0x05, 0x04);
            break;
        }
        case 'U':{
            SendDisplayByte(1, 0x05, 0x05);
            break;
        }
        case 'V':{
            SendDisplayByte(1, 0x05, 0x06);
            break;
        }
        case 'W':{
            SendDisplayByte(1, 0x05, 0x07);
            break;
        }
        case 'X':{
            SendDisplayByte(1, 0x05, 0x08);
            break;
        }
        case 'Y':{
            SendDisplayByte(1, 0x05, 0x09);
            break;
        }
        case 'Z':{
            SendDisplayByte(1, 0x05, 0x0A);
            break;
        }
        default:{
            break;
        }
    }
    delay_us(50);
}


void    lcdWriteAlphaSmall(char c){

    //sends display data to write the appropriate lower case alphabet 'c' to the LCD
    switch(c){
        case 'a':{
            SendDisplayByte(1, 0x06, 0x01);
            break;
        }
        case 'b':{
            SendDisplayByte(1, 0x06, 0x02);
            break;
        }
        case 'c':{
            SendDisplayByte(1, 0x06, 0x03);
            break;
        }
        case 'd':{
            SendDisplayByte(1, 0x06, 0x04);
            break;
        }
        case 'e':{
            SendDisplayByte(1, 0x06, 0x05);
            break;
        }
        case 'f':{
            SendDisplayByte(1, 0x06, 0x06);
            break;
        }
        case 'g':{
            SendDisplayByte(1, 0x06, 0x07);
            break;
        }
        case 'h':{
            SendDisplayByte(1, 0x06, 0x08);
            break;
        }
        case 'i':{
            SendDisplayByte(1, 0x06, 0x09);
            break;
        }
        case 'j':{
            SendDisplayByte(1, 0x06, 0x0A);
            break;
        }
        case 'k':{
            SendDisplayByte(1, 0x06, 0x0B);
            break;
        }
        case 'l':{
            SendDisplayByte(1, 0x06, 0x0C);
            break;
        }
        case 'm':{
            SendDisplayByte(1, 0x06, 0x0D);
            break;
        }
        case 'n':{
            SendDisplayByte(1, 0x06, 0x0E);
            break;
        }
        case 'o':{
            SendDisplayByte(1, 0x06, 0x0F);
            break;
        }
        case 'p':{
            SendDisplayByte(1, 0x07, 0x00);
            break;
        }
        case 'q':{
            SendDisplayByte(1, 0x07, 0x01);
            break;
        }
        case 'r':{
            SendDisplayByte(1, 0x07, 0x02);
            break;
        }
        case 's':{
            SendDisplayByte(1, 0x07, 0x03);
            break;
        }
        case 't':{
            SendDisplayByte(1, 0x07, 0x04);
            break;
        }
        case 'u':{
            SendDisplayByte(1, 0x07, 0x05);
            break;
        }
        case 'v':{
            SendDisplayByte(1, 0x07, 0x06);
            break;
        }
        case 'w':{
            SendDisplayByte(1, 0x07, 0x07);
            break;
        }
        case 'x':{
            SendDisplayByte(1, 0x07, 0x08);
            break;
        }
        case 'y':{
            SendDisplayByte(1, 0x07, 0x09);
            break;
        }
        case 'z':{
            SendDisplayByte(1, 0x07, 0x0A);
            break;
        }
        default:{
            break;
        }
    }
    delay_us(50);
}


void    lcdWriteNumeric(char c){

    //sends display data to write the appropriate number 'c' to the LCD
    switch(c){
        case '0':{
            SendDisplayByte(1, 0x03, 0x00);
            break;
        }
        case '1':{
            SendDisplayByte(1, 0x03, 0x01);
            break;
        }
        case '2':{
            SendDisplayByte(1, 0x03, 0x02);
            break;
        }
        case '3':{
            SendDisplayByte(1, 0x03, 0x03);
            break;
        }
        case '4':{
            SendDisplayByte(1, 0x03, 0x04);
            break;
        }
        case '5':{
            SendDisplayByte(1, 0x03, 0x05);
            break;
        }
        case '6':{
            SendDisplayByte(1, 0x03, 0x06);
            break;
        }
        case '7':{
            SendDisplayByte(1, 0x03, 0x07);
            break;
        }
        case '8':{
            SendDisplayByte(1, 0x03, 0x08);
            break;
        }
        case '9':{
            SendDisplayByte(1, 0x03, 0x09);
            break;
        }
        default:{
            break;
        }
    }
    delay_us(50);
}


void    lcdWriteSymbol(char c){

    //sends display data to write the appropriate symbol 'c' to the LCD
    switch (c){
        case '!':{
            SendDisplayByte(1,0x02,0x01);
            break;
        }
        case '"':{
            SendDisplayByte(1,0x02,0x02);
            break;
        }
        case '#':{
            SendDisplayByte(1,0x02,0x03);
            break;
        }
        case '$':{
            SendDisplayByte(1,0x02,0x04);
            break;
        }
        case '%':{
            SendDisplayByte(1,0x02,0x05);
            break;
        }
        case '&':{
            SendDisplayByte(1,0x02,0x06);
            break;
        }
        case '\'':{
            SendDisplayByte(1,0x02,0x07);
            break;
        }
        case '(':{
            SendDisplayByte(1,0x02,0x08);
            break;
        }
        case ')':{
            SendDisplayByte(1,0x02,0x09);
            break;
        }
        case '*':{
            SendDisplayByte(1,0x02,0x0A);
            break;
        }
        case '+':{
            SendDisplayByte(1,0x02,0x0B);
            break;
        }
        case ',':{
            SendDisplayByte(1,0x02,0x0C);
            break;
        }
        case '-':{
            SendDisplayByte(1,0x02,0x0D);
            break;
        }
        case '.':{
            SendDisplayByte(1,0x02,0x0E);
            break;
        }
        case '/':{
            SendDisplayByte(1,0x02,0x0F);
            break;
        }
        case ':':{
            SendDisplayByte(1,0x03,0x0A);
            break;
        }
        case ';':{
            SendDisplayByte(1,0x03,0x0B);
            break;
        }
        case '<':{
            SendDisplayByte(1, 0x03, 0x0C);
            break;
        }
        case '=':{
            SendDisplayByte(1, 0x03, 0x0D);
            break;
        }
        case '>':{
            SendDisplayByte(1, 0x03, 0x0E);
            break;
        }
        case '?':{
            SendDisplayByte(1, 0x03, 0x0F);
            break;
        }
        case '^':{
            SendDisplayByte(1, 0x05, 0x0E);
            break;
        }
        case '_':{
            SendDisplayByte(1, 0x05, 0x0F);
            break;
        }
        case ' ':{
            SendDisplayByte(1, 0x02, 0x00);
            break;
        }
        default:{
            break;
        }
    }
    delay_us(50);   //delay > 45us
}


void    lcdENPulse(void){


    GPIO_PORTA_DATA_R       &= ~0x04;
    delay_us(50);   //delay > 45us

    GPIO_PORTA_DATA_R 		|= 0x04;
    delay_us(50);   //delay > 45us

    GPIO_PORTA_DATA_R 		&= ~0x04;
    delay_us(50);   //delay > 45us

}


void    SendDisplayByte(int type, unsigned long first, unsigned long second){

    //send a byte of data to the LCD Driver
    SendDisplayNibble(type,first);  //pass upper 4 bits
    SendDisplayNibble(type,second); //pass lower 4 bits

}


void    SendDisplayNibble(int type, unsigned long bits){

    //send 4 bits (nybble) of data to the LCD Driver
    if(!type){  //type 0 - instruction, type 1 - data
        GPIO_PORTA_DATA_R 	 	&= ~0x08;
    }	else{
        GPIO_PORTA_DATA_R		|= 0x08;
    }

    delay_us(50);   //delay > 45us

    GPIO_PORTA_DATA_R 			&= ~0x04;
    delay_us(50);   //delay > 45us

    //write bits to data line
    GPIO_PORTB_DATA_R			= bits;

    lcdENPulse();       //pulse EN Line
}


void    lcdInit(void){

    //Port Initialization
    PortA_Init();
    PortB_Init();
    //Set PLL 80MHz
    PLL_Init(80000000);
    //initialize SysTick
    SysTick_Init();

    shift_toggle = 0;       //checks if calculator has been 'shifted'
    lcd_line_toggle = 0;    //checks if lcd print line has to be shifted down

    //Power on and delay for >100ms
    delay_ms(120);

    //send instruction 0x03, then delay > 4.1 ms
    SendDisplayNibble(0,0x03);
    delay_ms(5);

    //send instruction 0x03, then delay > 100 us
    SendDisplayNibble(0,0x03);
    delay_us(120);

    //send instruction 0x03, then delay > 100 us
    SendDisplayNibble(0,0x03);
    delay_us(120);

    //send instruction 0x02, then delay > 100 us
    //Prepare LCD Controller for true set-up
    SendDisplayNibble(0,0x02);
    delay_us(120);

    //send instruction 0x02, 0x08, then delay > 55 us
    //Set LCD Controller up
    SendDisplayByte(0,0x02,0x08);
    delay_us(60);

    //send instruction 0x00, 0x08 then delay > 53 us
    //Display Control
    SendDisplayByte(0,0x00,0x08);
    delay_us(60);

    //send instruction 0x00, 0x01 then delay > 3 ms
    //Clear Display
    SendDisplayByte(0,0x00,0x01);
    delay_ms(5);

    //send instruction 0x00, 0x06 then delay > 55 us
    //Entry Mode
    SendDisplayByte(0,0x00,0x06);
    delay_us(60);

    //LCD Initialization End
    //send instruction 0x00, 0x01 then delay > 3 ms
    //Display Control On/Off
    SendDisplayByte(0,0x00,0x0F);
    delay_ms(5);

}


void    PortA_Init(void){

    volatile unsigned long delay;
    SYSCTL_RCGC2_R              |= 0x00000001;      // 1) A clock
    delay                       = SYSCTL_RCGC2_R;   // delay
    GPIO_PORTA_CR_R 			= 0x3F;             // allow changes to PA5-0
    GPIO_PORTA_AMSEL_R 			= 0x00;        		// 3) disable analog function
    GPIO_PORTA_PCTL_R 			= 0x00000000;   	// 4) GPIO clear bit PCTL
    GPIO_PORTA_DIR_R			= 0x0C;          	// 5) PA3-2 output
    GPIO_PORTA_AFSEL_R 			= 0x00;        		// 6) no alternate function
    GPIO_PORTA_DEN_R 			= 0x0C;          	// 7) enable digital pins PA3-2
}


void    PortB_Init(void){

    volatile unsigned long delay;
    SYSCTL_RCGC2_R              |= 0x00000002;      // 1) B clock
    delay 					    = SYSCTL_RCGC2_R;   // delay
    GPIO_PORTB_CR_R 			= 0x0F;             // allow changes to PB3-0
    GPIO_PORTB_AMSEL_R 			= 0x00;        		// 3) disable analog function
    GPIO_PORTB_PCTL_R 			= 0x00000000;   	// 4) GPIO clear bit PCTL
    GPIO_PORTB_DIR_R 			= 0x0F;          	// 5) PB3-0 output
    GPIO_PORTB_AFSEL_R 			= 0x00;        		// 6) no alternate function
    GPIO_PORTB_DEN_R 			= 0x0F;          	// 7) enable digital pins PB3-0
}
