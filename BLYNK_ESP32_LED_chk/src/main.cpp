#include <Arduino.h>

// #define BLYNK_TEMPLATE_ID "TMPL3__LAUIVg"
// #define BLYNK_TEMPLATE_NAME "ESP32 Control"
// #define BLYNK_AUTH_TOKEN "7GsZQd5dBiz8D79HpJc58v_ZHhD2onBc"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

const char auth[] = BLYNK_AUTH_TOKEN;
const char *ssid = "Wokwi-GUEST";
const char *pass = "";

#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27

// -- Blynk Switch Handlers --
BLYNK_WRITE(V0)
{
  int value = param.asInt(); // 0 = OFF, 1 = ON
  digitalWrite(RED_LED, value);

  if (value == 1)
  {
    Serial.println("RED_LED: ON");
  }
  else
  {
    Serial.println("RED_LED: OFF");
  }
}

BLYNK_WRITE(V1)
{
  int value = param.asInt(); // 0 = OFF, 1 = ON
  digitalWrite(GREEN_LED, value);

  if (value == 1)
  {
    Serial.println("GREEN_LED: ON");
  }
  else
  {
    Serial.println("GREEN_LED: OFF");
  }
}

BLYNK_WRITE(V2)
{
  int value = param.asInt(); // 0 = OFF, 1 = ON
  digitalWrite(BLUE_LED, value);

  if (value == 1)
  {
    Serial.println("BLUE_LED: ON");
  }
  else
  {
    Serial.println("BLUE_LED: OFF");
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Start with all OFF
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  Serial.println("ESP32 is ready. waiting for Blynk commands....");
}

void loop()
{
  Blynk.run();
}