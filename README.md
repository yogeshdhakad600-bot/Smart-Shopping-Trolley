# Smart Shopping Trolley That Follows a Human

A hardware robotics project intended to reduce the effort of pushing a shopping trolley. The current prototype setup is based on an **ESP8266 NodeMCU**, an **IR sensor**, **three ultrasonic distance sensors**, an **L298N motor driver**, and **DC geared motors**.

## Project status

### Implemented hardware / current prototype
- ESP8266 NodeMCU controller
- IR sensor used as a basic tracking or movement input
- Three ultrasonic sensors planned for front, left, and right obstacle-distance sensing
- L298N motor driver and DC geared motors for trolley movement

> Update this list to reflect only what is physically assembled and tested. The firmware in this repository is a starter template and must be checked against the actual wiring before powering the motors.

### Planned features — not implemented yet
- RFID product identification and running-bill calculation
- Mobile app / Wi-Fi interface for status and bill
- Advanced person-specific tracking
- Full integrated safety validation

## Intended operation

1. Read the IR sensor input used by the current tracking method.
2. Measure distance to obstacles in front, left, and right.
3. Apply safety checks before issuing a movement command.
4. Use the L298N driver to control the DC motors.
5. Stop if an obstacle is too close, sensor readings are invalid, or the tracking input is not detected.

**Important limitation:** A basic IR obstacle/proximity sensor does not reliably identify a particular human or determine their position at a distance. The tracking method depends on the exact IR sensor and how it is aimed. Person-specific tracking may require a dedicated target or camera-based tracking.

## Hardware

See [`hardware/components_list.md`](hardware/components_list.md) and [`hardware/wiring_guide.md`](hardware/wiring_guide.md).

| Component | Purpose |
|---|---|
| ESP8266 NodeMCU | Main controller and optional Wi-Fi capability |
| IR sensor | Basic tracking / movement input, depending on sensor type |
| 3 × ultrasonic sensors | Front, left, and right distance measurement |
| L298N motor driver | Motor direction control |
| DC geared motors and wheels | Trolley movement |
| Battery and regulator | Power supply |
| Emergency-stop switch | Recommended physical motor-power cut-off |

## Firmware

The starter sketch is in [`firmware/smart_shopping_trolley.ino`](firmware/smart_shopping_trolley.ino).

Before using it:
1. Install the Arduino IDE and ESP8266 board support.
2. Confirm the exact board and sensor models.
3. Verify every GPIO assignment against your real wiring.
4. Ensure the ultrasonic sensor ECHO signals are reduced to **3.3 V or lower** before connecting to ESP8266 GPIO.
5. Test sensors with the wheels lifted and motor power disconnected first.
6. Add an independent emergency-stop circuit that can interrupt motor power.

The ESP8266 has boot-strap pins and limited GPIO. The example pin map is provisional; some pin assignments may affect boot depending on sensor output levels. Change the mapping or use suitable I/O expansion if needed.

## Repository structure

```text
smart-shopping-trolley/
├── README.md
├── .gitignore
├── firmware/
│   └── smart_shopping_trolley.ino
├── hardware/
│   ├── components_list.md
│   └── wiring_guide.md
├── circuit/
│   └── README.md
├── docs/
│   └── testing_checklist.md
└── media/
    └── README.md
```

## Testing checklist

- [ ] Verify ESP8266 boots reliably with all sensors connected.
- [ ] Verify IR input changes as expected for the chosen sensor.
- [ ] Verify each ultrasonic sensor independently.
- [ ] Confirm invalid or too-close readings stop the trolley.
- [ ] Confirm motor direction matches the code.
- [ ] Confirm emergency-stop switch cuts motor power.
- [ ] Test at low speed in a clear, controlled area.
- [ ] Record actual results before marking features complete.

## Planned next steps

1. Validate and document the actual circuit.
2. Tune the tracking behavior for the specific IR sensor.
3. Add and test the RFID module and product database.
4. Add a mobile interface if required.
5. Measure stop distance, response time, obstacle detection reliability, and billing accuracy.

## Contributions and license

Add contributor details and a license after deciding how the project may be reused. Do not commit passwords, Wi-Fi credentials, private tokens, or other secrets.
