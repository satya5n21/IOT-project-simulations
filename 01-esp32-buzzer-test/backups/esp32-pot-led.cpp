#include <Arduino.h>

#define pot 36 // ESP32 pin GIOP36 (ADC0)
int LED = 26;

void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop()
{
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(pot);
  float z1 = analogValue;
  Serial.print("Discrete Value = ");
  Serial.println(analogValue); // the raw analog reading
  float z2 = z1 * 5 / 4095;
  Serial.print("Analog Value  = ");
  Serial.println(z2); //
  // We'll have a few threshholds, qualitatively determined
  if (z2 > 3.5)
  {
    Serial.println(" Voltage abnormal");
    digitalWrite(LED, HIGH);
  }
  else
  {
    Serial.println("Voltage Normal 2");
    digitalWrite(LED, LOW);
  }

  delay(500);
}