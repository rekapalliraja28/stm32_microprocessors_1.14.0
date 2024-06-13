#include "stm32f4xx.h"                  // Device header
#define infinte 1

void delay(int seconds);

int main(void)
{
	RCC->AHB1ENR |= 0x1;                     // Enable AHB1 BUS which is connected to PA5 via GPIO port A
	RCC->AHB1ENR |= 0x4;                      // Enable AHB1 BUS which is connected to PC13 via GPIO port C
	GPIOA->MODER |= 0x400;                  // enable PA5 as output pin

	while(infinte)
		{

			if((GPIOC->IDR & 0x2000)==0)					//digitalWrite (13,HIGH)
			{
					delay(100);
					GPIOA->BSRR |=0x20;               //ODR corresponding to BSRR Set
			}

			else
			{
				delay(100);
				GPIOA->BSRR |=0x200000;					//ODR corresponding to BSRR RESet
			}
		}

}

void delay(int seconds)
{

	for(;seconds>0;seconds--)
		for(int count1=0;count1<3000;count1++);

}
