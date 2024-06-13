#include "stm32f4xx.h"                  // Device header
#define infinte 1

void delayMs(int seconds);

int main(void)
{

	RCC->AHB1ENR |= 1;                   // Enable AHB1 BUS which is connected to PA5 via GPIO port A
	GPIOA->MODER |= 0x400;               // in bits 0000 0000 0000 0000 0000 0100 0000 0000 as output mode

	while(infinte)
	{

		GPIOA->BSRR |=1<<5;               //ODR corresponding to BSRR Set
		delayMs(500);
		GPIOA->BSRR |=1<<21;				//ODR reset corresponding to bsrr
		delayMs(500);
	}

}

void delayMs(int seconds)
{

	for(;seconds>0;seconds--)
		for(int count1=0;count1<3000;count1++);

}
