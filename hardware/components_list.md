# Hardware Components List

Status labels must reflect the actual build. Quantities below are suggested for the described configuration.

| Component | Suggested quantity | Purpose | Status |
|---|---:|---|---|
| ESP8266 NodeMCU development board | 1 | Main controller / Wi-Fi capability | Current controller |
| IR sensor module | 1 | Basic tracking or movement input | Current input; confirm exact sensor model |
| Ultrasonic distance sensor (HC-SR04 class) | 3 | Front, left, and right distance sensing | Planned/installed as physically verified |
| L298N motor driver | 1 | Controls motor direction | Existing motor driver |
| DC geared motors and wheels | As required | Trolley movement | Existing prototype |
| Chassis / basket / frame | 1 | Supports load and electronics | Existing prototype |
| Battery suitable for motors | 1 | Motor power | Select by motor rating |
| Regulator for logic supply | 1 as required | Stable controller/sensor power | Verify actual board and supply |
| Emergency-stop switch | 1 | Manual stop | Recommended; ideally interrupts motor power directly |
| RC522-class RFID reader | 1 | Reads product tag UIDs | Planned — not implemented |
| Compatible RFID tags | As required | Product identification | Planned — not implemented |
| Display / buzzer / LEDs | Optional | User feedback | Optional / planned |
| Jumper wires, connectors, mounting hardware | As required | Connections and assembly | Required as applicable |

## Electrical notes

- ESP8266 GPIO uses 3.3 V logic and is not 5 V tolerant.
- Many HC-SR04 modules use a 5 V supply and output a 5 V ECHO signal. Use a suitable voltage divider or level shifter on each ECHO line.
- Power motors from an appropriate motor supply, not from the ESP8266 3.3 V pin.
- Check the L298N current and thermal limits against the actual motors.
- Establish a common ground where required by the circuit, while keeping power wiring appropriate for motor current.
- Final quantities, model numbers, and prices should be added after checking the actual components.
