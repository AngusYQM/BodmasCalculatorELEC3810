

//  main.c

//  CalculatorProject

//

//  Created by Angus Moore on 11/12/2018.

//  Copyright � 2018 Leeds.ac.uk. All rights reserved.

//

// Includes
#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include "Calculation.h"

#include "keypad.h"

#include "LCD.h"

#include "PLL.h"



//Arbitary values for left and right associativity

#define LEFT_ASSOCIATIVE 4

#define RIGHT_ASSOCIATIVE 5


int MAXSIZE = 100; //Max size an array can be, 100 is plenty of space.


char InputString[16]; //Input infix expression string array, 16 max due to LCD screen width

char operatorStack[16]; //Operator stack array

char RPNQue[50]; //Output reverse polish notation array, is longer due to added spacing in the string

char doubleConversionStack[16]; //Stack for converting RPN character strings into double values.

double evaluationStack[16]; //RPM evaluation array

char resultOutputString[16];


//End of array indicators

int topOperator = -1;

int endOfRPNOutputQue = -1;

int endOfInput = -1;

int topEvaluation = -1;

int topConversion = -1;

//Shift flag

int shiftFlag = 0;



///Operator stack functions///

int isOperatorStackEmpty(void){ //Check if the stack is empty, 1 if true, 0 if false

    

    if(topOperator == -1){//if top operator is equal to -1 then the stack is empty, return 1

        return 1;

    } else{

        return 0;

    }

    

}


int isOperatorStackFull(void){ //Check if the stack is full, 1 true, 0 if false

    

    if(topOperator == MAXSIZE){// if the top operator is equal to the max allowed size then stack is full

        return 1;

    } else{

        return 0;

    }

}


char topOperatorStackValue(void){ // Return the top value of the stack

    

    return operatorStack[topOperator];

    

}


char popOperatorStack(void){ // Pop the top element of the stack

    

    char topElement;

    

    if(!isOperatorStackEmpty()){

        topElement = operatorStack[topOperator];

        topOperator = topOperator-1;

        return topElement;

    } else{

        printf("Stack is empty\n");

    }

    return 0;

}


char pushOperatorStack(char pushOperatorValue){ //Push the value onto the top element of the stack

    

    if(!isOperatorStackFull()){

        topOperator = topOperator+1;

        operatorStack[topOperator] = pushOperatorValue;

    } else{

        printf("Stack is full\n");

    }

    return 0;

    

}


void clearOperatorStack(void){

    

    for(int i = 0; i <= topOperator; i++){

        operatorStack[i] = 0;

        

    }

    

    topOperator = -1;

}


///////Output que functions///////


int isOutputQueEmpty(void){ //Check if the stack is empty, 1 if true, 0 if false

    

    if(endOfRPNOutputQue == -1){

        return 1;

    } else{

        return 0;

    }

    

}


int isOutputQueFull(void){ //Check if the stack is full, 1 true, 0 if false

    

    if(endOfRPNOutputQue == MAXSIZE){

        return 1;

    } else{

        return 0;

    }

}


char addToOutputQue(char queValue){ //Add value to end of output que

    

    if(!isOutputQueFull()){

        endOfRPNOutputQue = endOfRPNOutputQue+1;

        RPNQue[endOfRPNOutputQue] = queValue;

    } else{

        printf("Que is full\n");

    }

    return 0;

}


char popOutputQue(void){ // Clear the output que

    

    char topElement;

    

    while(!isOutputQueFull()){

        topElement = RPNQue[endOfRPNOutputQue];

        endOfRPNOutputQue = endOfRPNOutputQue-1;

        return topElement;

    }

    

    return 0;

}


void clearOutputQue(void){

    

    for(int i = 0; i <= endOfRPNOutputQue; i++){

        RPNQue[i] = 0;

        

    }

    

    endOfRPNOutputQue = -1;

}



///Add keypad input into infix stack string functions///


int isInputStringFull(void){ //Check if the stack is full, 1 true, 0 if false

    

    if(endOfInput == MAXSIZE){

        return 1;

    } else{

        return 0;

    }

}


void infixInput(char keypadValue){ //Add input character to end of input string

    

    if(!isOutputQueFull()){

        endOfInput = endOfInput+1;

        InputString[endOfInput] = keypadValue;

    } else{

        printf("String is full\n");

    }

}


void clearInputString(void){

    

    for(int i = 0; i <= endOfInput; i++){

        InputString[i] = 0;

        

    }

    

    endOfInput = -1;

}



//RPN stacks////


int isEvaluationStackEmpty(void){ //Check if the stack is empty, 1 if true, 0 if false

    

    if(topEvaluation == -1){

        return 1;

    } else{

        return 0;

    }

    

}


int isEvaluationStackFull(void){ //Check if the stack is full, 1 true, 0 if false

    

    if(topEvaluation == MAXSIZE){

        return 1;

    } else{

        return 0;

    }

}


double topEvaluationStackValue(void){ // Return the top value of the stack

    

    double stackValue = evaluationStack[topEvaluation];

    return stackValue;

    

}


char popEvaluationStack(void){ // Pop the top element of the stack

    

    char topElement;

    

    if(!isEvaluationStackEmpty()){

        topElement = evaluationStack[topEvaluation];

        topEvaluation= topEvaluation-1;

        return topElement;

    } else{

        printf("Stack is empty\n");

    }

    return 0;

}


double pushEvaluationStack(double pushEvaluationValue){ //Push the converted double value onto the top element of the stack

    

    if(!isEvaluationStackFull()){

        topEvaluation = topEvaluation+1;

        evaluationStack[topEvaluation] = pushEvaluationValue;

    } else{

        printf("Stack is full\n");

    }

    return 0;

    

}


void clearEvaluationStack(void){

    

    for(int i = 0; i <= topEvaluation; i++){

        evaluationStack[i] = 0;

        

    }

    

    topEvaluation = -1;

}




void pushDoubleConversionStack(char pushConversionValue){ //Push the value onto the top element of the stack

    

        topConversion = topConversion+1;

        doubleConversionStack[topConversion] = pushConversionValue;


}


void clearDoubleConversionStack(void){

    

    for(int i = 0; i <= topConversion; i++){

        doubleConversionStack[i] = 0;

        

    }

    

    topConversion = -1;

}



//Infix to reverse polish notation functions//


int isOperator(char currentToken){

    

    switch(currentToken){

        case '+':

        case '-':

        case '*':

        case '/':

        case '^':

        case '%':

            return 1; //Return 1 if currentToken is an operator (1 = true);

            break;

        default:

            return 0; //Return 0 if not

            break;

            

    }


}


int operatorPriority(char operatorInput){ //Return the operator's priority

    

    int priority = 0;

    

    switch(operatorInput){

        case '^':

            priority = 4;

            break;

        case '*':

        case '/':

        case '%':

            priority = 3;

            break;

        case '+':

        case '-':

            priority = 2;

            break;

        case '(':

            priority = 1;

            break;

    }

    

    

    return priority;

    

}


int operatorAssociativity(char operatorInput){//Return the operators associativity

    

    switch (operatorInput) {

        case '^':

            return RIGHT_ASSOCIATIVE;

            break;

        case '*':

        case '/':

        case '+':

        case '-':

            return LEFT_ASSOCIATIVE;

            break;

        default:

            return 0;

            break;

    }

    

    

}



void convertInfixToRPN(void){ //Conversion of the input string to reverse polish notation by means of the shunting yard algorithm, this allows for calculation in line with BODMAS.


    

    for(int i = 0; i <= endOfInput; i++){ //Iterate through the input string, empty space is added between each operand and operator so as to allow for distinction between multi digit and floating point numbers when evaluating the RPN string.

        

        const char currentToken = InputString[i];

        

        if(isdigit(currentToken) || currentToken == '.'){

            

            if(isOperator(RPNQue[endOfRPNOutputQue])){

                addToOutputQue(' ');

            }

            addToOutputQue(currentToken);

        }

        

        

        else if(isOperator(currentToken)){

            

            addToOutputQue(' ');

            

            while(

                  ( (operatorPriority(topOperatorStackValue()) > operatorPriority(currentToken)) && (operatorAssociativity(currentToken) == RIGHT_ASSOCIATIVE) )

                  ||

                  ( (operatorPriority(topOperatorStackValue()) >= operatorPriority(currentToken)) && (operatorAssociativity(currentToken) == LEFT_ASSOCIATIVE) )

                 ){

                

                addToOutputQue(topOperatorStackValue());

                popOperatorStack();

                

            }

            

            pushOperatorStack(currentToken);

            

        }

        

        else if(currentToken == '('){

            

            pushOperatorStack(currentToken);

            

        }

        

        else if(currentToken == ')'){

            

            while(topOperatorStackValue() != '('){

                

                addToOutputQue(' ');

                addToOutputQue(topOperatorStackValue());

                popOperatorStack();

                

            }

            

            popOperatorStack(); //Discard left bracket, stack should be empty here

        }

        

        

    }


    

    while(!isOperatorStackEmpty()){

        

        addToOutputQue(' ');

        addToOutputQue(topOperatorStackValue());

        popOperatorStack();

        

    }

    


    

    

}



//RPN evaluation functions//

double performOperation(char operator, double operand1, double operand2){

    

    double result = 0;

    

    switch(operator){

        case '+':

            result = (operand1 + operand2);

            break;

        case '-':

            result = (operand1 - operand2);

            break;

        case '*':

            result = (operand1 * operand2);

            break;

        case '/':

            result = (operand1 / operand2);

            break;

        case '^':

            result = pow(operand1, operand2);

            break;

        default:

            break;

            

            

    }

    

    return result;

    

}


double evaluateRPN(void){// Evaluates the reverse polish notation string

    

    double result = 0;

    

    for (int i = 0; i <= RPNQue[i]; i++){

        

        char currentTokenRPN = RPNQue[i];

        

        if(isOperator(currentTokenRPN)){// if the curerent token is an operator then perform the operation on the top two operands in the evaluation stack.

         

            double num2 = (topEvaluationStackValue());

            popEvaluationStack();

            double num1 = (topEvaluationStackValue());

            popEvaluationStack();

            result = performOperation(currentTokenRPN, num1, num2); //Calculate

            pushEvaluationStack(result); //Add to evaluation stack

            

            

        }

        else if (isdigit(currentTokenRPN) || currentTokenRPN == '.'){ //If the current token is a digit or decimal place add to the double conversion stack.

            

            pushDoubleConversionStack(currentTokenRPN);

            

        }

        else if (currentTokenRPN == ' ' && !isOperator(RPNQue[i-1])){// If a space is encountered and the previous tokenis not an operator, then convert the string in the double conversion stack to a double and add it to the evaluation stack, then clear the double conversion stack.

            

            

            double convertedValue = atof(doubleConversionStack); //Converts the char string in the conversion stack into a double, allows for correct calculation

            pushEvaluationStack(convertedValue); // Push converted double to the evaluation stack.

            clearDoubleConversionStack(); // Clear the double conversion stack.

            

        }

    

    }

    

    popEvaluationStack();

    

    return result;

    

}



double calculate(void){ //Calculate function to call in main, return result of infix input expression
	
	char keybuffer = decodeKeyPress();

	if (keybuffer != '?'){ //Constant string of '?' coming in from the keypad decoding function, when a character that is not '?' is returned we know a key has been pressed.
		
		
		char pressedKey = keybuffer; // the pressed key is equal to the input on the keypad.
		
	 if(pressedKey == 's'){// If the shift key is pressed set the shift flag to 1.
			
			 shiftFlag = 1;
			
		}
		
       // If shift flag has been set and 1 is pressed then print the alternative button output to LCD and add it to the infix input.
	 if(shiftFlag == 1 && pressedKey == '1'){
		 pressedKey = '(';
		 LCD_WriteData(pressedKey);
		 infixInput(pressedKey);
		 shiftFlag = 0;
		 }
		
		
	 if(pressedKey == '2' && shiftFlag == 1){
		 pressedKey = ')';
		 LCD_WriteData(pressedKey);
		 infixInput(pressedKey);
		 shiftFlag = 0;
		 }

		
		
	 if(pressedKey == '3' && shiftFlag == 1){
		 pressedKey = '^';
		 LCD_WriteData(pressedKey);
		 infixInput(pressedKey);
		 shiftFlag = 0;
		 }
		 
		
	 if(pressedKey == '+' && shiftFlag == 1){
		 pressedKey = '*';
		 LCD_WriteData(pressedKey);
		 infixInput(pressedKey);
		 shiftFlag = 0;
		 }
		
		
	 if(pressedKey == '-' && shiftFlag == 1){
		 pressedKey = '/';
		 LCD_WriteData(pressedKey);
		 infixInput(pressedKey);
		 shiftFlag = 0;
		 }
		
		
	// If the key pressed is not =, C, s, or an alternative operator, then print it to the screen and add to the infix input.
	 else if(pressedKey != '=' && pressedKey != 'C' && pressedKey != 's' && pressedKey != '/' && pressedKey != '*' && pressedKey != '^' && pressedKey != ')' && pressedKey != '('){
			LCD_WriteData(pressedKey);
		    infixInput(pressedKey);
			SysTick_Wait(8000000);
		 
		 }



	
   if(pressedKey == '='){
    convertInfixToRPN(); //Convert infix to RPN
    double result = evaluateRPN(); //Evaluate the RPN
		snprintf(resultOutputString, 16, "%lf", result);
		LCD_GoTo(1,0);
		LCD_WriteRamString(resultOutputString);	//Print the result on the bottom row.
		SysTick_Wait(8000000);
   }
		
	 if(pressedKey == 'C'){ //If the cancel key is pressed clear the screen and all calculator stacks.
		 LCD_ClearScreen();
		 clearAllCalculatorStacks();
		 SysTick_Wait(8000000);
		 
	 }
	 
	 
	 SysTick_Wait(8000000);
	 
 }
	
SysTick_Wait(8000000);
 }	

void clearAllCalculatorStacks(void){ //Clear all stacks to default, filled with 0's, called when 'Clear' button is pressed on calculator

    

    clearOperatorStack();

    clearOutputQue();

    clearInputString();

    clearEvaluationStack();

    clearDoubleConversionStack();

    

}




