#include <RF24.h>

RF24 radio(4, 5); // CE pin 4, CSN pin 5

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(2);               // Start on channel 2
  radio.setPALevel(RF24_PA_MIN);    // <-- Keep power at minimum
  radio.stopListening();            // Prepare to transmit
  Serial.println("Jammer ready. Type CHxx to change channel (e.g., CH12).");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command.startsWith("CH")) {
      int ch = command.substring(2).toInt();
      if (ch >= 0 && ch <= 125) {
        radio.setChannel(ch);
        Serial.print("Switched to channel: ");
        Serial.println(ch);
      } else {
        Serial.println("Invalid channel. Please enter CH0–CH125.");
      }
    }
  }

  // Smaller packet, no delay
  byte noise[8];
  for (int i = 0; i < 8; i++) {
    noise[i] = random(0, 255);
  }
  radio.write(&noise, 8);
}

