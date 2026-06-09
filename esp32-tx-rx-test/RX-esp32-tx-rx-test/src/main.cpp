#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Wokwi-GUEST";
const char *password = "";
const char *mqtt_server = "172.17.0.1";

// Array to define the output pins for the 5 sequential LEDs
const int ledPins[] = {18, 19, 21, 22, 23};
const int totalLEDs = 5;
const int BUZZER_PIN = 25;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  String message = "";
  for (int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }

  int sensorValue = message.toInt();
  Serial.println("Received Telemetry: " + String(sensorValue));

  // --- 1. Sequential LED Bar Graph Logic ---
  // Determine how many LEDs should be turned ON based on sensor threshold splits (0 to 4095)
  // Each LED represents roughly a step of ~819 units (4095 / 5)
  int ledsToLight = map(sensorValue, 0, 4095, 0, totalLEDs);

  for (int i = 0; i < totalLEDs; i++)
  {
    if (i < ledsToLight)
    {
      digitalWrite(ledPins[i], HIGH); // Power on the LED
    }
    else
    {
      digitalWrite(ledPins[i], LOW); // Power off the LED
    }
  }

  // --- 2. Passive Buzzer Handling Logic ---
  if (sensorValue > 50)
  {
    int frequency = map(sensorValue, 0, 4095, 200, 2000);
    tone(BUZZER_PIN, frequency);
  }
  else
  {
    noTone(BUZZER_PIN);
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000); // Give the virtual serial monitor window a moment to attach
  Serial.println("Receiver Board Booted. Initializing hardware pins...");

  // Initialize the Buzzer output
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize all 5 LED pins as OUTPUT arrays dynamically
  for (int i = 0; i < totalLEDs; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Ensure they start completely dark
  }

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial.println("Connecting to virtual Wi-Fi network...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("\nWi-Fi Connected successfully!");
  Serial.println("Receiver Board Initialized. Awaiting MQTT packets...");
}

void loop()
{
  if (!client.connected())
  {
    Serial.print("Attempting MQTT connection... ");
    if (client.connect("ESP32_Receiver"))
    {
      Serial.println("Connected to Broker!");
      client.subscribe("device/telemetry");
      Serial.println("Successfully subscribed to channel: device/telemetry");
    }
    else
    {
      Serial.print("Failed to connect. Client State error code: ");
      Serial.println(client.state());
      delay(2000);
    }
  }

  client.loop();
  delay(10);
}