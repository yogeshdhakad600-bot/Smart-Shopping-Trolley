# Wiring Guide — Verify Before Connecting

This guide describes a **provisional** wiring plan for an ESP8266 NodeMCU, four L298N input signals, one shared ultrasonic TRIG signal, three ECHO signals, and one IR signal. ESP8266 GPIO is limited, and several pins have boot-strap requirements. If the board does not boot reliably with all sensors attached, redesign the pin plan or use suitable I/O expansion.

## Provisional pin assignment

| Function | NodeMCU label | Notes |
|---|---|---|
| L298N IN1 | D1 | GPIO5 |
| L298N IN2 | D2 | GPIO4 |
| L298N IN3 | D5 | GPIO14 |
| L298N IN4 | D6 | GPIO12 |
| Ultrasonic TRIG (shared) | D7 | GPIO13 |
| Front ECHO | D0 | GPIO16; verify library/timing behavior |
| Left ECHO | D3 | GPIO0; boot-strap pin |
| Right ECHO | D4 | GPIO2; boot-strap pin |
| IR output | D8 | GPIO15; boot-strap pin |

**Do not wire this table blindly.** D3, D4, and D8 affect ESP8266 boot mode. Sensor modules may drive these pins to levels that prevent boot. Confirm the exact sensor output state during startup, and change the mapping if necessary. A GPIO expander or a different controller may be more reliable for a fully integrated design.

## Ultrasonic sensors

- Connect all TRIG inputs to the shared TRIG pin only if the sensors can be triggered together and ECHO outputs are read separately.
- Trigger/read sensors sequentially in firmware to reduce cross-talk.
- Connect each ECHO output through a voltage divider or level shifter if it can output 5 V.
- Connect sensor grounds to the controller ground.
- Confirm sensor voltage requirements from the specific module datasheet.

## L298N and motors

- Connect IN1–IN4 as per the verified pin plan.
- Connect motor terminals to the driver outputs.
- Supply the motor driver using a power source suitable for the motors and driver.
- ENA/ENB jumpers may be used for fixed full-speed operation, or PWM speed control can be added with suitable available GPIO after the pin plan is finalized.
- Test wheel direction with the wheels lifted. If a motor turns in the wrong direction, change its wiring or software logic.
- Do not power motors from the ESP8266 board.

## IR sensor

- Connect sensor output to the selected GPIO only after confirming it outputs 3.3 V-compatible logic.
- Open Serial Monitor and observe the output while moving the target.
- Change `targetDetected` polarity in the sketch if the module is active LOW.
- A basic IR sensor does not necessarily identify a person or provide left/right direction.

## Emergency stop

Use a physical emergency-stop switch that can interrupt motor power independently of the main program. A software-only stop command is not a substitute for an independent motor-power cut-off.

## Before powering on

1. Check polarity and voltage with a multimeter.
2. Confirm ESP8266 GPIO signals never exceed 3.3 V.
3. Verify all pin assignments and boot behavior.
4. Disconnect motor power for the first controller/sensor tests.
5. Lift the wheels during initial motor tests.
