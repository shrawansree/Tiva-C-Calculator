//
// Created by Shrawan Sreekumar on 1/2/2023.
//
#include "Password.h"

uint16_t    access_key =   0;

void    passwordControlInit(void){

    //check both keys for Flash access
    if (!(FLASH_BOOTCFG_R & 0x10)) {
        access_key =    0x71D5;
    }
    else {
        access_key =    0xA442;
    }
}


int     passwordWrite(unsigned int* password){

		int size = sizeof(*password)/sizeof(unsigned int);
    //calculate block size (of 1024)
    int blocks = ((2 * sizeof(uint32_t)) / 1024) + 1;

    if(!passwordClear(2)){ //attempt to clear that block of flash memory
        return -1;
    }

    int i = 0;
    for(int i = 0; i < 2; i++){
        //data register loaded with data
        FLASH_FMD_R     = ((volatile unsigned int*)password)[i];
        //clear and set write address
        FLASH_FMA_R     &= 0xFFFC0000;
        FLASH_FMA_R     |= (uint32_t)BASE_ADDRESS + (i * sizeof(uint32_t));
        FLASH_FMC_R     = (access_key << 16) | 0x1; // write the data

        while (FLASH_FMC_R & 0x1) {
            //wait till write complete
        }
    }

    return 0;

}


unsigned int*   passwordRead(int wordsize){

    //allocate memory for password
    unsigned int* password  =   (unsigned int*) malloc(sizeof(unsigned int) *   wordsize);
    for (int i = 0; i < wordsize; i++) {
        //read from flash to password buffer
        ((unsigned int*)password)[i] = BASE_ADDRESS[i]; //copy value
    }
    return  password;
}


int     passwordClear(int blocks){
    if (access_key == 0) {  //check access key
        return 0;
    }

    int i   =   0;
    while(i < blocks) {
        FLASH_FMA_R &= 0xFFFC0000;  //clear and set write address
        FLASH_FMA_R |= ((unsigned int)BASE_ADDRESS) + (i*1024); //allocate memory in blocks
        FLASH_FMC_R = (access_key << 16) | 0x2; //set erase
        while (FLASH_FMC_R & 0x2) {
            //wait until bit cleared
        }
        i++;
    }
    return 1;
}


void    promptPassword(void){

    lcdCursorControl(1);    //turn on LCD Cursor
    char*   key     =   (char*) malloc(sizeof(char));   //allocate memory for keypad value captured
    while(1){   //infinite loop
        key[0] = readKeypad();  //read key pressed value
        if(key[0] == '*'){  //if 'end', break from loop
            break;
        }
        if(key[0] != 'n') { //if keypad not pressed
            if (cursor_position > 6){   //if string length is greater than 6 (limits password length to 6)
                while (key[0] != '*' && key[0] != '#') {    //unless terminate or erase, do not process
                    key[0] = readKeypad();
                }
            }
            processInput(key[0]);   //process each key press
        }
        delay_ms(110);  //delay between key presses
    }

    string[cursor_position] = '\0'; //set string to terminate with EOF
    free(key);  //free 'key' memory

}


int     verifyPassword(void){

    lcdClearScreen();   //clear screen

    for (int i = 0; i < cursor_position; i++) {
        if( !isdigit(string[i]) ){  //if password input is not all digits
            return 0;
        }
    }

    unsigned int*   passCheck;  //pointer to memory location of read password
    passCheck   =   passwordRead(2);    //read password from flash memory
    if(passCheck[1] ==  PASSWORD_PARITY){   //check password parity
        if(passCheck[0] ==  strtol(string,NULL,10)){    //compare password in memory vs entered
            return 1;
        }
    }

    free(passCheck);    //free memory allocated to holding password from flash

    return 0;

}


int     passwordReset(void){
    lcdClearScreen();   //clear screen
    lcdCursorControl(0);    //  set cursor display off

    int timeout =   0;      //timeout password reset
    while(  timeout != 3 ){ //if failed more than 3 times

        displayPassword();  //display password graphics
        promptPassword();   //prompt user for password

        if(verifyPassword()){
					  shutdown(); //clear all values and free allocated memory
						calculatorInit();   //allocate new memory space for values
            break;  //if successfully verified password, break
        }

        displayPasswordError(); //if not, display error
        shutdown(); //clear all values and free allocated memory
        calculatorInit();   //allocate new memory space for values

        timeout++;
    }

    if( timeout == 3 ){
        return 0;   //if timeout failed, return 0
    }

		delay_ms(500);
    timeout =   0;
    while(  timeout != 3 ){ //if failed more than 3 times

        displayNewPassword(); //if password verified, display graphics for new password
        displayShift(1);    // shift input to lower line
        promptPassword();   //prompt new password

        int c   =   0;
        for (int i = 0; i < cursor_position; i++) {
            if( !isdigit(string[i]) ){  //if password input is not all digits
                c   =   1;
            }
        }
        if(!c){
            break;
        }

        displayPasswordError(); //if not, display error
        shutdown(); //clear all values and free allocated memory
        calculatorInit();   //allocate new memory space for values

        timeout++;
    }

    if( timeout == 3 ){
        return 0;   //if timeout failed, return 0
    }

		delay_ms(500);
    //  allocate memory for new password
    unsigned int*   newPass =   (unsigned int*) malloc(sizeof(unsigned int)*2);
    //  copy parity bits
    newPass[1]              =   PASSWORD_PARITY;
		newPass[0]							=		strtol(string,NULL,10);

    if(!passwordWrite(newPass)){  //if writing password to flash is successful
			  displaySuccess();   //display success graphics on LCD
				shutdown(); //clear out prompt inputs
				calculatorInit();   //allocate new memory location for inputs
        free(newPass);  //free memory allocated to hold new password
        return 0;
    }
		
    shutdown(); //clear out prompt inputs
    calculatorInit();   //allocate new memory location for inputs
		free(newPass);
    return 1;

}




