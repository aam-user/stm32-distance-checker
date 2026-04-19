# Distance Checker — STM32 Nucleo F401RE

Proximity alert system using HC-SR04 ultrasonic sensor with visual and audio feedback.

## Hardware

| Component | Pin |
|---|---|
| HC-SR04 TRIG | D12 |
| HC-SR04 ECHO | D11 |
| LED Red | D2 |
| LED Yellow | D4 |
| Buzzer | D7 |

## Behavior

| Distance | LED | Buzzer |
|---|---|---|
| < 10 cm | Red — fast blink | Fast beep |
| 10–20 cm | Yellow — slow blink | Slow beep |
| > 20 cm | Off | Off |

## Wiring note

HC-SR04 ECHO outputs 5V. Nucleo F401RE runs at 3.3V.  
Use a voltage divider on the ECHO pin:  
`ECHO → 1kΩ → D11`  
`junction between resistors → 1kΩ → GND`

## Environment

- Board: STM32 Nucleo F401RE
- IDE: Mbed Studio
- Framework: Mbed OS 6

## Monitor

```bash
cat /dev/ttyACM0
```

## License

MIT
