#include "stm32f4xx_hal.h"

// Define GPIO pin mappings for seven-segment display segments
#define SEG_A_PIN GPIO_PIN_0
#define SEG_B_PIN GPIO_PIN_1
#define SEG_C_PIN GPIO_PIN_2
#define SEG_D_PIN GPIO_PIN_3
#define SEG_E_PIN GPIO_PIN_4
#define SEG_F_PIN GPIO_PIN_5
#define SEG_G_PIN GPIO_PIN_6

// Function prototypes
void displayDigit(uint8_t digit);

int main(void) {
    HAL_Init();
    // Initialize the GPIO peripherals
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = SEG_A_PIN | SEG_B_PIN | SEG_C_PIN | SEG_D_PIN | SEG_E_PIN | SEG_F_PIN | SEG_G_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Loop to display numbers from 0 to 9
    while (1) {
        for (uint8_t i = 0; i <= 9; ++i) {
            displayDigit(i);
            HAL_Delay(1000); // Adjust delay as needed
        }
    }
}

void displayDigit(uint8_t digit) {
    // Define seven-segment patterns for each digit
    const uint8_t patterns[] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111  // 9
    };

    // Set GPIO pins according to the pattern for the given digit
    HAL_GPIO_WritePin(GPIOA, SEG_A_PIN, (patterns[digit] >> 0) & 1);
    HAL_GPIO_WritePin(GPIOA, SEG_B_PIN, (patterns[digit] >> 1) & 1);
    HAL_GPIO_WritePin(GPIOA, SEG_C_PIN, (patterns[digit] >> 2) & 1);
    HAL_GPIO_WritePin(GPIOA, SEG_D_PIN, (patterns[digit] >> 3) & 1);
    HAL_GPIO_WritePin(GPIOA, SEG_E_PIN, (patterns[digit] >> 4) & 1);
    HAL_GPIO_WritePin(GPIOA, SEG_F_PIN, (patterns[digit] >> 5) & 1);
    HAL_GPIO_WritePin(GPIOA, SEG_G_PIN, (patterns[digit] >> 6) & 1);
}
