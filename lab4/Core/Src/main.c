#include "main.h"

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

uint8_t button_press_count = 0;  // Счётчик нажатий кнопки

// Массив периодов для светодиодов (100 ms, 200 ms, 300 ms, 400 ms)
uint32_t led_periods[] = {99, 199, 299, 399};  // Начальные задержки для PD12, PD13, PD14, PD15

// Флаг для обработки нажатия кнопки с дебаунсингом
uint8_t button_pressed = 0;
uint8_t button_state = 0;  // Для отслеживания состояния кнопки (включена/выключена)

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
        // Чтение состояния кнопки (внешний пин PA0)
        button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

        // Проверяем, было ли нажатие кнопки (по спадающему фронту)
        if (button_state == GPIO_PIN_RESET && button_pressed == 0) {
            button_pressed = 1;  // Устанавливаем флаг, чтобы избежать повторных срабатываний

            // Увеличиваем счетчик нажатий кнопки
            button_press_count++;

            // Циклично сдвигаем значения периодов для всех светодиодов по часовой стрелке
            uint32_t temp = led_periods[3];  // Сохраняем последнее значение
            for (int i = 3; i > 0; i--) {
                led_periods[i] = led_periods[i - 1];  // Сдвигаем все значения на 1 вправо
            }
            led_periods[0] = temp;  // Переносим последнее значение в начало

            // Перезагружаем таймеры с новыми периодами
            htim2.Init.Period = led_periods[0];
            htim3.Init.Period = led_periods[1];
            htim4.Init.Period = led_periods[2];
            htim5.Init.Period = led_periods[3];

            HAL_TIM_Base_Stop_IT(&htim2);
            HAL_TIM_Base_Stop_IT(&htim3);
            HAL_TIM_Base_Stop_IT(&htim4);
            HAL_TIM_Base_Stop_IT(&htim5);

            HAL_TIM_Base_Init(&htim2);
            HAL_TIM_Base_Init(&htim3);
            HAL_TIM_Base_Init(&htim4);
            HAL_TIM_Base_Init(&htim5);

            HAL_TIM_Base_Start_IT(&htim2);
            HAL_TIM_Base_Start_IT(&htim3);
            HAL_TIM_Base_Start_IT(&htim4);
            HAL_TIM_Base_Start_IT(&htim5);
        }

        // Если кнопка отпущена, сбрасываем флаг
        if (button_state == GPIO_PIN_SET) {
            button_pressed = 0;
        }

        // Пауза, чтобы избежать перегрузки процессора
        HAL_Delay(10);  // Можно уменьшить значение, если система стабильна
    }
}

void SystemClock_Config(void)
{
    // Настройка системного тактирования
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Включаем тактирование порта D для светодиодов
    __HAL_RCC_GPIOD_CLK_ENABLE();

    // Включаем тактирование порта A для кнопки
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Настройка светодиодов (PD12, PD13, PD14, PD15)
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    // Настройка кнопки (PA0)
    GPIO_InitStruct.Pin = GPIO_PIN_0;  // Кнопка на PA0
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // Вход с кнопки
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void MX_TIM2_Init(void)
{
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 15999; // Для 1 кГц частоты
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = led_periods[0]; // Начальная задержка 100 ms
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim2);
}

static void MX_TIM3_Init(void)
{
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 15999; // Для 1 кГц частоты
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = led_periods[1]; // Начальная задержка 200 ms
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim3);
}

static void MX_TIM4_Init(void)
{
    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 15999; // Для 1 кГц частоты
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = led_periods[2]; // Начальная задержка 300 ms
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim4);
}

static void MX_TIM5_Init(void)
{
    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 15999; // Для 1 кГц частоты
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = led_periods[3]; // Начальная задержка 400 ms
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim5);
}

