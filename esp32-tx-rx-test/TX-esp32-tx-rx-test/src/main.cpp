#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h> // Make sure to add this to your lib_deps in platformio.ini

const char *ssid = "Wokwi-GUEST"; // Wokwi's built-in virtual network SSID
const char *password = "";
// Use 10.0.2.2 to point to your actual computer's localhost from within the Wokwi sandbox
const char *mqtt_server = "172.17.0.1";

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  client.setServer(mqtt_server, 1883);
}

void loop()
{
  // If the client isn't connected, attempt to reconnect and print why it failed
  if (!client.connected())
  {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqtt_server);
    Serial.print("... ");

    if (client.connect("ESP32_Transmitter"))
    {
      Serial.println("CONNECTED!");
    }
    else
    {
      Serial.print("FAILED, rc=");
      Serial.print(client.state());
      Serial.println(" (Will retry in 2 seconds)");
      delay(2000);
      return; // Skip publishing this loop since we are offline
    }
  }

  client.loop();

  int potValue = analogRead(34);
  String payload = String(potValue);

  // This will now only execute if we are 100% authenticated with Mosquitto
  if (client.publish("device/telemetry", payload.c_str()))
  {
    Serial.println("Successfully Delivered: " + payload);
  }
  else
  {
    Serial.println("Publish failed! Packet dropped.");
  }

  delay(200);
}