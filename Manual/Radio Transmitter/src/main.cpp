#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN pins

const byte address[6] = "00001";
const uint8_t presetChannel = 76; // You can change to any valid channel (0–125)

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(presetChannel);
  radio.openWritingPipe(address);
  radio.stopListening();
  Serial.println("Transmitter ready. Sending...");
}

void loop() {
  const char message[] = "Data";
  bool success = radio.write(&message, sizeof(message));

  if (success) {
    Serial.println("Sent: Success");
  } else {
    Serial.println("Sent: Failed");
  }

  delay(1000);
}
