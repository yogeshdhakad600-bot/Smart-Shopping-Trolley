# Testing Checklist

Record date, setup, expected behavior, actual result, and any corrective action for every test.

## Controller and sensors
- [ ] ESP8266 boots reliably with the selected wiring.
- [ ] IR sensor polarity and behavior are verified in Serial Monitor.
- [ ] Front ultrasonic sensor returns plausible distances.
- [ ] Left ultrasonic sensor returns plausible distances.
- [ ] Right ultrasonic sensor returns plausible distances.
- [ ] ECHO signals are safely reduced to 3.3 V or lower.
- [ ] Sensor cross-talk and blind spots are assessed.

## Motor and safety
- [ ] Left and right motor direction are verified with wheels lifted.
- [ ] Trolley stops when the front obstacle is inside the stop threshold.
- [ ] Trolley stops when a side sensor detects a critical obstacle.
- [ ] Invalid or missing sensor readings cause a stop.
- [ ] Physical emergency-stop switch interrupts motor power.
- [ ] No unexpected restart occurs after a stop.
- [ ] Driver and motors remain within their rated temperature/current limits.

## Integrated test
- [ ] Tracking behavior is tested in a clear, controlled space.
- [ ] Following distance and speed are measured.
- [ ] Stop distance is measured under different safe test loads.
- [ ] Firmware version and wiring changes are recorded.

## Planned features — test only after implementation
- [ ] RFID tag UID maps to the correct product.
- [ ] Duplicate reads do not unintentionally add multiple items.
- [ ] Item removal and total recalculation work.
- [ ] Mobile app shows correct status, list, and total.

## Results log template

| Date | Test | Setup | Expected | Actual | Pass/Fail | Notes |
|---|---|---|---|---|---|---|
| YYYY-MM-DD | Example: front obstacle stop | Wheels lifted / controlled setup | Motors stop at threshold | Fill after test | Pending | |
