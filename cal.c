#include "cal.h"
#include "PLL.h"
#include "LCD.h"
#include "keypad.h"
#include <math.h>
#include <stdio.h>
#include <ctype.h>
	
void cal(){
	
	char input[16] = {0};
	char key_value = 0;
	char res[16];
	float num1 = 0,num2 = 0;
	float result = 0;
	unsigned char count = 0, operator_ ;
	unsigned char i = 0,operator_index = 0,equal_index;
	int temp, temp2;
	//char result1, result2;
	key_value = decodeKeyPress();
	//float Numbers[10];
	
	while( key_value != '=') //read opearnds and operator from user
  {
		if (key_value != '?'){
			
			 //display inputs on LCD display
			SysTick_Wait(8000000);
			
			if(isdigit(key_value)){
				LCD_WriteData(key_value);
				input[count] = key_value; //save inputs
				SysTick_Wait(8000000);
				count++;
			}
			
			else if (operator_index == 0 && key_value == '+') //check the opearator
			{
				LCD_WriteData(key_value);
				operator_ = 1;
				operator_index = count;
				count++;
			}
			else if(operator_index == 0 && key_value == '-')
			{
				LCD_WriteData(key_value);
				operator_ = 2;
				// LCD_WriteData('=');
				operator_index = count;
				count++;
			}
			else if(operator_index == 0 && key_value == '*')
			{
				LCD_WriteData(key_value);
				operator_ = 3;
				operator_index = count;
				count++;
			}
			else if(operator_index == 0 && key_value == '/')
			{ 
				LCD_WriteData(key_value);
				operator_ = 4;
				operator_index = count;
				count++;
			}
			else if (key_value == 'C') //check the opearator
			{
				LCD_ClearScreen();
				LCD_ResetCursor();
			}
		}
		
		//while( decodeKeyPress() != '?');
  //LCD_WriteData('=');
		key_value = decodeKeyPress();
	}
	if(key_value == '='){
    LCD_WriteData(key_value);
		equal_index = count;
	}
	


//get the first operand
	for(i=0;i<operator_index; i++)
	{ 
		temp= input[i]-'0'; //char to int
		num1 += (temp)*(pow(10,(operator_index-i-1)));
		
	}
	printf("The Number1 is %f \n",num1);
	
	for(i=operator_index + 1; i < count; i++)
	{ 
		temp= input[i]-'0'; //char to int
		num2 += (temp)*(pow(10,(count-i-1)));
		
	}
 /////////////////////////////////////////////////////////////////////////////////////// 
  //get the second operand
 /* for(int j=operator_index+2;j<equal_index+1;j++)
  { 
		temp2= input[j]-'0'; //char to int
    num2 += (temp2)*(pow(10,(equal_index-j-1)));
  }*/
////////////////////////////////////////////////////////////////////////////////////////  
  switch(operator_)
  {
   case 1:
    result = num1+num2;
    break;
	 
   case 2:
    //if(num1>num2)
     result = num1-num2;
    //else 
    //{
	 //SysTick_Wait(8000000);
     //result = num2-num1;
    //}
    break;
		
   case 3:
	
    result = num1*num2;
    break;
	 
   case 4:
		 if(num2 == 0){
				LCD_ClearScreen();
				LCD_ResetCursor();
			 
				LCD_WriteRamString("Error");
			 
				while( decodeKeyPress() != '?');
				while( decodeKeyPress() == '?');
				
				LCD_ClearScreen();
				LCD_ResetCursor();
			 return;
		 }
    result = num1/num2;
    break;
  }
	
	snprintf(res, sizeof(res), "%.3f", result);
	
	LCD_WriteRamString(res);
	
	while( decodeKeyPress() != '?');
	while( decodeKeyPress() == '?');
	
	LCD_ClearScreen();
	LCD_ResetCursor();
	 SysTick_Wait(8000000);
}

   