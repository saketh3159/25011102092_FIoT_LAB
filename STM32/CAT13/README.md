# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 13

**DATE:** 26/10/2026

**NAME OF EXP:** BME280 Data Acquisition & HTTP Cloud Ingestion

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 NUCLEO-F401RE + BME280 (I2C) + ESP8266 (UART)

---

## Overview

This experiment covers digital sensor interfacing over I2C, implementing Bosch BME280 compensation formulas for temperature, pressure, and humidity, formatting JSON telemetry payloads, and transmitting HTTP POST requests via ESP8266 to Node-RED cloud pipelines.

## Dedicated Tasks

- **[TASK 13A: BME280 I2C Hardware Bring-Up & Bosch API Integration](TASK13A/)**: I2C communication with BME280 sensor reading calibrated temperature, pressure, and humidity.
- **[TASK 13B: Dynamic JSON Payload Generation & HTTP POST Transmission](TASK13B/)**: Formatting JSON strings and transmitting HTTP POST requests to an IoT endpoint.
- **[TASK 13C: Node-RED Cloud Ingestion Pipeline & Statistical Telemetry](TASK13C/)**: Node-RED HTTP dashboard receiving, parsing, and plotting environmental metrics.

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 13 is shown below:

![Circuit Diagram](circuit.png)

### Inference

Accurate environmental data acquisition and reliable HTTP cloud telemetry were achieved using the STM32F401RE, BME280, and ESP8266 modem.
