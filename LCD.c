//#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "LCD.h"

	
/*
void LCD_init(void);                             // lcd initalise
void LCD_WriteCommand (unsigned char command);   // function to write command to the LCD
void LCD_ClearScreen(void);                      // to clear and home the LCD display
//void LCD_GoTo( int iRow, int iCol );          // to move the position of the couror to a specifick address
void LCD_WriteData(char c);                      // function to send the data to be displayed on the LCD
void LCD_WriteRamString(char *String);
void PORTA_Init(void);
void PORTB_Init(void);
*/
// PORTA initalise 
void PORTA_Init(void)
{
	  
//	delay = 
	  GPIO_PORTA_DIR_R = 0x0C;   // set PORTA pin 2,3 as output for control 
    GPIO_PORTA_DEN_R = 0x0C;   // set PORTA pin 2,3 as digital pins 
}

// PORTB initalise 
void PORTB_Init(void)
{
	  
	  GPIO_PORTB_DIR_R = 0x0F;   // set PORTB pin 0-3 as output for control 
    GPIO_PORTB_DEN_R = 0x0F;   // set PORTB pin 0-3 as digital pins 
}

// Pulse initalise 
void LCD_ENPulse(void)
{
   LCD_EN  = 0x04; // for high = 1
   SysTick_Wait(45);  // wait for 450 ns 
	
   LCD_EN  = 0x00; // for low = 0
	 SysTick_Wait(45);  //  wait for 450 ns 
}

// LCD initalise 
void LCD_init(void)
{	
    volatile unsigned long delay;
		SYSCTL_RCGC2_R |= 0x01;     // enable clock to GPIOA
		SYSCTL_RCGC2_R |= 0x02;     // enable clock to GPIOB 
		delay = SYSCTL_RCGC2_R;
		
	  PORTA_Init();
	  PORTB_Init();
	
	  SysTick_Wait(1600000);       // initialization sequence for 15ms
	
	  LCD_RS = 0x00;              // to set RS = 0
	  LCD_DB = (0x03);               // set the output to 0x3
	  LCD_ENPulse();
	  SysTick_Wait(4000000);     // wait 5 ms after the power is applied
	               // write 0011
	  LCD_ENPulse();
		SysTick_Wait(1600000);
		
	  
	  LCD_ENPulse();
		SysTick_Wait(400000);
	
	  LCD_DB = (0x02);  // 4-bit mode
	  LCD_ENPulse();
		SysTick_Wait(400000);
		
		LCD_WriteCommand(0x28);    //function set 4bits / 2line 5*7 font    
		SysTick_Wait(4000);
		
		//LCD_WriteCommand(0x06);     // move cursor right 	
    //SysTick_Wait(3200); 
		
		LCD_WriteCommand(0x0F);     // turn on display, cursor blinking    
		SysTick_Wait(4000);            
		
	  LCD_WriteCommand(0x06);     //automatic increment - no display shift    
		SysTick_Wait(4000);    
		
	
}

//function to write a command to the LCD
void LCD_WriteCommand (unsigned char command)
	{
	   //LCD_DB = command;
		 //LCD_RS_EN = 0x00;                  //  EN = 0, RS = 0
		 LCD_RS = 0x00;
		 SysTick_Wait(4000);                  // small delay 50us 
		
		 LCD_DB = (command & 0xF0) >> 4;      //DB = 1 ,high nibble of c
		 LCD_ENPulse();                       // write data to lcd
		 SysTick_Wait(400000);                // 5 ms delay for writting a command
	   
		 LCD_DB = (command & 0x0F);           // low nibble of command (EN = 0, RS = 0)
		 LCD_ENPulse();
		 SysTick_Wait(400000);                // 5ms delay for writting a command
	
}
	
// function to clear and home to LCD display
void LCD_ClearScreen(void)
  {
	   LCD_WriteCommand(0x01);          //clear display
	  // SysTick_Wait(128000);            // wait 1.6ms
		 LCD_WriteCommand(0x02);          // cursor to home
   SysTick_Wait(300000); 		        //wait 1.6ms
}		
	
//function to move the position of the cursor to a specific DDRAM 

void LCD_GoTo(int Row,int Col)
{

// Values of Row = 0,1 (16 x 2 LCD )
// Values of Col = 0 to 39 but 0 to 15 are in the visible area of the LCD 

	unsigned char	address;
	int				RowAddr = 0x00;
	
	if( 1 == Row ) RowAddr = 0x40;
	address = ( unsigned char ) (RowAddr + Col );
	LCD_WriteCommand( 0x80 | address );					// Set DDRAM address
} 

void LCD_ResetCursor(void){
	LCD_WriteCommand(0x80);
}
	 
	  

void LCD_WriteData (char c)
  {
	   
		 LCD_RS = 0x08;                    // EN = 0 , RS = 1 
		 SysTick_Wait(4000);               // wait for 6ms to write command
		
		 LCD_DB = (c & 0xF0) >> 4;         // EN = 1, RS = 1 high nipple
		 LCD_ENPulse();
		 SysTick_Wait(16000);              //wait 200us to write command
		
     LCD_DB = (c & 0x0F);             //EN = 1, RS = 0 low nipple
	   LCD_ENPulse();
		 SysTick_Wait(16000);             //wait 200us to write command
		
}


// write string of characters
// used for writing a string stored in ram
void LCD_WriteRamString(char *String)
   {
		 while(*String) {
			 LCD_WriteData(*String);
			 String++;
		 }	 
}
	 
