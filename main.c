#include "PLL.h"
#include "LCD.h"
#include "keypad.h"
#include "cal.h"
#include "Calculation.h"
#include "UART.h"
#include <stdio.h>





int main(void)
{	

	PLL_Init();
	SysTick_Init();
	UART_Init();
	
  LCD_init();	
	PortE_Init();
	PortD_Init();
	SysTick_Wait(400000); 
	LCD_ClearScreen();
	SysTick_Wait(400000);

	
	LCD_WriteRamString("Calculator");
	SysTick_Wait(18000000);
	LCD_ClearScreen();
	
	
while(1){

	calculate();
	SysTick_Wait(8000000);
 
		
	}

}

	
