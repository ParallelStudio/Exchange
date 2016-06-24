//Author: Jesse Mejía and from Bruce Allen
//Date: 06/2016

#define pinCount 8
int sensorPins[] = {
  22
};

//variables needed to store values

long anVolt, inches, cm;
int sum = 0; //Create sum variable so it can be averaged
int avgrange = 60; //Quantity of values to average (sample size)

void setup() {
   //This opens up a serial connection to shoot the results back to the PC console
  Serial.begin(9600);

}

void loop() {
  for (int i = 0; i < avgrange ; i++){
    //Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
    //analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
    anVolt = analogRead(sensorPins[0]) / 2;

    sum += anVolt;

    delay(10);
  }

 inches = sum / avgrange;
 cm = inches * 2.54;
 Serial.print(inches);
 Serial.print("in, ");
 Serial.println();

  //reset sample total
  sum = 0;

  delay(500);

}
