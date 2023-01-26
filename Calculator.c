#include "Calculator.h"

char symbols[] = "E^/x+-";

char*       string;
int         cursor_position;

float*      values;
int         valcount;

char*       operators;
int         opcount;

float*      output;


void    calculatorInit(void){
    //allocate memory to hold user string input
    string                  =   (char*)     malloc(STRINGLEN*sizeof(char));
    cursor_position         =   0;
    string[cursor_position] =   'x';    //set first value to 'x'

    //array to store float values pulled from string
    values                  =   (float*)    calloc(((STRINGLEN-2)/2), sizeof(float));
    valcount                =   0;

    //array to store char values of operators pulled from string
    operators               =   (char*)     calloc(((STRINGLEN-2)/2), sizeof(char));
    opcount                 =   0;

    //allocate memory to store output
    output                  =   (float*)    malloc(sizeof(float));
}


int     calculatorRun(int inputLimit){

    //set cursor display to active
    lcdCursorControl(1);

    //allocate memory for key
    char* key = (char*) malloc(sizeof(char));

    while(1){
        key[0] = readKeypad();
        if(key[0] == '*'){
            break;
        }
        if(key[0] != 'n') {
            if (cursor_position > 15 && !lcd_line_toggle) {
                //if cursor moves past last character in first line
                lcdNextLine();
            }
            if(cursor_position < 16 && lcd_line_toggle){
                //if cursor moves behind first character in second line
                lcdNextLine();
            }

            if (cursor_position > inputLimit) {
                //if cursor moves past '32' characters, only accept termination
                // character/remove character command
                while (key[0] != '*' && key[0] != '#') {
                    key[0] = readKeypad();
                    if (key[0] == 'D') {    //accept shift command to erase entire string
                        processInput(key[0]);
                    }
                }
            }
            processInput(key[0]); //process input
        }
        delay_ms(110);
    }

    string[cursor_position] = '\0';
    free(key);

    lcdClearScreen();

    lcdCursorControl(0);

    if(parseInput()){
        return  1;
    }   else{
        return  0;
    }
}


int     trigRun(int choice){

    lcdClearScreen(); //clear screen

    switch (choice) {   //perform different trig functions on output based off menu choice
        case 1:{
            lcdWriteAlphaSmall('s');
            lcdWriteAlphaSmall('i');
            lcdWriteAlphaSmall('n');
            lcdWriteSymbol('(');
            break;
        }
        case 2:{
            lcdWriteAlphaSmall('c');
            lcdWriteAlphaSmall('o');
            lcdWriteAlphaSmall('s');
            lcdWriteSymbol('(');
            break;
        }
        case 3:{
            lcdWriteAlphaSmall('t');
            lcdWriteAlphaSmall('a');
            lcdWriteAlphaSmall('n');
            lcdWriteSymbol('(');
            break;
        }
        case 4:{
            lcdWriteAlphaSmall('s');
            lcdWriteAlphaSmall('i');
            lcdWriteAlphaSmall('n');
            lcdWriteAlphaSmall('h');
            lcdWriteSymbol('(');
            break;
        }
        case 5:{
            lcdWriteAlphaSmall('c');
            lcdWriteAlphaSmall('o');
            lcdWriteAlphaSmall('s');
            lcdWriteAlphaSmall('h');
            lcdWriteSymbol('(');
            break;
        }
        case 6:{
            lcdWriteAlphaSmall('t');
            lcdWriteAlphaSmall('a');
            lcdWriteAlphaSmall('n');
            lcdWriteAlphaSmall('h');
            lcdWriteSymbol('(');
            break;
        }
        default:{
            break;
        }
    }

    if(!calculatorRun(MAXTRIG_INPUT)){
        return  0;
    }   else{
        //compute final output based on choice
        switch (choice) {
            case 1:{
                *output  =   (float)sin((double)*output);
                break;
            }
            case 2:{
                *output  =   (float)cos((double)*output);
                break;
            }
            case 3:{
                *output  =   (float)tan((double)*output);
                break;
            }
            case 4:{
                *output  =   (float)sinh((double)*output);
                break;
            }
            case 5:{
                *output  =   (float)cosh((double)*output);
                break;
            }
            case 6:{
                *output  =   (float)tanh((double)*output);
                break;
            }
            default:{
                break;
            }
        }

        return 1;
    }


}


void    processInput(char key){
    //process different inputs based on user input
    switch (key){
        case '0':{
            lcdWriteData(key);
            if(!shift_toggle) {
                string[cursor_position++] = key;
            } else{
                string[cursor_position++] = '^';
                shift_toggle = !shift_toggle;
            }
            break;
        }
        case '1' ... '9':{
            lcdWriteData(key);
            string[cursor_position++] = key;
            break;
        }
        case 'A':{
            lcdWriteData(key);
            if(!shift_toggle) {
                string[cursor_position++] = '+';
            } else{
                string[cursor_position++] = 'x';
                shift_toggle = !shift_toggle;
            }
            break;
        }
        case 'B':{
            lcdWriteData(key);
            if(!shift_toggle) {
                string[cursor_position++] = '-';
            } else{
                string[cursor_position++] = '/';
                shift_toggle = !shift_toggle;
            }
            break;
        }
        case 'C':{
            lcdWriteData(key);
            if(!shift_toggle) {
                string[cursor_position++] = '.';
            } else{
                string[cursor_position++] = 'E';
                shift_toggle = !shift_toggle;
            }
            break;
        }
        case 'D':{
            shift_toggle = !shift_toggle;
            break;
        }
        case '*':{
            string[--cursor_position] = key;
            break;
        }
        case '#':{
            if(!shift_toggle) {
                lcdClearLast();
                string[--cursor_position] = '\0';
            } else{
                cursor_position = 0;
                free(string);
                string = (char *) malloc(STRINGLEN*sizeof(char));
                lcdClearScreen();
                shift_toggle = !shift_toggle;
            }
            break;
        }
        default:{
            break;
        }
    }
}


int     is_symbol(char c){
    //check if input char is a symbol
    int i = 0;
    while(symbols[i] != '\0'){
        if(c == symbols[i]){
            return 1;
        }
        i++;
    }
    return 0;
}


int     errorCheck(void){

    //grammatically, every operator should have a value before and after it;
    // hence valcount is always 1 + opcount
    if(valcount != opcount + 1){
        if(valcount != 1) {
            return 0;
        }
        if(opcount > 0){
            return 0;
        }
        return 1;
    }
    return 1;
}


void    parseDigit(int* i){
    char tmp[(STRINGLEN-2)/2];  //  tmp value store for parsing digit
    int t = 0;
    memset(tmp,0,sizeof(tmp));  //fill tmp with 0s

    if( string[i[0]] == '-'){   //accept negative values
        tmp[t++] = string[i[0]++];
    }
    if( string[i[0]] == '.') {  //if first value is '.', append a 0 to keep with mathematical practise
        tmp[t++] = '0';
        tmp[t++] = '.';

        while ( isdigit(string[i[0]]) && t < ((STRINGLEN-2)/2)){ //while string is less than maximum compute size
            tmp[t++] = string[i[0]++];
        }
    }   else{
        while ( isdigit(string[i[0]]) || string[i[0]] == '.'){
            if(t < ((STRINGLEN-2)/2)) {
                tmp[t++] = string[i[0]++];
            }
        }
    }

    tmp[t] = '\0';
    values[valcount++] = strtof(tmp,NULL);  //convert string to float and store in vals
}


void    tokenize(void){

    //converts input string into tokens of values and operators
    int* i = (int*)malloc(sizeof(int));
    i[0] = 0;

    //if the string begins with a +/-, append 0 to maintain arithmetic integrity
    if(string[0] == '+' || string[0] == '-'){
        values[valcount++] = 0;
    }
    while(string[i[0]] != '\0'){    //read whole string
        if( is_symbol(string[i[0]]) ){  //if symbol,
            if(string[i[0]] == '-'){
                operators[opcount++] = '+';
                parseDigit(i);
            }
            else{
                operators[opcount++] = string[i[0]++];
            }
        }
        if( string[i[0]] == '.'){   //if decimal point
            parseDigit(i);
        }
        if( isdigit(string[i[0]])){ //if value
            parseDigit(i);
        }
    }
    free(i);
}


int     parseInput(void){
    //parse the input string
    tokenize(); //convert string to tokens

    if(errorCheck()){   //check for errors in input
        //parse following PEDMAS rules
        for (int i = 0; i < opcount; i++) {
            if (operators[i] == 'E') {
                values[i] = values[i] * powf(10, values[i + 1]);
                values[i + 1] = 0;
            }
        }
        for (int i = 0; i < opcount; i++) {
            if (operators[i] == '^') {
                if(values[i] < 0){
                    values[i]   =   0;
                }
                values[i] = powf(values[i], values[i + 1]);
                values[i + 1] = 0;
            }
        }
        for (int i = 0; i < opcount; i++) {
            if (operators[i] == '/') {
                values[i] = values[i] / values[i + 1];
                values[i + 1] = 0;
            }
        }
        for (int i = 0; i < opcount; i++) {
            if (operators[i] == 'x') {
                values[i] = values[i] * values[i + 1];
                values[i + 1] = 0;
            }
        }
        for (int i = 0; i < opcount; i++) {
            if (operators[i] == '+') {
                values[i] = values[i] + values[i + 1];
                values[i + 1] = 0;
            }
        }
        for (int i = 0; i < opcount; i++) {
            if (operators[i] == '-') {
                values[i] = values[i] - values[i + 1];
                values[i + 1] = 0;
            }
        }

        *output = 0;
        for (int i = 0; i < valcount; i++) {    //sum all remaining values to get output
            *output += values[i];
        }

        return 1;

    }   else{
        return 0;
    }

}


void    printOutput(void){

    //display output to LCD
    char tmp[STRINGLEN];
    sprintf(tmp, "%7.7f", *output);

    lcdWriteSymbol('=');
    for (int i = 0; i < 8; i++) {
        if (tmp[i] == '.' || tmp[i] == '-') {
            lcdWriteSymbol(tmp[i]);
        } else {
            lcdWriteNumeric(tmp[i]);
        }
    }
}


void    shutdown(void){
    //free allocated memory to arrays and value stores
    free(string);
    free(values);
    free(operators);
    free(output);
}