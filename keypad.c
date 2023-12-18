//#include "tm4c123ge6pm.h"
//#include <stdio.h> // standard C library // 
//#include "UART.h"
//#include "TExaS.h" 
#include "PLL.h"
#include "keypad.h"

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))	
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))	
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))	
#define GPIO_PORTE_CR_R       	(*((volatile unsigned long *)0x40024524))	
// input
#define PE0	                    (*((volatile unsigned long *)0x40024004 /*& 0x01*/))
#define PE1	                    (*((volatile unsigned long *)0x40024008 /*& 0x02*/))
#define PE2	                    (*((volatile unsigned long *)0x40024010 /*& 0x04*/))
#define PE3	                    (*((volatile unsigned long *)0x40024020 /* & 0x08*/))
	
#define PE01     (PE0 & 0x01)	 
#define PE11     (PE1 & 0x02)
#define PE21     (PE2 & 0x04)
#define PE31     (PE3 & 0x08)


#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))	
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))	
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))
#define GPIO_PORTD_CR_R       	(*((volatile unsigned long *)0x40007524))
	

// output
#define PD0	                    (*((volatile unsigned long *)0x40007004))
#define PD1	                    (*((volatile unsigned long *)0x40007008))
#define PD2	                    (*((volatile unsigned long *)0x40007010))
#define PD3	                    (*((volatile unsigned long *)0x40007020))
	
/*
#define N_col 4
#define N_row 4
	

unsigned char readKeypad(){

 unsigned char col_count =0,row_count=0;
 while(1)
 {
  for(col_count = 0;col_count < N_col; col_count++)
  {
 GPIO_PORTD_DATA_R = 1<<col_count;
   for(row_count = 0;row_count < N_row;row_count++)
   {
    if((GPIO_PORTE_DATA_R &(1<<(row_count+2))) != 0) 
    {
			SysTick_Wait(4000);
     return ((row_count*4)+col_count+1);     
    } 
   }
  }
 }
}
*/
char decodeKeyPress(void){
	//int c;
	//char ;   
	int column;
	for (column =0 ; column < 4; column++){
		  
		if (column == 0)
		{
				PD0 = 0x01; PD1 =0x00; PD2 = 0x00; PD3 = 0x00; 				// column 
			SysTick_Wait(4000);
			
			
					if(PE0 == 0x01){
					//key_value = '1';
					SysTick_Wait(4000);
					//break;
						while(PE0 == 0x01){
						return '1';
						}break;
					}	 //////////////////////////////////////////////////////////
				 if (PE1 == 0x02){
			    //key_value = '4';  
					SysTick_Wait(4000);
					 while(PE1 == 0x02){
					return '4';
					 }break;
					//printf("4\n");
				} if (PE2 == 0x04){
			    //key_value = '7';
				 SysTick_Wait(4000);
					while(PE2 == 0x04){
								return '7';
					}break;
					//printf("7\n");
				} if (PE3 == 0x08){
			    //key_value = '7';
				 SysTick_Wait(4000);
					while (PE3 == 0x08){
								return 'C';
					}break;
					//printf("7\n");
				}
		}
		
				  
		if (column == 1)
		{
				PD0 = 0x00; PD1 =0x02; PD2 = 0x00; PD3 = 0x00; 				// column 
			SysTick_Wait(4000);
			
			
					if(PE0 == 0x01){
					//key_value = '1';
					SysTick_Wait(4000);
					//break;
						while(PE0 == 0x01){
						return '2';
						}break;
					}	 //////////////////////////////////////////////////////////
				 if (PE1 == 0x02){
			    //key_value = '4';  
					SysTick_Wait(4000);
					 while(PE1 == 0x02){
					return '5';
					 }break;
					//printf("4\n");
				} if (PE2 == 0x04){
			    //key_value = '7';
				 SysTick_Wait(4000);
					while(PE2 == 0x04){
								return '8';
					}break;
					//printf("7\n");
				} if (PE3 == 0x08){
			    //key_value = '7';
				 SysTick_Wait(4000);
					while (PE3 == 0x08){
								return '0';
					}break;
					//printf("7\n");
				}
		}
		
		if (column == 2)
		{
				PD0 = 0x00; PD1 =0x00; PD2 = 0x04; PD3 = 0x00; 				// column 
			SysTick_Wait(4000);
			
			
					if(PE0 == 0x01){
					//key_value = '1';
					SysTick_Wait(4000);
					//break;
						while(PE0 == 0x01){
						return '3';
						}break;
					}	 //////////////////////////////////////////////////////////
				 if (PE1 == 0x02){
			    //key_value = '4';  
					SysTick_Wait(4000);
					 while(PE1 == 0x02){
					return '6';
					 }break;
					//printf("4\n");
				} if (PE2 == 0x04){
			    //key_value = '7';
				 SysTick_Wait(4000);
					while(PE2 == 0x04){
								return '9';
					}break;
		
				} if (PE3 == 0x08){
			 
				 SysTick_Wait(4000);
					while (PE3 == 0x08){
								return '.';
					}break;
		
				}
			}
				
				
						if (column == 3)
		{
				PD0 = 0x00; PD1 =0x00; PD2 = 0x00; PD3 = 0x08; 				// column 
			SysTick_Wait(4000);
			
			
					if(PE0 == 0x01){
				
					SysTick_Wait(4000);

						while(PE0 == 0x01){
						return '+';
						}break;
					}	 
				 if (PE1 == 0x02){
					 
					SysTick_Wait(4000);
					 while(PE1 == 0x02){
					return '-';
					 }break;

				} if (PE2 == 0x04){
				 SysTick_Wait(4000);
					while(PE2 == 0x04){
								return 's';
					}break;
					
				} if (PE3 == 0x08){
				 SysTick_Wait(4000);
					while (PE3 == 0x08){
								return '=';
					}break;
				}
		}
		}
		
 return '?';
}

void PortE_Init(void){ unsigned long volatile delay;
   SYSCTL_RCGC2_R |= 0x10;            // Port E clock
   delay = SYSCTL_RCGC2_R;            // wait 3-5 bus cycles
	 GPIO_PORTE_CR_R = 0x0F;            // PE3,2,1,0 input 
	 GPIO_PORTE_DIR_R = 0x00;           // PE3,2,1,0 input 
	 GPIO_PORTE_AFSEL_R = 0x00;       
	 GPIO_PORTE_AMSEL_R = 0x00;       
	 GPIO_PORTE_PCTL_R = 0x00000000;
	 GPIO_PORTE_DEN_R = 0x0F; 
	 GPIO_PORTE_PDR_R  = 0x0F;           //pull down means 1&1 button is pressed
}

void PortD_Init(void){ unsigned long volatile delay;
	 SYSCTL_RCGC2_R |= 0x08;            // Port D clock
   delay = SYSCTL_RCGC2_R;            // wait 3-5 bus cycles
	 GPIO_PORTD_CR_R = 0x0F;  
	 GPIO_PORTD_DIR_R = 0x0F;   
	 GPIO_PORTD_AFSEL_R = 0x00; 
	 GPIO_PORTD_AMSEL_R = 0x00; 
	 GPIO_PORTD_PCTL_R = 0x0000FFFF;
	 GPIO_PORTD_DEN_R = 0x0F;  
}
