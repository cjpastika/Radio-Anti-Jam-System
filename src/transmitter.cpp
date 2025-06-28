#include <Arduino.h>

// --- Channel list for hopping ---
const uint8_t baseChannelList[12] = {
  5, 9, 15, 21, 27, 33, 45, 51, 57, 69, 75, 81
};

uint8_t hopSequence[12]; // Final shuffled result

// --- User inputs ---
String TOD_input = "";
String WOD_input = "";
int net_number = 0;
bool gotAllInputs = false;

// --- Helper function to safely read serial input ---
String getLineInput(String prompt) {
  String input = "";
  char c;

  Serial.println(prompt);
  while (true) {
    if (Serial.available()) {
      c = Serial.read();

      // Echo character if not Enter
      if (c != '\n' && c != '\r') {
        input += c;
        Serial.print(c);
      }

      // Break and return when Enter is hit
      if (c == '\n') {
        input.trim();
        Serial.println();
        return input;
      }
    }
  }
}

// --- Compute seed based on TOD, WOD, and Net Number ---
unsigned long computeSeed(String tod, String wod, int netNum) {
  unsigned long hash = 0;
  for (char c : tod) hash = (hash * 31) + c;
  for (char c : wod) hash = (hash * 31) + c;
  hash = (hash * 31) + netNum;
  return hash;
}

// --- Fisher-Yates Shuffle with seed ---
void shuffleChannels(uint8_t* input, uint8_t* output, int len, unsigned long seed) {
  memcpy(output, input, len);
  randomSeed(seed);

  for (int i = len - 1; i > 0; i--) {
    int j = random(0, i + 1);
    uint8_t temp = output[i];
    output[i] = output[j];
    output[j] = temp;
  }
}

// --- Print the final hop sequence ---
void printHopSequence() {
  Serial.println("\nFinal Hop Sequence:");
  for (int i = 0; i < 12; i++) {
    Serial.print("Channel ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(hopSequence[i]);
  }
}

// --- Collect inputs from user with proper prompting ---
void requestInputs() {
  TOD_input = getLineInput("Enter Time of Day (HHMM):");
  WOD_input = getLineInput("Enter Word of the Day (WOD):");

  String netStr = getLineInput("Enter Net Number (integer):");
  net_number = netStr.toInt();  // Safe parse
  gotAllInputs = true;
}

// --- Setup runs once ---
void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for Serial Monitor (ESP32)

  requestInputs();

  unsigned long seed = computeSeed(TOD_input, WOD_input, net_number);
  shuffleChannels((uint8_t*)baseChannelList, hopSequence, 12, seed);
  printHopSequence();
}

// --- Main loop (empty for now) ---
void loop() {
  // You can implement channel hopping here using hopSequence[]
}