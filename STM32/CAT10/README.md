# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 10

**DATE:** 05/10/2026

**NAME OF EXP:** STM32 USART Serial Communication Modes

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 NUCLEO-F401RE + PuTTY Terminal

---

## Overview

This experiment covers serial communication on the STM32, configuring USART2 for ST-LINK virtual COM port debugging, implementing polled transmission, interrupt-driven bidirectional echoing, and dual-UART transparent bridging to an ESP8266 modem.

## Dedicated Tasks

- **[TASK 10A: USART2 Polling String Transmission](TASK10A/)**: Synchronous polled transmission of formatted text banners over USART2 @ 115200 baud.
- **[TASK 10B: USART2 Interrupt-Driven Bidirectional Echo](TASK10B/)**: Asynchronous character reception using RX complete interrupts with full-duplex terminal echo.
- **[TASK 10C: Dual-UART Transparent Bridge & Provisioning Engine](TASK10C/)**: Bidirectional bridge linking USART1 (ESP8266 modem) and USART2 (PC debug terminal).

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 10 is shown below:

![Circuit Diagram](circuit.png)

### Inference

USART communication at 115200 baud was verified across polled, interrupt, and dual-port bridging architectures.
