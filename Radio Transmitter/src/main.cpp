#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5);
const byte address[6] = "00001";

const uint8_t baseChannels[12] = {5, 9, 15, 21, 27, 33, 45, 51, 57, 69, 75, 81};
uint8_t hopSequence[12];

String getLineInput(const char* prompt) {
  Serial.println(prompt);
  String input = "";
  while (true) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\r' || c == '\n') {
        if (input.length() > 0) {
          Serial.println();
          return input;
        }
      } else {
        input += c;
        Serial.print(c);
      }
    }
  }
}

unsigned long computeSeed(String tod, String wod, int netNum) {
  unsigned long hash = 0;
  for (char c : tod) hash = (hash * 31) + c;
  for (char c : wod) hash = (hash * 31) + c;
  hash = (hash * 31) + netNum;
  return hash;
}

void shuffleChannels(const uint8_t* input, uint8_t* output, int len, unsigned long seed) {
  memcpy(output, input, len);
  randomSeed(seed);
  for (int i = len - 1; i > 0; i--) {
    int j = random(0, i + 1);
    uint8_t tmp = output[i];
    output[i] = output[j];
    output[j] = tmp;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  String tod = getLineInput("Enter Time of Day (HHMM): ");
  String wod = getLineInput("Enter Word of the Day (WOD): ");
  int netNum = getLineInput("Enter Net Number (integer): ").toInt();

  unsigned long seed = computeSeed(tod, wod, netNum);
  shuffleChannels(baseChannels, hopSequence, 12, seed);
  Serial.println("✅ Transmitter ready. Sending...");

  if (!radio.begin()) {
    Serial.println("❌ Radio init failed");
    while (1);
  }

  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.openWritingPipe(address);
}

void loop() {
  static int index = 0;
  static const char data[] = "DATA";

  radio.stopListening();
  radio.setChannel(hopSequence[index]);

  bool success = radio.write(&data, sizeof(data));
  if (success) {
    Serial.print("📡 Sent on channel ");
    Serial.print(hopSequence[index]);
    Serial.println(": ✅ Success");

    if (radio.isAckPayloadAvailable()) {
      char ack[32] = "";
      radio.read(&ack, sizeof(ack));
      Serial.print("✅ ACK payload received: ");
      Serial.println(ack);
    } else {
      Serial.println("⚠️ No ACK payload received");
    }

    index = (index + 1) % 12;
  } else {
    Serial.print("📡 Sent on channel ");
    Serial.print(hopSequence[index]);
    Serial.println(": ❌ Failed");
  }

  delay(200); // adjust to match receiver
}
