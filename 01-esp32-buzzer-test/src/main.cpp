#include <Arduino.h>

// --- Pin Definitions ---
const int POT_PIN = 34;    // Analog input pin connected to Potentiometer SIG
const int BUZZER_PIN = 25; // Output pin connected to Piezo Buzzer SIG

// --- PWM Channel Settings (For Older ESP32 Core Frameworks) ---
const int BUZZER_PWM_CHANNEL = 0; // Use PWM Channel 0 (0 to 15 available)
const int PWM_RESOLUTION = 8;     // 8-bit resolution

// --- Variables ---
int rawPotValue = 0;     // Variable to store raw ADC data (0 to 4095)
int targetFrequency = 0; // Variable to store mapped sound frequency (Hz)

void setup()
{
  // Initialize serial communication for diagnostic monitoring
  Serial.begin(115200);
  Serial.println("--- Local ESP32 Simulation Initialized ---");

  // Configure pin behaviors
  pinMode(POT_PIN, INPUT);

  // 1. Setup channel 0 with a placeholder 2000Hz frequency and 8-bit depth
  ledcSetup(BUZZER_PWM_CHANNEL, 2000, PWM_RESOLUTION);

  // 2. Physically bind GPIO 25 to that configured hardware PWM channel
  ledcAttachPin(BUZZER_PIN, BUZZER_PWM_CHANNEL);
}

void loop()
{
  // 1. Read the 12-bit analog value from the potentiometer dial (0 - 4095)
  rawPotValue = analogRead(POT_PIN);

  // 2. Map the raw sensor readings to a comfortable audio frequency range (100Hz - 2000Hz)
  targetFrequency = map(rawPotValue, 0, 4095, 100, 2000);

  // 3. Print values to the Serial Monitor for visual validation
  Serial.print("Potentiometer ADC: ");
  Serial.print(rawPotValue);
  Serial.print(" | Driving Buzzer at: ");
  Serial.print(targetFrequency);
  Serial.println(" Hz");

  // 4. Handle audio logic based on the sensor position
  if (rawPotValue > 50)
  {
    // Generate continuous oscillations using the updated channel frequency handler
    ledcWriteTone(BUZZER_PWM_CHANNEL, targetFrequency);
  }
  else
  {
    // Kill the audio wave entirely when the dial is turned all the way down
    ledcWriteTone(BUZZER_PWM_CHANNEL, 0);
  }

  // A tiny stabilization delay to keep the local simulation engine breathing easily
  delay(50);
}