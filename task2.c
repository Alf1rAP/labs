#include <stdio.h>
#include <string.h>

struct microcontroller {
    char name[20];
    int flashMemory;      // В килобайтах
    int sram;             // В килобайтах
    float clockSpeed;     // В мегагерцах
};

int main() {
    // Инициализация структуры
    struct microcontroller stm32 = {"STM32F407VG", 1024, 192, 168.0};

    // Вывод начальных данных структуры
    printf("Microcontroller Characteristics:\n");
    printf("Name: %s\n", stm32.name);
    printf("Flash Memory: %d KB\n", stm32.flashMemory);
    printf("SRAM: %d KB\n", stm32.sram);
    printf("Clock Speed: %.1f MHz\n", stm32.clockSpeed);

    // Модификация данных структуры
    stm32.flashMemory = 2048;  // Увеличиваем flash память
    stm32.sram = 256;          // Увеличиваем SRAM
    stm32.clockSpeed = 180.0;  // Меняем частоту

    // Вывод изменённых данных структуры
    printf("\nModified Microcontroller Characteristics:\n");
    printf("Name: %s\n", stm32.name);
    printf("Flash Memory: %d KB\n", stm32.flashMemory);
    printf("SRAM: %d KB\n", stm32.sram);
    printf("Clock Speed: %.1f MHz\n", stm32.clockSpeed);

    return 0;
}
