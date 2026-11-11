# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 14

**DATE:** 02/11/2026

**NAME OF EXP:** Environmental Sensing (BME280) & MQTT Cloud Analytics

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 NUCLEO-F401RE + BME280 + ESP8266 + Node-RED

---

## Overview

This experiment covers end-to-end IoT cloud integration using the lightweight MQTT protocol. The STM32 reads high-precision BME280 environmental data and publishes structured JSON telemetry through the ESP8266 MQTT client API (ESPLib) to a public MQTT broker (broker.emqx.io).

## Dedicated Tasks

- **[TASK 14: Integrated Smart Edge Node (BME280 - MQTT Client)](TASK14/)**: End-to-end integration acquiring sensor data and publishing MQTT messages.
- **[TASK 14A: BME280 I2C Environmental Sensing & Compensation](TASK14A/)**: Raw sensor ADC sampling and high-precision compensation math implementation.
- **[TASK 14B: ESP8266 MQTT Client API & Cloud Telemetry](TASK14B/)**: MQTT connection handling, topic publishing (stm32/test/data), and QoS delivery.

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 14 is shown below:

![Circuit Diagram](circuit.png)

### Inference

An end-to-end smart IoT edge node was successfully deployed, publishing live sensor metrics over MQTT for cloud ingestion and visualization.
