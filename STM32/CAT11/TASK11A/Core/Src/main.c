/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : CAT 11 - TASK 11A: ESP8266 TCP Server Configuration
  * Target Device   : STM32F401RET6 (NUCLEO-F401RE, ARM Cortex-M4 @ 84 MHz)
  * Hardware        : Wemos D1 WiFi Module (ESP8266) + STM32 NUCLEO Board
  * Pin Map         : PA2  -> USART2 TX (ST-LINK Virtual COM Debug @ 115200)
  *                   PA3  -> USART2 RX (ST-LINK Virtual COM Debug @ 115200)
  *                   PA9  -> USART1 TX (ESP8266 RX @ 115200)
  *                   PA10 -> USART1 RX (ESP8266 TX @ 115200)
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

typedef enum {
  SERVER_STATE_INIT = 0,
  SERVER_STATE_TEST_AT,
  SERVER_STATE_SET_MODE,
  SERVER_STATE_JOIN_WIFI,
  SERVER_STATE_GET_IP,
  SERVER_STATE_SET_MUX,
  SERVER_STATE_START_SERVER,
  SERVER_STATE_RUNNING
} Server_State_t;

Server_State_t server_state = SERVER_STATE_INIT;
uint32_t state_tick = 0;
uint8_t esp_byte = 0;
uint8_t pc_byte = 0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

int main(void)
{
  char *banner = "\r\n===============================================\r\n"
                 " CAT 11 - TASK 11A: ESP8266 TCP Server Bring-Up\r\n"
                 "===============================================\r\n";
  uint32_t now = 0;

  char cmd_at[]     = "AT\r\n";
  char cmd_mode[]   = "AT+CWMODE=1\r\n";
  char cmd_join[]   = "AT+CWJAP=\"SNUC\",\"snu12345\"\r\n";
  char cmd_ip[]     = "AT+CIFSR\r\n";
  char cmd_mux[]    = "AT+CIPMUX=1\r\n";
  char cmd_server[] = "AT+CIPSERVER=1,80\r\n";

  char log_at[]     = "[1/6] Sending AT ping to ESP8266...\r\n";
  char log_mode[]   = "[2/6] Configuring Station Mode (AT+CWMODE=1)...\r\n";
  char log_join[]   = "[3/6] Connecting to Wi-Fi SSID 'SNUC'...\r\n";
  char log_ip[]     = "[4/6] Querying Station IP Address (AT+CIFSR)...\r\n";
  char log_mux[]    = "[5/6] Enabling Multiple Connections (AT+CIPMUX=1)...\r\n";
  char log_server[] = "[6/6] Starting TCP Server on Port 80 (AT+CIPSERVER=1,80)...\r\n";
  char log_ready[]  = "\r\n[SUCCESS] TCP Server running on Port 80! Waiting for client HTTP requests...\r\n";

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  HAL_UART_Transmit(&huart2, (uint8_t *)banner, strlen(banner), HAL_MAX_DELAY);
  state_tick = HAL_GetTick();

  while (1)
  {
    now = HAL_GetTick();

    switch (server_state)
    {
      case SERVER_STATE_INIT:
        if (now - state_tick > 1000)
        {
          HAL_UART_Transmit(&huart2, (uint8_t *)log_at, strlen(log_at), 100);
          HAL_UART_Transmit(&huart1, (uint8_t *)cmd_at, strlen(cmd_at), 100);
          server_state = SERVER_STATE_TEST_AT;
          state_tick = now;
        }
        break;

      case SERVER_STATE_TEST_AT:
        if (now - state_tick > 1000)
        {
          HAL_UART_Transmit(&huart2, (uint8_t *)log_mode, strlen(log_mode), 100);
          HAL_UART_Transmit(&huart1, (uint8_t *)cmd_mode, strlen(cmd_mode), 100);
          server_state = SERVER_STATE_SET_MODE;
          state_tick = now;
        }
        break;

      case SERVER_STATE_SET_MODE:
        if (now - state_tick > 1000)
        {
          HAL_UART_Transmit(&huart2, (uint8_t *)log_join, strlen(log_join), 100);
          HAL_UART_Transmit(&huart1, (uint8_t *)cmd_join, strlen(cmd_join), 100);
          server_state = SERVER_STATE_JOIN_WIFI;
          state_tick = now;
        }
        break;

      case SERVER_STATE_JOIN_WIFI:
        if (now - state_tick > 5000)
        {
          HAL_UART_Transmit(&huart2, (uint8_t *)log_ip, strlen(log_ip), 100);
          HAL_UART_Transmit(&huart1, (uint8_t *)cmd_ip, strlen(cmd_ip), 100);
          server_state = SERVER_STATE_GET_IP;
          state_tick = now;
        }
        break;

      case SERVER_STATE_GET_IP:
        if (now - state_tick > 2000)
        {
          HAL_UART_Transmit(&huart2, (uint8_t *)log_mux, strlen(log_mux), 100);
          HAL_UART_Transmit(&huart1, (uint8_t *)cmd_mux, strlen(cmd_mux), 100);
          server_state = SERVER_STATE_SET_MUX;
          state_tick = now;
        }
        break;

      case SERVER_STATE_SET_MUX:
        if (now - state_tick > 1000)
        {
          HAL_UART_Transmit(&huart2, (uint8_t *)log_server, strlen(log_server), 100);
          HAL_UART_Transmit(&huart1, (uint8_t *)cmd_server, strlen(cmd_server), 100);
          server_state = SERVER_STATE_START_SERVER;
          state_tick = now;
        }
        break;

      case SERVER_STATE_START_SERVER:
        if (now - state_tick > 1500)
        {
          HAL_UART_Transmit(&huart2, (uint8_t *)log_ready, strlen(log_ready), 100);
          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); /* LED on = Server Active */
          server_state = SERVER_STATE_RUNNING;
          state_tick = now;
        }
        break;

      case SERVER_STATE_RUNNING:
        /* Transparent forward between ESP8266 modem and PC Terminal */
        if (HAL_UART_Receive(&huart1, &esp_byte, 1, 2) == HAL_OK)
        {
          HAL_UART_Transmit(&huart2, &esp_byte, 1, 2);
        }
        if (HAL_UART_Receive(&huart2, &pc_byte, 1, 2) == HAL_OK)
        {
          HAL_UART_Transmit(&huart1, &pc_byte, 1, 2);
        }
        break;
    }
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
