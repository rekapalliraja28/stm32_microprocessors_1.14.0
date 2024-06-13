#include "stm32f4xx.h"

void delay(uint32_t ms) {
    uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 2000; j++) {} // Adjust this loop for your clock frequency
}

int main(void) {
    uint8_t switch_press_count = 0;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN; // Enable GPIOA and GPIOC clock

    // Configure LED1 (PA5) and LED2 (PA7) pins as output
    GPIOA->MODER |= (1 << (5 * 2)) | (1 << (7 * 2));

    // Configure switch pin (PC13) as input
    GPIOC->MODER &= ~(3 << (13 * 2));

    while (1) {
        // Check if the switch is pressed
        if (!(GPIOC->IDR & (1 << 13))) {
            delay(50); // Debouncing
            switch_press_count++;

            switch (switch_press_count) {
                case 1:
                    GPIOA->ODR ^= (1 << 5); // Toggle LED1 once
                    for (int i = 0; i < 3; i++) {
                        GPIOA->ODR ^= (1 << 7); // Toggle LED2 three times
                        delay(200);
                    }
                    break;
                case 2:
                    for (int i = 0; i < 2; i++) {
                        GPIOA->ODR ^= (1 << 5); // Toggle LED1 twice
                        delay(200);
                    }
                    for (int i = 0; i < 6; i++) {
                        GPIOA->ODR ^= (1 << 7); // Toggle LED2 six times
                        delay(200);
                    }
                    break;
                case 3:
                    for (int i = 0; i < 3; i++) {
                        GPIOA->ODR ^= (1 << 5); // Toggle LED1 thrice
                        delay(200);
                    }
                    for (int i = 0; i < 9; i++) {
                        GPIOA->ODR ^= (1 << 7); // Toggle LED2 nine times
                        delay(200);
                    }
                    switch_press_count = 0; // Reset switch press count after every 3 presses
                    break;
                default:
                    break;
            }

            while (!(GPIOC->IDR & (1 << 13))) {} // Wait for the switch to be released
        }
    }
}
