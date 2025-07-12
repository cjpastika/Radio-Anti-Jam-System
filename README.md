# Radio-Anti-Jam-System1

Project Overview:
The goal of this project is to build a radio frequency hopping system that simulates military anti-jam modes such as HAVEQUICK and SINGCARS. To do this I have built 3 modules: a jammer, a receiver, and a transmitter. Due to hardware constraints and simply a lack of knowledge on classified government anti-jam modes, I have built a much simpler version of a frequency hopping system that relies on essentially a ACK handshake between the transmitter and receiver before hopping. For military usage this would likely be too slow to have much use but it should be an excellent proof of concept.

Materials needed: 
3 ESP-32 microcontrollers
3 nrf24l01 radio modules (NOT THE PA+LNA VERSION)
6 breadboards
3 47uF 50V capacitors
3 power/data cables (must have 1 end be micro-usb)
Male-Female breadboard wires

Assembly:

Runtime prereqs:
-must have platform IO installed and the cores initialized for all 3 projects
-must have all modules plugged in

Usage:

If you want the radio to get jammed:
-use the manual folder
-build and upload rcv and transmit
-switch to the receiver serial monitor and enter your TOD, WOD, and Net ID
-enter identical data into the transmit serial monitor quickly
-verify information is being sent and rceived
-build and upload the jammer project
-check the serial monitor to confirm data is no longer being received

If you want to use frequency hopping mode: 
-use the FH folder
-build and upload rcv and transmit
-switch to the receiver serial monitor and enter your TOD, WOD, and Net ID
-enter identical data into the transmit serial monitor quickly
-verify information is being sent and rceived and radios are hopping
-build and upload the jammer project
-check the serial monitor to confirm data is still being received
