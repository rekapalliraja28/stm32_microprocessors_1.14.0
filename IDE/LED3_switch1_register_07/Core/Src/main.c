#include "stm32f4xx.h"

#define DEBOUNCE_DELAY 100

void delay(int milliseconds);

int main(void)
{
    //int switchState = 0; // Variable to store the state of the switch press
    int numPresses = 0; // Variable to store the number of times the switch is pressed

    // Enable clock for GPIOA and GPIOB
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;

    // Configure PA7, PA8, and PA9 as output (LEDs)
    GPIOA->MODER |= GPIO_MODER_MODE7_0 | GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0;

    // Configure PB8 as input (Switch)
    GPIOB->MODER &= ~(GPIO_MODER_MODE8_Msk);  // Clear the bits for PB8

    while(1)
    {
        if(GPIOB->IDR & GPIO_IDR_ID8)
        {
            delay(DEBOUNCE_DELAY); // Debounce delay

            if(GPIOB->IDR & GPIO_IDR_ID8) // Check again if the switch is still pressed
            {
                numPresses++; // Increment number of presses

                switch (numPresses)
                {
                    case 1:
                        GPIOA->BSRR |= GPIO_BSRR_BS7;
                        delay(DEBOUNCE_DELAY);
                        GPIOA->BSRR |= GPIO_BSRR_BR7;
                        break;
                    case 2:
                        GPIOA->BSRR |= GPIO_BSRR_BS8;
                        delay(DEBOUNCE_DELAY);
                        GPIOA->BSRR |= GPIO_BSRR_BR8;
                        break;
                    case 3:
                        GPIOA->BSRR |= GPIO_BSRR_BS9;
                        delay(DEBOUNCE_DELAY);
                        GPIOA->BSRR |= GPIO_BSRR_BR9;
                        break;
                    default:
                        numPresses = 0; // Reset numPresses after the third press
                        GPIOA->BSRR |= GPIO_BSRR_BR7 | GPIO_BSRR_BR8 | GPIO_BSRR_BR9; // Turn off all LEDs
                        break;
                }
            }

            while(GPIOB->IDR & GPIO_IDR_ID8); // Wait until the switch is released
        }
    }

    return 0;
}

// Simple delay function
void delay(int milliseconds)
{
    for(int i = 0; i < milliseconds * 1000; i++);
}
