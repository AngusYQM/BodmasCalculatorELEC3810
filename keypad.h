#ifndef keypad_H
#define keypad_H

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
	
void PortE_Init(void);
void PortD_Init(void);
//void PLL_Init(void);

unsigned char readKeypad(void);
char decodeKeyPress(void);
//void SysTick_Wait(unsigned long);
//void SysTick_Init(void);

#endif
	
