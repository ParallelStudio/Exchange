/*
//Author: Jesse Mejía
//Date: 06/2016
*/

#define pinCount 9
int sensorPins[] = {
  14, 15, 16, 17, 18, 19, 20, 21, 22
};
bool pinStates[pinCount];
bool noteStates[pinCount];
unsigned long pinLastDebounce[pinCount];
unsigned long debounceDelay = 200;
int targetRange = 36;
// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 5;
int readings[pinCount][numReadings];      // the readings from the analog input
int readIndices[pinCount];              // the index of the current reading
int totals[pinCount];                  // the running totals
int averages[pinCount];                // the averages


void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
}

void loop() {
   for (int pin = 0; pin < pinCount; pin++ ) {
//    int index = readIndices[pin];
//    totals[pin] = totals[pin] - readings[pin][index]; 
//    readings[pin][index] = analogRead(sensorPins[pin]);
//    totals[pin] = totals[pin] + readings[pin][index];
//    readIndices[pin] = index + 1;
// 
//    // if we're at the end of the array...
//    if (readIndices[pin] >= pinCount) {
//      // ...wrap around to the beginning:
//      readIndices[pin] = 0;
//      averages[pin] = totals[pin] / numReadings;
//      bool tripped = averages[pin] < targetRange;

      bool tripped = analogRead(sensorPins[pin]) < targetRange;
      if (pinStates[pin] != tripped) {
        pinLastDebounce[pin] = millis();
        pinStates[pin] = tripped;
//        Serial.println("debouncing");
      }
      else if (noteStates[pin] != pinStates[pin] && (millis() - pinLastDebounce[pin]) > debounceDelay) {
      usbMIDI.sendNoteOn(pin, pinStates[pin] ? 127 : 0, 1);
//      Serial.print(pinStates[pin] ? "on " : "off ");
//      Serial.print(pin);
//      Serial.print('\n'); 
      noteStates[pin] = pinStates[pin];
      }
      //Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in and pin goes from 0 to 1024
      // send it to the computer as ASCII digits
//      Serial.print(pin);
//      Serial.print(": ");
//      Serial.print(averages[pin]);
//      Serial.print('\n');
    }
    
    delay(10);        // delay in between reads for stability
}
