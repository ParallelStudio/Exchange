//Author: Jesse Mejía
//Date: 06/2016

#define pinCount 3
int sensorPins[] = {
  3, 4, 5
};
bool pinStates[pinCount];
bool noteStates[pinCount];
unsigned long pinLastDebounce[pinCount];
int targetRange = 24; //inches for triggering note-on
unsigned long debounceDelay = 250;

void setup() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(sensorPins[thisPin], INPUT);
    //Used to read in the pulse that is being sent by the MaxSonar device.
    //Pulse Width representation with a scale factor of 147 uS per Inch.
  }
}

void loop() {
  //variables needed to store values
  long pulse, inches;
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pulse = pulseIn(sensorPins[thisPin], HIGH);
    //147uS per inch
    inches = pulse/147;
    bool tripped = inches < targetRange;
    
    if (pinStates[thisPin] != tripped) {
      pinLastDebounce[thisPin] = millis();
      pinStates[thisPin] = tripped;
//      Serial.println("debouncing");
    }
    if ((millis() - pinLastDebounce[thisPin]) > debounceDelay){
      if (noteStates[thisPin] != pinStates[thisPin]) {
        usbMIDI.sendNoteOn(thisPin, pinStates[thisPin] ? 127 : 0, 1);
        Serial.print(pinStates[thisPin] ? "on " : "off ");
        Serial.print(sensorPins [thisPin]);
        Serial.print('\n'); 
        noteStates[thisPin] = pinStates[thisPin];
       }
    }
//      Serial.print(pulseIn(sensorPins[thisPin], HIGH)/147);
//      Serial.print("in, ");
//      Serial.print('\n');
//      Serial.println();
  }

   delay(50);
}
