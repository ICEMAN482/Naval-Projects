# Bilge System Connections

## Base Power (Establishing Rails)
| Component | Terminal / Pin | Destination Component | Destination Terminal / Pin |
| :--- | :--- | :--- | :--- |
| Laptop USB / Supply | 5V Output | Breadboard | ESP32 |
| ESP32 | VIN / 5V | Breadboard | 5V Rail |
| ESP32 | GND | Breadboard | Common GND Rail |

## System (ESP32 Controlled)
| Component | Terminal / Pin | Destination Component | Destination Terminal / Pin |
| :--- | :--- | :--- | :--- |
| Float Switch | Terminal 1 | Breadboard | Common GND Rail |
| Float Switch | Terminal 2 | ESP32 | D23 |
| Water Pump (System) | Red Wire | L293D Motor Driver | OUT1 |
| Water Pump (System) | Black Wire | L293D Motor Driver | OUT2 |
| L293D Motor Driver | IN1 | ESP32 | D27 |
| L293D Motor Driver | IN2 | Breadboard | Common GND Rail |
| L293D Motor Driver | EN1 | Breadboard | 5V Rail |
| ACS712 Current Sensor | Green Screw 1 | L293D Motor Driver | 12V Screw |
| ACS712 Current Sensor | Green Screw 2 | Breadboard | 5V Rail |
| L293D Motor Driver | GND Screw | Breadboard | Common GND Rail |
| L293D Motor Driver | 5V Screw | Breadboard | 5V Rail |
| ACS712 Current Sensor | VCC Pin | Breadboard | 5V Rail |
| ACS712 Current Sensor | OUT Pin | ESP32 | D35 |
| ACS712 Current Sensor | GND Pin | Breadboard | Common GND Rail |
| Manual Override Switch| Terminal 1 | Breadboard | Common GND Rail |
| Manual Override Switch| Terminal 2 | ESP32 | D26 |

## Independent (Manual Control)
| Component | Terminal / Pin | Destination Component | Destination Terminal / Pin |
| :--- | :--- | :--- | :--- |
| Water Pump (Independent)| Red Wire | Toggle Switch | Terminal 1 |
| Water Pump (Independent)| Black Wire | Breadboard | Common GND Rail |
| Toggle Switch | Terminal 1 | Water Pump (Independent) | Red Wire |
| Toggle Switch | Terminal 2 | Breadboard | 5V Rail |
