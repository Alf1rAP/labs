#include "main.h"

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM5_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();

    // Запуск таймеров с прерываниями
    HAL_TIM_Base_Start_IT(&htim2);  // Таймер для светодиода 1
    HAL_TIM_Base_Start_IT(&htim3);  // Таймер для светодиода 2
    HAL_TIM_Base_Start_IT(&htim4);  // Таймер для светодиода 3
    HAL_TIM_Base_Start_IT(&htim5);  // Таймер для светодиода 4

    while (1)
    {
        // Основной цикл можно оставить пустым, вся логика в прерываниях
    }
}

void SystemClock_Config(void)
{
    // Настройка системного тактирования
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOD_CLK_ENABLE(); // Включаем тактирование порта D для светодиодов

    // Настройка светодиодов
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

static void MX_TIM2_Init(void)
{
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 15999; // Для 1 кГц частоты (при частоте 16 МГц)
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 99; // 100 ms (1 кГц * 100 мс = 100)
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim2);
}

static void MX_TIM3_Init(void)
{
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 15999; // Для 1 кГц частоты
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 199; // 200 ms
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim3);
}

static void MX_TIM4_Init(void)
{
    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 15999; // Для 1 кГц частоты
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 299; // 300 ms
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim4);
}

static void MX_TIM5_Init(void)
{
    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 15999; // Для 1 кГц частоты
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = 399; // 400 ms
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim5);
}


