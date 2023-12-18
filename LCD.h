#ifndef LCD_H
#define LCD_H



#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
//#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
	
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
	
#define LCD_RS    (*((volatile unsigned long *)0x40004020))     //to set RS to PA3
#define LCD_EN    (*((volatile unsigned long *)0x40004010))     //to set EN to PA2
#define LCD_DB    (*((volatile unsigned long * )0x4000503C))   // to set (DB4-PB0 , DB5-PB1 ,DB6-PB2 , DB7-PB3)
	

void LCD_init(void);                             // lcd initalise
void PORTA_Init(void);                           // portA initalise
void PORTB_Init(void);                           // portB initalise
void LCD_WriteCommand (unsigned char command);   // function to write command to the LCD
void LCD_ClearScreen(void);                      // to clear and home the LCD display
//void LCD__GoTo (unsigned char address);          // to move the position of the couror to a specifick address
void LCD_WriteData(char c);                      // function to send the data to be displayed on the LCD
void SysTick_init(void);
void LCD_WriteRamString(char *String);
void LCD_ENPulse(void);
void LCD_ResetCursor(void);


#endif
