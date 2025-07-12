# Radio-Anti-Jam-System

# Overview
This project includes two systems:
A frequency hopping transceiver system using NRF24L01+ modules and ESP32 boards.
A simple RF jammer that can switch channels dynamically.
Both systems can be controlled from a serial monitor and are designed for testing and educational purposes.

# Hardware Required
3 ESP32 boards (can also use Arduino boards with adjustments)
3 NRF24L01+ modules (preferably with external antennas)
3 µF capacitors (recommended for NRF24 power stability)
Jumper wires
Breadboard (optional)
USB cables for programming

#Software Required
Arduino IDE (or PlatformIO)
RF24 library (by TMRh20)

# NRF24L01+ Wiring (ESP32)
NRF24 Pin	ESP32 Pin
GND	GND
VCC	3.3V
CE	GPIO 4
CSN	GPIO 5
SCK	GPIO 18
MOSI	GPIO 23
MISO	GPIO 19
IRQ	Not connected (optional)

Important: Use 3.3V only. NRF24L01+ modules can be damaged by 5V.

# Frequency Hopping System Assembly:
Connect each NRF24 module to each ESP32 board using the table above.
Solder or place a 10 µF capacitor between VCC and GND near each NRF24 module to reduce noise.
Connect both ESP32 boards to your computer using USB cables.
Install the RF24 library in Arduino IDE:
Go to Sketch > Include Library > Manage Libraries.
Search for "RF24".
Install "RF24 by TMRh20".
Upload the transmitter sketch to one ESP32.
Upload the receiver sketch to the second ESP32.
Open Serial Monitor for both boards (115200 baud or whatever you set in code).
Check that they sync up and start exchanging messages while hopping across channels.

# Frequency Hopping Control
You can adjust the hopping channels in a hopTable[] array in your code.
Hopping speed can be changed with a delay or timer constant (for example, hopIntervalMs).
You can modify or add serial commands to change channels or parameters live from your computer.

# Jammer Assembly
Use another ESP32 and NRF24 module wired the same way.
Upload your jammer sketch.
Connect to Serial Monitor to control which channel to jam.
You can make the jammer change channels rapidly (like a hopping jammer) by updating the channel index in code from the serial monitor.
Keep power amplifier levels low if you want to avoid wide interference.

# Running the Jammer
Set a starting channel from Serial Monitor.
Change channels on demand (for example, by typing a new channel number).
The jammer will continuously transmit random or constant data on that channel, blocking or interfering with other devices.
You can also configure it to automatically hop channels in a loop, similar to the hopping system.

# Tips
Always use a capacitor near NRF24 power pins to prevent brownouts.
Check antenna placement and make sure there is no metal blocking signal paths.
Use separate USB ports to avoid interference from your computer.
Test each system separately before using them together.

# Important
This project is for educational and experimental use only. Interference with real communication systems without permission is illegal in most countries. Use responsibly and comply with local laws.

# Contact
For questions or issues, please open an issue on this repository or contact me directly.
