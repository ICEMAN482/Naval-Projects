# 🌊 Naval Automated Bilge & Telemetry Test Rig

## 📌 Project Overview
An IoT fluid-dynamics and telemetry testbed. This project simulates an automated marine bilge system that detects flooding, safely evacuates the water, and features a robust manual override system. The logic is designed to mimic real-world naval safety protocols.

## ⚙️ Key Engineering Features
* **Autonomous Evacuation System:** Utilizes dual magnetic float switches (High/Low) to monitor water levels and trigger the pump automatically.
* **Anti-Cavitation Logic:** The automated system intentionally shuts off before the tank is completely empty, leaving a small "reserve puddle" to ensure the submersible pump never runs dry and burns out.
* **Live Load Telemetry:** Integrates an ACS712-05B (5A) highly sensitive current sensor to monitor micro-fluctuations in the engine load as the 5V pump struggles against water weight.
* **Flawless State Management:** Features custom logic utilizing state flags (`manualOverrideTriggered`) to clearly separate "Auto Stop" and "Manual Stop" events, eliminating overlapping edge-case bugs.

## 🛠️ Hardware Components
* **Microcontroller:** ESP32
* **Sensors:** ACS712-05B (5 Amp) Current Sensor, Magnetic Float Switch
* **Actuators:** 5V Mini Submersible Water Pump, 5V Single-Channel Relay
* **Controls:** Heavy-duty manual toggle switch for hardware overrides

## 💡 The "Edge Case" Solution
During development, a logic conflict occurred where the automatic float switch drop and the manual switch shut-off competed for the exact same event trigger. This caused the system to prematurely kill the loop. I solved this by introducing a boolean state machine flag that tracks *why* the pump was activated in the first place. The ESP32 is now completely aware of its state and will never confuse an automated shutdown with a manual override.

## 🚀 How to Use
1. Wire the components according to the isolated logic/power circuit blueprint.
2. Upload the `bilge_system.ino` file to the ESP32.
3. Submerge the pump and float switches in the test tank.
4. Monitor the Serial Output for live telemetry and state changes.
