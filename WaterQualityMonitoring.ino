#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <Adafruit_ADS1X15.h>
#include <DFRobot_ESP_EC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED width, in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DFRobot_ESP_EC ec;
Adafruit_ADS1115 ads;

float voltage, ecValue, tdsValue;
String safetyStatus;

String apiKey = "WO6H1JLUUME5JJRN";
const char *ssid =  "ZTE_2.4G_XjtJKS";
const char *pass =  "bq9kKXMU";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(32);
  ec.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
}

void loop()
{
  voltage = analogRead(36);  
  ecValue = ec.readEC(voltage, 25.0);
  tdsValue = ecValue * 500; // TDS in ppm

  if(tdsValue <= 500){
    safetyStatus = "Safe";
  } else {
    safetyStatus = "Unsafe";
  }

  Serial.print("EC: "); Serial.print(ecValue, 2);
  Serial.print(" mS/cm, TDS: "); Serial.print(tdsValue, 0);
  Serial.print(" ppm, Status: "); Serial.println(safetyStatus);

  // OLED display with uniform text size and spacing
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("EC: "); display.print(ecValue, 2); display.println(" mS/cm");

  display.setCursor(0, 20);
  display.print("TDS: "); display.print(tdsValue, 0); display.println(" ppm");

  display.setCursor(0, 40);
  display.print("Status: "); display.println(safetyStatus);

  display.display();
  delay(2000);

  // Optional calibration
  ec.calibration(voltage, 25.0);

  // ThingSpeak upload
  if (client.connect(server, 80))
  {
    String postStr = apiKey;
    postStr += "&field1=" + String(ecValue, 2);
    postStr += "&field2=" + String(tdsValue, 0);
    postStr += "&field3=" + safetyStatus;
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    delay(500);
  }
  client.stop();
}
