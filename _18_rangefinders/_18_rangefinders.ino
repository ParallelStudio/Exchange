//Author: Jesse Mejía
//Date: 06/2016


int sensorPins[] = {
  3, 4, 5
};
int pinCount = 3;
int pinStates[3]; //needs to be the same length as pinCount
const int channel = 1;
int targetRange = 12; //inches for triggering note-on

void setup() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(sensorPins[thisPin], INPUT);
    pinStates[thisPin] = 0;
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
    if (inches < targetRange){ //we get a line tripped
      if(pinStates[thisPin] == 0){ //it wasn't already tripped
        usbMIDI.sendNoteOn(thisPin, 127, 1);
        Serial.print("noteon from pin ");
        Serial.print(thisPin);
        Serial.print('\n'); 
        pinStates[thisPin] = 1;
      }
      else{ //we're in sustain mode and do  nothing
      }
    }else if (inches > targetRange){ //no person present
      if (pinStates[thisPin] == 1){ //last loop a person was present
        usbMIDI.sendNoteOn(thisPin, 0, 1);
        Serial.print("noteoff from pin ");
        Serial.print(thisPin);
        Serial.print('\n'); 
        pinStates[thisPin] = 0;
      }
    }
    //usbMIDI.sendControlChange(7, inches, channel);
//    Serial.print("pin2: ");
//    Serial.print(thisPin);
//    Serial.print(" - ");

//    Serial.print(pulseIn(sensorPins[thisPin], HIGH)/147);
//    Serial.print("in, ");
//    Serial.print('\n');
//    Serial.println();
  }
   delay(500);
}
