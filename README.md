
## Heater Control System using ESP32 (Wokwi Simulation)

## Overview

This project is a simulation-based embedded systems prototype that demonstrates the behavior of a heater controller using an ESP32 microcontroller. The system is designed to monitor temperature input and respond by transitioning through defined operating states. Each state is visually indicated using an individual LED, with heater and buzzer control for operational safety and feedback.

The main aim is to replicate a real-world heater's intelligent control logic, suitable for smart kitchen or industrial automation environments. The simulation was built and tested using the Wokwi platform.

## System Description

The system reads simulated temperature values using a potentiometer. Based on the temperature, it identifies which thermal zone the system is in: Idle, Heating, Stabilizing, Target Reached, or Overheat.

- **Idle**: When the temperature is below 25.0°C, the system remains idle, and the heater is turned off.
- **Heating**: Between 25.0°C and 60.0°C, the system activates the heater to raise the temperature.
- **Stabilizing**: When the temperature is between 60.0°C and 65.0°C, the heater remains on to stabilize near the target.
- **Target Reached**: Between 65.0°C and 70.0°C, the desired temperature is reached, so the heater is turned off.
- **Overheat**: Beyond 70.0°C, the system disables the heater and activates a buzzer to indicate unsafe temperature levels.

Each of these states is mapped to an individual LED for clear visual feedback. Additionally, the system logs state and temperature to the serial monitor every second.

## Hardware Simulation Components

The system includes the following components, all simulated within the Wokwi environment:

- **ESP32**: The main controller handling analog input, logic, and digital output.
- **Potentiometer**: Acts as a temperature input source by varying analog voltage.
- **LEDs**: Five LEDs are used to display the system's current state.
- **Digital Output Pin**: Controls a virtual heater (e.g., a relay or transistor in real hardware).
- **Buzzer**: Provides an audible alert in the Overheat condition.

## Code Functionality

The firmware is written in Arduino C++ and structured around a finite state machine (FSM). Temperature values are sampled every 500 ms. Depending on the range the temperature falls into, the corresponding state is triggered.

LEDs are updated such that only the one associated with the current state is active. The heater control pin is activated only during Heating and Stabilizing states. The buzzer is enabled only during the Overheat state. Every second, the serial monitor prints the current temperature, state name, and BLE advertising string format `HTR<StateCode>`.


## Simulation

The project was built using the [Wokwi simulator](https://wokwi.com/projects/436647292966195201), which emulates the ESP32 and all peripherals.
