//

//  main.h

//  CalculatorProject

//

//  Created by Angus Moore on 11/12/2018.

//  Copyright © 2018 Leeds.ac.uk. All rights reserved.

//


#ifndef CALCULATION_H

#define CALCULATION_H


//PUBLIC FUNCTIONS

void infixInput(char keypadValue);

double calculate(void);

void clearAllCalculatorStacks(void);


//LOCAL FUNTIONS


//stdlib decleration

int isdigit(int c);

double strtod(const char *nptr, char **endptr);


//STACK FUNCTIONS


//Operator stack

int isOperatorStackEmpty(void);

int isOperatorStackFull(void);

char topOperatorStackValue(void);

char popOperatorStack(void);

char pushOperatorStack(char pushOperatorValue);

void clearOperatorStack(void);


//Output que stack

int isOutputQueEmpty(void);

int isOutputQueFull(void);

char addToOutputQue(char queValue);

char popOutputQue(void);

void clearOutputQue(void);


//Input string stack

int isInputStringFull(void);

void clearInputString(void);


//Evaluation stack

int isEvaluationStackEmpty(void);

int isEvaluationStackFull(void);

double topEvaluationStackValue(void);

char popEvaluationStack(void);

double pushEvaluationStack(double pushEvaluationValue);

void clearEvaluationStack(void);


//Double conversion stack

void pushDoubleConversionStack(char pushConversionValue);

void clearDoubleConversionStack(void);


//Operator, conversion and evaluation functions

int isOperator(char currentToken);

int operatorPriority(char operatorInput);

int operatorAssociativity(char operatorInput);

void convertInfixToRPN(void);

double performOperation(char operator, double operand1, double operand2);

double evaluateRPN(void);





#endif

