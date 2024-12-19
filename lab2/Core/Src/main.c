#include "stm32f4xx.h"

int main(void)
{
    uint32_t i;

    // Включаем тактирование порта GPIOD для светодиодов
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // Настроим пины GPIOD на выход (для светодиодов)
    GPIOD->MODER |= 0x55000000;   // Пины 12-15 на выход
    GPIOD->OTYPER &= ~0x0000;     // Выходы с подтягивающими резисторами
    GPIOD->OSPEEDR &= ~0x00000000; // Нормальная скорость

    while (1)
    {
        // Включаем светодиод по очереди
        for (i = 0; i < 4; i++) {
            GPIOD->ODR = (1 << (12 + i));  // Включаем светодиод
            for (volatile uint32_t delay = 0; delay < 500000; delay++) {}  // Задержка
            GPIOD->ODR &= ~(1 << (12 + i)); // Выключаем светодиод
            for (volatile uint32_t delay = 0; delay < 500000; delay++) {}  // Задержка
        }
    }
}
