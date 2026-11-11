/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : CAT 11 - TASK 11B: HTTP Request Parser & Static HTML Response
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
#include <stdlib.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

typedef enum {
  SERVER_INIT = 0,
  SERVER_CONFIG_AT,
  SERVER_CONFIG_MODE,
  SERVER_CONFIG_WIFI,
  SERVER_CONFIG_IP,
  SERVER_CONFIG_MUX,
  SERVER_CONFIG_START,
  SERVER_LISTEN
} ServerInitState_t;

ServerInitState_t init_state = SERVER_INIT;
uint32_t state_tick = 0;

#define RX_BUF_SIZE 1024
char rx_buf[RX_BUF_SIZE];
uint16_t rx_idx = 0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

static void send_uart2(const char *msg)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), 100);
}

static void send_esp(const char *cmd)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)cmd, strlen(cmd), 200);
}

static void handle_http_request(int link_id)
{
  char cmd[64];
  char response[512];
  char body[] = "<html><body><h1>STM32 IoT Node</h1><p>Hello from STM32</p></body></html>\r\n";
  int body_len = strlen(body);
  int resp_len = snprintf(response, sizeof(response),
                          "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Content-Length: %d\r\n"
                          "Connection: close\r\n"
                          "\r\n"
                          "%s",
                          body_len, body);

  char log_msg[128];
  snprintf(log_msg, sizeof(log_msg), "[HTTP] Incoming GET on link %d. Preparing %d byte response.\r\n", link_id, resp_len);
  send_uart2(log_msg);

  /* Step 1: Send CIPSEND command */
  snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d,%d\r\n", link_id, resp_len);
  send_esp(cmd);
  HAL_Delay(50);

  /* Step 2: Send HTTP response payload */
  send_esp(response);
  HAL_Delay(100);

  /* Close TCP link */
  snprintf(cmd, sizeof(cmd), "AT+CIPCLOSE=%d\r\n", link_id);
  send_esp(cmd);
  send_uart2("[HTTP] Static HTML response transmitted and link closed.\r\n");
}

int main(void)
{
  char *banner = "\r\n=======================================================\r\n"
                 " CAT 11 - TASK 11B: HTTP Web Server & Static HTML Page\r\n"
                 "=======================================================\r\n";
  uint32_t now = 0;
  uint8_t ch = 0;

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  send_uart2(banner);
  state_tick = HAL_GetTick();

  while (1)
  {
    now = HAL_GetTick();

    /* Server initialization state machine */
    if (init_state < SERVER_LISTEN)
    {
      switch (init_state)
      {
        case SERVER_INIT:
          if (now - state_tick > 1000)
          {
            send_uart2("[1/6] AT ping...\r\n");
            send_esp("AT\r\n");
            init_state = SERVER_CONFIG_AT;
            state_tick = now;
          }
          break;

        case SERVER_CONFIG_AT:
          if (now - state_tick > 1000)
          {
            send_uart2("[2/6] Setting station mode...\r\n");
            send_esp("AT+CWMODE=1\r\n");
            init_state = SERVER_CONFIG_MODE;
            state_tick = now;
          }
          break;

        case SERVER_CONFIG_MODE:
          if (now - state_tick > 1000)
          {
            send_uart2("[3/6] Joining Wi-Fi network 'SNUC'...\r\n");
            send_esp("AT+CWJAP=\"SNUC\",\"snu12345\"\r\n");
            init_state = SERVER_CONFIG_WIFI;
            state_tick = now;
          }
          break;

        case SERVER_CONFIG_WIFI:
          if (now - state_tick > 5000)
          {
            send_uart2("[4/6] Querying IP address...\r\n");
            send_esp("AT+CIFSR\r\n");
            init_state = SERVER_CONFIG_IP;
            state_tick = now;
          }
          break;

        case SERVER_CONFIG_IP:
          if (now - state_tick > 2000)
          {
            send_uart2("[5/6] Enabling multi-connection mode...\r\n");
            send_esp("AT+CIPMUX=1\r\n");
            init_state = SERVER_CONFIG_MUX;
            state_tick = now;
          }
          break;

        case SERVER_CONFIG_MUX:
          if (now - state_tick > 1000)
          {
            send_uart2("[6/6] Launching TCP server on Port 80...\r\n");
            send_esp("AT+CIPSERVER=1,80\r\n");
            init_state = SERVER_CONFIG_START;
            state_tick = now;
          }
          break;

        case SERVER_CONFIG_START:
          if (now - state_tick > 1500)
          {
            send_uart2("\r\n[READY] Web Server Active on port 80. Connect using browser http://<IP>/\r\n");
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            init_state = SERVER_LISTEN;
            state_tick = now;
          }
          break;

        default:
          break;
      }
    }

    /* Receive incoming data from ESP8266 */
    if (HAL_UART_Receive(&huart1, &ch, 1, 2) == HAL_OK)
    {
      HAL_UART_Transmit(&huart2, &ch, 1, 2); /* Echo to PC debug console */

      if (rx_idx < RX_BUF_SIZE - 1)
      {
        rx_buf[rx_idx++] = (char)ch;
        rx_buf[rx_idx] = '\0';
      }

      /* Check for +IPD frame */
      char *ipd = strstr(rx_buf, "+IPD,");
      if (ipd != NULL)
      {
        char *colon = strchr(ipd, ':');
        if (colon != NULL)
        {
          /* Parse link_id: format is +IPD,<link_id>,<len>: */
          int link_id = atoi(ipd + 5);
          handle_http_request(link_id);
          rx_idx = 0;
          memset(rx_buf, 0, sizeof(rx_buf));
        }
      }

      /* Prevent buffer overrun */
      if (rx_idx >= RX_BUF_SIZE - 2)
      {
        rx_idx = 0;
      }
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
