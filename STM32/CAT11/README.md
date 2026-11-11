# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 11

**DATE:** 12/10/2026

**NAME OF EXP:** HTTP Server: STM32–Wemos Wi-Fi Modem Using AT Commands

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 NUCLEO-F401RE + Wemos D1 WiFi Module (ESP8266)

---

## Overview

This experiment covers developing an embedded HTTP web server on the STM32F401RE interfacing with an ESP8266 Wi-Fi modem via UART AT commands, configuring TCP multi-connection servers, handling inbound HTTP GET requests, and serving both web browsers and Node-RED automation flows.

## Dedicated Tasks

- **[TASK 11A: ESP8266 TCP Server Configuration via AT Commands](TASK11A/)**: Configuring ESP8266 into multi-connection TCP server mode listening on port 80.
- **[TASK 11B: HTTP Request Parser & Static HTML Response](TASK11B/)**: Parsing inbound +IPD frames and transmitting static HTML webpage using 2-step CIPSEND.
- **[TASK 11C: Node-RED as a Second HTTP Client of STM32/ESP8266 Server](TASK11C/)**: Multi-client HTTP server delivering dynamic telemetry to web browsers and Node-RED flows.

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 11 is shown below:

![Circuit Diagram](circuit.png)

### Inference

The STM32 successfully functioned as an embedded HTTP web server, serving HTML dashboards and JSON telemetry to web browsers and Node-RED.
