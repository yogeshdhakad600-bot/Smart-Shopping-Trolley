# Smart Shopping Trolley That Follows a Human

A robotics project aimed at making shopping easier by developing a trolley that follows a shopper, detects nearby obstacles, and prioritizes safe stopping. The planned Stage 2 enhancements include RFID-based product identification and running-bill calculation, plus Wi-Fi status and billing access through a mobile app.

> **Project status:** The original prototype is described as using an Arduino UNO, an IR sensor, one ultrasonic sensor, an L298N motor driver, and DC motors for human following and path correction. The ESP8266-based controller, RFID billing, mobile app, emergency-stop layer, and multi-sensor obstacle avoidance are Stage 2 enhancements and should be marked complete only after they have been implemented and tested.

## Features

### Core prototype
- Human-following behavior using an IR tracking input.
- Obstacle detection and path correction using an ultrasonic sensor.
- Motor direction control through an L298N motor driver and DC geared motors.

### Planned / Stage 2 enhancements
- **ESP8266 controller:** coordinate sensor input, movement logic, and Wi-Fi connectivity.
- **Multi-direction obstacle detection:** use three ultrasonic sensors (front, left, and right).
- **RFID-based product identification:** associate a tag UID with a product name and price.
- **Running bill:** maintain a shopping list and calculate a total from scanned products.
- **Mobile app connection:** show trolley status, item list, and bill over Wi-Fi.
- **Emergency stop:** give manual stop and critical-obstacle stop priority over normal movement.
- **Optional user feedback:** buzzer, LED, or display.

## How It Works

1. The shopper starts the trolley and establishes the tracking target.
2. The IR tracking input provides movement or direction information.
3. Ultrasonic sensors measure distances to obstacles around the trolley.
4. The controller checks the emergency-stop state and obstacle conditions before issuing movement commands.
5. The L298N motor driver controls the DC motors to move, turn, slow down, or stop.
6. When RFID is integrated, a reader reads the tag UID and matches it to a product record to update the shopping list and running total.
7. Wi-Fi can provide status and billing information to a mobile app.

### Safety priority

**Manual emergency stop → critical obstacle stop → warning/slow down → obstacle avoidance → human following**

If sensor readings are missing, contradictory, or invalid, the trolley should stop rather than guess.

## Hardware Requirements

| Component | Purpose |
|---|---|
| ESP8266 development board | Controller and Wi-Fi connectivity for the enhanced version |
| IR tracking sensor | Human movement/direction input |
| Ultrasonic sensors (up to 3) | Front, left, and right obstacle detection |
| L298N motor driver | Controls motor direction and speed |
| DC geared motors and wheels | Trolley movement |
| RFID reader (RC522-class) and RFID tags | Product identification |
| Emergency-stop switch | Manual stop input; preferably cuts motor power directly |
| Battery, regulator, and wiring | Power distribution |
| Optional buzzer, LED, or display | User feedback |

**Compatibility note:** Confirm the exact ESP8266 board, GPIO pin assignments, voltage levels, motor current, and power supply before wiring. The RC522-class RFID reader uses 3.3 V logic. Keep motor and logic power appropriately managed, and verify that the selected driver can handle the motors' current and heat.

## Software / Development Tools

- Arduino IDE or another ESP8266-compatible development environment
- ESP8266 board support package
- Libraries appropriate to the selected ultrasonic sensors and RFID reader
- Optional mobile app or web interface for Wi-Fi status and billing
- Git and GitHub for source-code version control

Exact library names, firmware, mobile-app framework, and pin assignments should be added once selected for the actual build.

## Getting Started

1. **Assemble the base:** mount the motors, wheels, controller, motor driver, and battery securely.
2. **Test motor control:** verify forward, reverse, turning, and stop commands with the wheels lifted from the floor.
3. **Integrate tracking:** connect the IR sensor and validate the intended human-following behavior.
4. **Add obstacle sensing:** mount sensors with clear fields of view and test each approach direction. Trigger ultrasonic sensors sequentially if needed to reduce cross-talk.
5. **Implement safety logic:** ensure emergency-stop and obstacle-stop conditions override all normal movement commands.
6. **Add RFID billing:** map tag UIDs to product records and implement duplicate-read handling and item removal.
7. **Add Wi-Fi features:** expose status, shopping list, and bill to a mobile interface if this feature is implemented.
8. **Validate the integrated system:** record results for following stability, stop distance, response time, obstacle detection, and billing accuracy.

## Repository Structure

A suggested structure for this GitHub repository:

```text
smart-shopping-trolley/
├── README.md
├── firmware/
│   └── smart_shopping_trolley.ino
├── circuit/
│   └── wiring_diagram.png
├── cad/
│   └── trolley_layout.*
├── mobile-app/
├── docs/
│   ├── project-report.pdf
│   └── test-results.md
└── media/
    └── prototype-photos/
```

Create or rename folders to match the files that actually exist in your repository. Do not include empty or placeholder files as if they were completed work.

## Testing Checklist

- [ ] Trolley follows the intended target in a controlled area.
- [ ] Following distance and speed are tested.
- [ ] Front, left, and right obstacle detection are checked.
- [ ] Emergency stop reliably stops the motors.
- [ ] The trolley does not restart unexpectedly after a stop.
- [ ] Invalid sensor readings result in a safe stop.
- [ ] RFID tags map to the correct products and prices.
- [ ] Duplicate RFID reads do not unintentionally add items.
- [ ] Item removal and bill recalculation work correctly.
- [ ] The controller and motor driver remain stable during extended tests.

## Limitations and Safety

- An ordinary IR sensor may detect reflected signals or movement but may not identify one specific person. Reliable person-specific tracking may require a clearly defined tracking target or a camera-based tracking module.
- Ultrasonic sensors can have blind spots, inconsistent readings, and cross-talk.
- RFID identifies tagged products; it does not automatically guarantee a complete checkout system. Duplicate reads, removal, and final bill verification need explicit handling.
- Do not test with real shoppers or in crowded public areas until the system has been validated under controlled conditions.
- Measure stopping distance at different speeds and loads. Do not claim safety certification or standards compliance unless it has been formally verified.

## Future Improvements

- Camera-based person detection and tracking
- Improved obstacle sensing and navigation
- Mobile interface for live trolley status and billing
- Battery-level monitoring
- Better product removal and checkout workflows
- Logged test data and performance measurements

## Project Documentation

Add the project's design specification, circuit diagrams, source code, CAD files, prototype photos, and test logs to this repository as they become available. Clearly label features as **implemented**, **in progress**, or **planned**.

## Contributors

Add team member names, roles, and institutional details here if appropriate.

## License

No license has been specified yet. Add a `LICENSE` file before publishing if you want to define how others may use, modify, and distribute this project.
