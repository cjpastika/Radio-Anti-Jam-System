#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN pins

const byte address[6] = "00001";
const uint8_t presetChannel = 76; // Must match transmitter

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(presetChannel);
  radio.openReadingPipe(0, address);
  radio.startListening();
  Serial.println("Receiver ready. Waiting for messages...");
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.print("Received: ");
    Serial.println(text);
  }
}
