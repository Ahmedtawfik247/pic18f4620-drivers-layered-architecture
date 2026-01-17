# PIC18F4620 Layered Drivers (MCAL + ECU)

Embedded C project implementing a layered driver architecture for **PIC18F4620** using **MPLAB X** and **XC8**.

## Architecture
- **MCAL Layer**: GPIO, EEPROM, Interrupts, device configuration
- **ECU Layer**: LED, Button, Relay, DC Motor, Keypad, 7-Segment, Character LCD
- **Application Layer**: Example usage and integration

## Implemented Modules
### MCAL
- GPIO
- Interrupts (external/internal + manager)
- EEPROM
- Device configuration

### ECU
- LED
- Button
- Relay
- DC Motor
- Keypad
- 7-Segment
- Character LCD

## How to Build
1. Open the project folder in **MPLAB X**.
2. Select configuration: `default` (Debug/Production).
3. Build using **XC8**.
4. Flash the generated `.hex` file to PIC18F4620 (if hardware is available).

## Notes
- This repository contains **source code only** (build artifacts are excluded via `.gitignore`).

## Author
Ahmed Mohamed Elsayed Tawfik  
LinkedIn: https://www.linkedin.com/in/ahmed-mohamed-tawfik/
